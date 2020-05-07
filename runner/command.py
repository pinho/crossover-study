"""Class Command

Represents a command line program with a set of parameters.
An object of this class hold arguments and start a command line execution.
"""

import os

class Command():
    program_name : str
    args : dict
    inpath_program : bool

    def __init__(self, program, inputfile, crossover, popsize, num_epochs, crossover_rate=0.8, mutation_rate=0.05, locally=True):
        self.program_name = program
        self.args = dict()
        self.args["infile"] = inputfile
        self.args["crossover"] = int(crossover)
        self.args["popsize"] = int(popsize)
        self.args["epochs"] = int(num_epochs)
        self.args["xrate"] = float(crossover_rate)
        self.args["mrate"] = float(mutation_rate)
        self.inpath_program = locally

    def __str__(self):
        strcmd = './' if self.inpath_program else ''
        strcmd += self.program_name
        for key in self.args:
            strcmd += f' --{key} {str(self.args[key])}'
        return strcmd

    def run(self, suppress_log=False):
        cmd_ = str(self)
        if suppress_log:
            cmd_ += " > /dev/null"
        os.system(cmd_)
