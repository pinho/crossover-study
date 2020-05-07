#!/bin/python

import click
from collections.abc import Iterable
from runner import Runner


@click.command()
@click.option('-n', '--number-exec', default=1, show_default=True, help='Number of executions')
@click.option('-c', '--config', default='config.yml', show_default=True, type=str, help="Set the config file")
@click.option('--suppress', default=False, is_flag=True, help="Suppres log of each command")
def main(number_exec, config, suppress):
    rnr = Runner(config)

    rnr.run(number_exec, suppress=suppress)
    
    return


if __name__ == '__main__':
    try:
        main()
    except KeyError as e:
        print(f'KeyError: key {e} not found')
