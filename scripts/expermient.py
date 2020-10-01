from yaml import load, CLoader
from collections.abc import Iterable
from os import system
from docker.types import Mount
import docker
import time
import click

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
CONFIG_FILE = "config.yml" 
IMAGE_NAME  = "crossoverstudy"
VOLUME_NAME = "studyvol"
VALID_CLI_OPTIONS = [
  "infile", "db", "popsize", "epochs", "crossover", "xrate", "mrate", "ring"]

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
            for numgen in iter_params["epochs"]:
              for infile in iter_params["infile"]:
                # Cria obj de combinação
                pc = ParamCombination({
                  "crossover": crossover,
                  "xrate": xrate,
                  "mrate": mrate,
                  "popsize": popsize,
                  "epochs": numgen,
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
  # Verifica o número de contêiners em execução
  cont = client.containers.create(IMAGE_NAME, fullcommand,
      detach=True, mounts=[ Mount("/db", VOLUME_NAME) ], cpu_shares=500)
  return cont


# Main function 
@click.command()
@click.argument('binaryname')
@click.option('-n','--count',help="Repetir execuções N vezes", default=1, show_default=True)
@click.option('--max',help="Número máximo de contêiners ativos", default=2, show_default=True)
def main(binaryname, count, max):
  c = ConfigFile(CONFIG_FILE)
  combinations = c.parse_combinations()
  containers = []

  for parCombination in combinations:
    command = Command(binaryname, params=parCombination)
    full_command = f"run {count} '{command}'"
    print("[*******]", full_command, end="", flush=True)
    
    containers.append( docker_create(full_command) )
    time.sleep(.5)
    print(f"\r[CREATED] {full_command}", flush=True)

  containers_running = 0
  for cont in containers:
    print(cont)
    cont.start()
    containers_running += 1
    # time.sleep(2)
    if containers_running == max:
      cont.wait()

# ---------------------------------------------------------------------------- #
if __name__ == "__main__":
  main()
