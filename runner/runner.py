import yaml
from .command import Command
from collections.abc import Iterable

def key_exists(key: str, dict_config: dict):
    if key in dict_config.keys():
        return
    else:
        raise Exception(f'Key \'{key}\' not found in config file')

def is_iterable(obj):
    return isinstance(obj, Iterable)


class Runner():
    def __init__(self, config_file : str):
        with open(config_file, 'r') as f:
            buff = f.read()
            conf = yaml.load(buff, Loader=yaml.CLoader)
        key_exists('run', conf)
        key_exists('program', conf['run'])
        key_exists('args', conf['run'])
        key_exists('crossover', conf['run']['args'])
        key_exists('epochs', conf['run']['args'])
        key_exists('population', conf['run']['args'])
        key_exists('crossover_rate', conf['run']['args'])
        key_exists('mutation_rate', conf['run']['args'])
        key_exists('instance', conf['run']['args'])
        self.program_name = conf['run']['program']
        self.parameters = conf['run']['args']
        # Transform all elements in lists
        for key in self.parameters:
            if not is_iterable( self.parameters[key] ):
                self.parameters[key] = [ self.parameters[key] ]

    def run(self, num_executions, savedb, suppress=False):
        for i in range(num_executions):
            if (num_executions > 1): print(f"[ {i+1} ]", end="")
            for crossover_ in self.parameters["crossover"]:
                for epochs_ in self.parameters["epochs"]:
                    for popsize_ in self.parameters["population"]:
                        for crossover_r in self.parameters["crossover_rate"]:
                            for mutation_r in self.parameters["mutation_rate"]:
                                command = Command(
                                    self.program_name, self.parameters["instance"],
                                    crossover=crossover_,
                                    popsize=popsize_,
                                    num_epochs=epochs_,
                                    crossover_rate=crossover_r,
                                    mutation_rate=mutation_r,
                                    database=savedb
                                )
                                if (num_executions > 1): print(' \t:: ', end='')
                                print(command)
                                command.run(suppress_log=suppress)
        return
