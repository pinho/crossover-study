import yaml
from collections.abc import Iterable

class ConfigFile:
    """class ConfigFile

    Define a representação de um arquivo de configuração YAML que define todos
    os parâmetros para a execuções do algoritmo genético.
    """

    def __init__(self, filename : str):
        """ConfigFile Construtor

        Recebe o nome do arquivo de configuração (.yaml ou .yml).
        Verifica se todas as chaves requeridas estão presentes no arquivo.
        """
        self.filename = filename

        with open(filename, "r") as f:
            buff = f.read()
            conf = yaml.load(buff, Loader=yaml.CLoader)

        self.key_exists('run', conf)
        self.key_exists('program', conf['run'])
        self.key_exists('instance', conf['run'])
        self.key_exists('args', conf['run'])
        self.key_exists('crossover', conf['run']['args'])
        self.key_exists('epochs', conf['run']['args'])
        self.key_exists('population', conf['run']['args'])
        self.key_exists('crossover_rate', conf['run']['args'])
        self.key_exists('mutation_rate', conf['run']['args'])

        self.program_name = conf['run']['program']
        self.instance_file = conf['run']['instance']
        self.parameters = conf['run']['args']

        # Transforma todos os elementos (values) do dict em listas
        for key in self.parameters:
            if not isinstance( self.parameters[key], Iterable ):
                self.parameters[key] = [ self.parameters[key] ]

        # Conta a quantidade de comandos diferentes para cobrir todas as
        # combinações de parâmetros
        aux = 1
        for key in self.parameters:
            aux = aux * len( self.parameters[key] )
        self.num_combinations = aux


    def key_exists(self, key: str, dict_config: dict):
        """Checa se uma chave (string) faz parte de um dicionário
        """
        if key in dict_config.keys():
            return
        else:
            raise Exception(f'Key \'{key}\' not found in config file')
