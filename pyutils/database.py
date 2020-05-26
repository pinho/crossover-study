import sqlite3
from numpy import array

# classe DB
#
# Interface de comunicação com um arquivo de banco de dados (.db) com a estrutura
# usada no projeto.
#
# Implementa principalmente os métodos de leitura de dados do banco.
class DB:

    def __init__(self, filename):
        self.filename = filename
        self.connection = sqlite3.connect(self.filename)

    def __str__(self):
        return f'DB(\'{self.filename}\')'

    # Leitura e tratamento dos dados de convergência na tabela execuções
    def read_convergence(self, where=None, dtype=float ):
        sql = 'SELECT convergencia FROM execucoes '
        cur = self.connection.cursor()
        # Criando lista de resultados da consulta
        lista = []
        for row in cur.execute(sql):
            lista.append( [dtype(elem) for elem in row[0].split(';')] )

        return lista
