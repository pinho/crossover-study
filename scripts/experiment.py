from yaml import load, CLoader
from collections.abc import Iterable
from os import system
from datetime import datetime
from docker.types import Mount
import docker
import time
import click


# ---------------------------------------------------------------------------- #
# Funcao para imprimir LOG com timestamp
# ---------------------------------------------------------------------------- #
def debug_log(message):
    now = datetime.now()
    print(now.strftime('[%d/%m/%y - %H:%M:%S %p] -- '), end='', flush=True)
    print(f'{message}', flush=True)

# ---------------------------------------------------------------------------- #
# Executar experimentos.
# by Ronaldd Pinho <ronaldppinho@gmail.com>
# 
# Executa um conjunto de testes com diferentes configurações do algoritmo.
# 
# Um arquivo de configuração (yaml) define os parâmetros de configurações das
# execuções. Diferentes configurações são construídas e cada uma delas é execu-
# tada em um contêiner "-n" vezes
# ---------------------------------------------------------------------------- #
# Definições padrão
# CONFIG_FILE = "config.yml" 
IMAGE_NAME  = "crossoverstudy"
VOLUME_NAME = "studyvol"
VALID_CLI_OPTIONS = [
  "infile", "db", "popsize", "stop", "crossover", "xrate", "mrate", "ring"]

# ---------------------------------------------------------------------------- #
# Classe ParamCombination: Combinação de parâmetros
# Define uma combinação de parâmetros e exporta a string correspondente para uso
# na linha de comandos com os "--{option}" e valores
class ParamCombination:
  params: dict
  def __init__(self, dictP: dict):
    self.params = dictP

  def __str__(self):
    s = str()
    for option in self.params:
      s += f" --{option} {self.params[option]} "
    return s

# ---------------------------------------------------------------------------- #
# Classe ConfigFile: Configuração definida por um arquivo yaml.
# Faz o carregamento do arquivbo de configuração em um dicionário e exporta
# definindo as flags e opções aceitas nos binários de execução do algoritmo.
class ConfigFile:
  params: dict
  def __init__(self, filename: str):
    with open(filename, "r") as f:
      buff = f.read()
    self.params = load(buff, Loader=CLoader)

    # Validar as opções definidas no arquivo
    for option in self.params:
      if not self.is_valid_option(option):
        raise KeyError(f'Option "{option}" is invalid.')
    # for option in VALID_CLI_OPTIONS:
    #   try:
    #     _ = self.params[option]
    #   except KeyError:
    #     raise KeyError(f'Option "{option}" is missing.')

  def is_valid_option(self, optname) -> bool:
    return (optname in VALID_CLI_OPTIONS)

  def turn_all_iterable(self) -> dict:
    new_dict = dict()
    for key in self.params:
      if isinstance(self.params[key], Iterable) and not isinstance(self.params[key], str):
        new_dict[key] = self.params[key]
      else:
        new_dict[key] = [ self.params[key] ]
    return new_dict

  def parse_combinations(self) -> list:
    iter_params = self.turn_all_iterable()
    dbfile = self.params["db"]
    param_list = []

    for crossover in iter_params["crossover"]:
      for xrate in iter_params["xrate"]:
        for mrate in iter_params["mrate"]:
          for popsize in iter_params["popsize"]:
            for numgen in iter_params["stop"]:
              for infile in iter_params["infile"]:
                # Cria obj de combinação
                pc = ParamCombination({
                  "crossover": crossover,
                  "xrate": xrate,
                  "mrate": mrate,
                  "popsize": popsize,
                  "stop": numgen,
                  "infile": infile,
                  "db": dbfile
                })
                param_list.append(pc)

    return param_list

# ---------------------------------------------------------------------------- #
# Classe Command: Representa um comando disparável na linha de comando
# É usado para criar um comando completo com um binário e uma combinação de
# opções de linha de comandos.
class Command:
  binary_name: str
  params: ParamCombination
  def __init__(self, binary: str, params=None):
    self.binary_name = binary
    self.params = params

  def __str__(self):
    return f'{self.binary_name} {self.params}'

  def run(self):
    system(str(self))

# ---------------------------------------------------------------------------- #
# Criar contêineres
def docker_create(fullcommand) -> docker.models.containers.Container:
  client = docker.from_env()
  num_list_containers = len(client.containers.list(all=True))
  # Configura e Cria um novo container e retorna-o
  cont = client.containers.create(IMAGE_NAME, fullcommand,
      name=f'experimentation_{num_list_containers+1}', detach=True, 
      mounts=[ Mount("/db", VOLUME_NAME) ], cpu_shares=500)
  return cont

# Main function 
@click.command()
@click.argument('binaryname')
@click.option('-n','--count',help="Repetir execuções N vezes", default=1, show_default=True)
@click.option('-t', '--wait-time', help="Tempo entre as verficações de contêineres (segundos)", default=30, show_default=True)
@click.option('-c', '--config', help="Caminho para o arquivo de configuração YAML", default='experiment.config.yml', show_default=True)
@click.option('-j', '--max-con',help="Número máximo de contêiners ativos rodando em paralelo", default=1, show_default=True)
def main(binaryname, count, wait_time, config, max_con):
  c = ConfigFile(config)
  combinations = c.parse_combinations()
  containers = []

  debug_log("Analisando as combinações de parâmetros")

  for parCombination in combinations:
    command = Command(binaryname, params=parCombination)
    full_command = f"run {count} '{command}'"
    containers.append( docker_create(full_command) )
  ids = [ c.attrs['Id'] for c in containers ]
  
  # num_created_containers = len(containers)
  client = docker.from_env()
  num_containers = len(containers) # Número de containers escalonados
  num_running = 0 # Número de containers rodando

  debug_log(f"{num_containers} contêineres escalonados")

  for id in ids:
    cont = client.containers.get(id)
    
    if len(client.containers.list()) < max_con:
      num_running += 1
      debug_log(f"[{num_running}º de {num_containers}] Iniciando o contêiner \"{cont.attrs['Name'][1:]}\"")
      cont.start()
    else:
      debug_log("Esperando algum contêiner finalizar")
      start_wait = time.time()
      time_until_now = 0
      while not len(client.containers.list()) < max_con:
        time.sleep(wait_time)
        time_until_now += wait_time
        # debug_log(f"({round(time_until_now/60,1)} minutos) Aguardando...")
      debug_log(f"Vaga para um novo contêiner: tempo de espera = {round((time.time()-start_wait)/60, 2)} minutos")
      num_running += 1
      debug_log(f"Iniciando o contêiner \"{cont.attrs['Name'][1:]}\"")
      cont.start()
      pass
  
  print("----------------------------------------")
  debug_log("Todos os contêineres já foram iniciados.\nTchaau :D")
  return

# ---------------------------------------------------------------------------- #
if __name__ == "__main__":
  main()
