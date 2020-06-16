import platform, sys
from .config_file import ConfigFile
from .command import Command

class Runner:
    """Executador de comandos

    A class Runner é construída a partir de uma instância de um arquivo de
    configuração YAML e possui a função de executar as combinação dos parâmetros
    definidos no arquivo.

    Um objeto da classe possui um arquivo de configurção (ConfigFile)
    o nome de um dos executáveis do projeto
    e o arquivo de instância para entrada da(s) execução(ões).
    """
    config: ConfigFile
    executable: str
    input_file: str

    def __init__(self, config_file: ConfigFile):
        self.config = config_file

    def set_executable(self, name: str):
        self.executable = name

    def set_input(self, filename: str):
        self.input_file = filename

    def run(self, num, database, suppress=True):
        '''Executa todas as combinações de parâmetros

        A partir de um arquivo de configuração Yaml (ConfigFile), o método
        executa todas as combinações de parâmetros possíveis "num" vezes.
        '''

        ## Dicionário de argumentos
        args = self.config.parameters
        ## Número total ed comandos para executar
        total_num_commands = num * self.config.num_combinations

        e = 0
        for i in range(num):
            for crossover_ in args["crossover"]:
                for epochs_ in args["epochs"]:
                    for popsize_ in args["population"]:
                        for crossover_r in args["crossover_rate"]:
                            for mutation_r in args["mutation_rate"]:
                                comm = Command(
                                    self.config.problem_name,
                                    self.config.instance_file,
                                    crossover=crossover_,
                                    popsize=popsize_,
                                    num_epochs=epochs_,
                                    crossover_rate=crossover_r,
                                    mutation_rate=mutation_r,
                                    database=database
                                )
                                e += 1

                                if (platform.system() == "Linux"):
                                    sys.stdout.write(f"\r\u001b[44;1m {e} de {total_num_commands} \u001b[0m {comm.get_params()}")
                                else:
                                    sys.stdout.write(f"\r{e} de {total_num_commands} {comm.get_params()}")
                                    
                                # print('\n', comm)
                                comm.run(suppress_log=suppress)
        return
