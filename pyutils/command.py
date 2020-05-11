"""Class Command

Represents a command line program with a set of parameters.
An object of this class hold arguments and start a command line execution.
"""

import os
import sqlite3

class Command():
    program_name : str
    args : dict
    inpath_program : bool

    def __init__(self, program, inputfile, crossover, popsize, num_epochs, database,
            crossover_rate=0.8, mutation_rate=0.05, locally=True):
        self.program_name = program
        self.args = dict()
        self.args["infile"] = inputfile
        self.args["crossover"] = int(crossover)
        self.args["popsize"] = int(popsize)
        self.args["epochs"] = int(num_epochs)
        self.args["xrate"] = float(crossover_rate)
        self.args["mrate"] = float(mutation_rate)
        self.args["db"] = database
        self.inpath_program = locally


    def __str__(self):
        strcmd = './' if self.inpath_program else ''
        strcmd += self.program_name
        for key in self.args:
            strcmd += f' --{key} {str(self.args[key])}'
        return strcmd


    def config_id(self):
        '''Define o código da configuração de parâmetros

        A partir de uma combinação de parâmetros definida em uma arquivo Yaml,
        a função cria a sua respectiva string 
        '''
        if self.args['crossover'] == 0:
            code = 'UNIFORM'
        else:
            code = str(self.args['crossover']) + 'POINTS'

        cr = str( int(100 * self.args['xrate']) )
        mr = str( int(100 * self.args['mrate']) )
        code += 'P'+ str(self.args['popsize'])
        code += 'G'+ str(self.args['epochs'])
        code += 'CR'+ cr
        code += 'MR'+ mr
        # print(code)
        return code


    def insert_on(self, dbname: str):
        con = sqlite3.connect(dbname)
        cur = con.cursor()
        cur.execute('INSERT INTO config VALUES (?, ?, ?, ?, ?, ?);',
                (self.config_id(), self.args['crossover'], self.args['popsize'],
                self.args['epochs'], self.args['xrate'],
                self.args['mrate']))


    def run(self, suppress_log=False):
        cmd_ = str(self)
        if suppress_log:
            cmd_ += " > /dev/null"
        os.system(cmd_)
