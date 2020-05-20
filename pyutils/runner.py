from .config_file import ConfigFile

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

    # TODO: Reimplementar o método run()
    # def run(self, num_executions, savedb, suppress=False):
    #     for i in range(num_executions):
    #         if (num_executions > 1): print(f"[ {i+1} ]", end="")
    #         for crossover_ in self.parameters["crossover"]:
    #             for epochs_ in self.parameters["epochs"]:
    #                 for popsize_ in self.parameters["population"]:
    #                     for crossover_r in self.parameters["crossover_rate"]:
    #                         for mutation_r in self.parameters["mutation_rate"]:
    #                             command = Command(
    #                                 self.program_name, self.parameters["instance"],
    #                                 crossover=crossover_,
    #                                 popsize=popsize_,
    #                                 num_epochs=epochs_,
    #                                 crossover_rate=crossover_r,
    #                                 mutation_rate=mutation_r,
    #                                 database=savedb
    #                             )
    #                             command.insert_on(savedb)
    #                             if (num_executions > 1): print(' \t:: ', end='')
    #                             print(command)
    #                             command.run(suppress_log=suppress)
    #     return
