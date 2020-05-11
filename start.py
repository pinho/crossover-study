#!/bin/python

import click
import os
import sqlite3
import pyutils

SCRATCH_DB_PATH = './'
SCRATCH_DB = 'scratch.db'

@click.command()
@click.option('-c', '--config', default='config.yml', show_default=True, 
        type=str, help="Set the config file")
@click.option('-n', '--number-exec', default=1, show_default=True, 
        type=int, help='Number of executions')
@click.option('-o', '--output', default='result.db', show_default=True, 
        type=str, help="Set name of db file to save all results")
@click.option('--suppress', default=False, is_flag=True, 
        help="Suppres log of each command")
def main(number_exec, config, output, suppress):
    try:
        # Copia a estrutura do banco de dados
        os.system('cp -vf '+ SCRATCH_DB_PATH+SCRATCH_DB +' '+ output)

        # Cria um objeto Runner
        rnr = pyutils.Runner(config)

        # Dispara execuções
        rnr.run(number_exec, output, suppress=suppress)

    except FileNotFoundError as err:
        print(err)
    except sqlite3.DatabaseError:
        print("Erro no banco de dados")
    except sqlite3.DataError:
        print("Erro nos dados")


if __name__ == '__main__':
    try:
        main()
    except KeyError as e:
        print(f'KeyError: key {e} not found')
