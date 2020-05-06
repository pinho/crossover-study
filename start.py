#!/bin/python

import yaml
import click
from collections.abc import Iterable
from starter import Command

def is_iterable(obj):
    return isinstance(obj, Iterable)


@click.command()
@click.option('-n', '--number-exec', default=1, show_default=True, help='Number of executions')
@click.option('-c', '--config', default='config.yml', show_default=True, type=str, help="Set the config file")
@click.option('--suppress', default=False, is_flag=True, help="Suppres log of each command")
def main(number_exec, config, suppress):
    with open(config, 'r') as f:
        stream = f.read()
    
    config = yaml.load(stream, Loader=yaml.CLoader)
    PROGRAM = config["run"]["program"]
    ARGS = config['run']['args']
    
    # Transforma o dict de argumentos em um dict de listas
    for a in ARGS:
        if not is_iterable( ARGS[a] ):
            ARGS[a] = [ ARGS[a] ]

    for i in range(number_exec):
        for crossover_ in ARGS["crossover"]:
            for epochs_ in ARGS["epochs"]:
                for popsize_ in ARGS["population"]:
                    for crossover_r in ARGS["crossover_rate"]:
                        for mutation_r in ARGS["mutation_rate"]:
                            command = Command(
                                PROGRAM, ARGS["instance"],
                                crossover=crossover_,
                                popsize=popsize_,
                                num_epochs=epochs_,
                                crossover_rate=crossover_r,
                                mutation_rate=mutation_r
                            )
                            print(command)
                            command.run(suppress_log=suppress)
    
    return


if __name__ == '__main__':
    main()
