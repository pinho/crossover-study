#!/bin/python

import click
from runner import Runner

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
        rnr = Runner(config)
        rnr.run(number_exec, output, suppress=suppress)
    except FileNotFoundError as err:
        print(err)


if __name__ == '__main__':
    try:
        main()
    except KeyError as e:
        print(f'KeyError: key {e} not found')
