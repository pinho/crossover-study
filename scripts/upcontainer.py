#!/bin/python3
# Lançar uma execução no container docker 
# 
# Deve receber:
#   um comando (-c) para executar
#   o número de vezes (-n) para repetí-lo 
#   um arquivo de configuração com os argumentos

import os
import docker
import click
import yaml
from collections.abc import Iterable

IMAGE_NAME  = 'crossoverstudy'
VOLUME_NAME = 'studyvol'

class ConfigFile:
  filename: str
  args: dict

  def __init__(self, filename : str):
    self.filename = filename
    with open(filename, "r") as f:
      buff = f.read()
      self.args = yaml.load(buff, Loader=yaml.CLoader)

  def __str__(self):
    res = ""
    for key in self.args:
      res += f"--{key} {self.args[key]} "
    return res


# O comando e as definições das opções de linha de comandos.
# O comando deve ser passado como argumnto posicional, por exemplo
#
# >>> raiseOnContainer.py "maxclique -f /data/in/brock200_1.clq"
#
@click.command()
@click.argument('command')
@click.option('-n', '--count', help="Número de vezes para repetir", default=1, show_default=True)
@click.option('-c', '--config', type=str, help="Arquivo de configuração dos parâmetros", default="config.yml")
@click.option('--name', help="Nome para o container")
@click.option('--rm', help="Remover contêiner ao finalizar", type=bool, default=False)
def main(command, count, config, name, rm):
  CMD = ["run"]
  CMD.append(str(count))
  
  for word in command.split(" "):
    CMD.append(word)

  if config is not None:
    config_file = ConfigFile(config)
    list_args = str(config_file)
    # print(list_args)
    for word in list_args.split(" "):
      CMD.append(word)

  fullcmd = ""
  for word in CMD:
    fullcmd += f'{word} '

  click.echo(f'Comando completo:\n{fullcmd}')

  client = docker.from_env()
  container = client.containers.run(IMAGE_NAME, command=CMD,
      detach=True,
      remove=rm,
      name=name,
      mounts=[ docker.types.Mount("/databases", "studyvol") ],
      cpu_shares=500 )

  print(f"Container \'{name}\' {container.status}")


if __name__ == '__main__':
  if os.geteuid() == 0:
    main()
  else:
    print("Não pode executar esta operação a menos que seja root")
