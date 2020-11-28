"""SQLite Database Files

Possui classes voltadas para arquivo de bancos de dados SQLite especialmente
estruturados para os problemas de otimização.
Algumas consultas comuns foram automatizadas em métodos da classe.
"""

import sqlite3 as lite
import pandas as pd
from numpy import array

# Lista padrão de operadores de crossover usados nos experimentos
DEF_CROSS_LIST = [ 0, 1, 2, 4, 8, 16, 32, 64 ]

# Um arquivo de banco de dados SQLite do projeto.
class DatabaseFile:
  def __init__(self, path):
    self.filename = path
    self.tablename = None
    self.result_column = None
    try:
      self.connection = lite.connect(self.filename)
    except:
      raise IOError(f'Não foi possível abrir o arquivo "{self.filename}"')
    self.main_cursor = self.connection.cursor()


  # Faz uma consulta por informações de quantidade de execuções, média dos
  # resultados para cada um dos operadores de crossover agrupados por arquivos
  # de instâncias. Retorna um pandas.DataFrame with o resultado da consulta.
  def select_all_crossovers_per_instance(self):
    if self.tablename is None or self.result_column is None:
      raise NotImplementedError
    else:
      QRY = f'''SELECT instance_file, crossover, count(id) as count, avg({self.result_column}) as mean_costs
          FROM {self.tablename}
          GROUP BY instance_file, crossover
          ORDER BY instance_file, crossover'''
      return pd.read_sql_query(QRY, self.connection)


  # Faz uma selação retornando os valores de resultados obtidos por cada
  # execução usando alguma outra coluna para filtrar.
  def get_results(self, as_array=False, **kwargs):
    # raise NotImplementedError
    QRY = f'''SELECT {self.result_column} FROM {self.tablename}'''
    num_args = len(kwargs.keys())
    # print("Número de argumentos em kwargs:", num_args)
    if num_args > 0:
      QRY += ' WHERE '
      for n, arg in enumerate(kwargs.keys()):
        # print(n, arg)
        QRY += f'{arg} == '
        QRY += f'"{kwargs[arg]}"' if isinstance(kwargs[arg], str) else f'{kwargs[arg]}'
        if n < (num_args-1):
          QRY += ' AND '
    
    resultant_df = pd.read_sql_query(QRY, self.connection)
    if as_array:
      return array( resultant_df[self.result_column], dtype=float )
    else:
      return resultant_df

  # Retrona um DataFrame onde cada coluna é um operador de crossover e as linhas
  # são os resultados obtidos nas execuções
  def get_results_per_crossover(self, instance, crossover_list=None):
    dicio = {}
    cross_operators_id = DEF_CROSS_LIST
    if crossover_list is not None:
      cross_operators_id = crossover_list

    for cross_id in cross_operators_id:
      dicio[cross_id] = self.get_results(
          instance_file=instance, crossover=cross_id, as_array=True)
    return pd.DataFrame(dicio)



#-------------------------------------------------------------------------------
# Arquivo de banco de dados SQLite para o problema da Cobertura de Conjuntos
class SCPDbFile(DatabaseFile):
  def __init__(self, filename: str):
    super().__init__(path = filename)
    self.tablename = 'setcovering_executions'
    self.result_column = 'total_costs'


#-------------------------------------------------------------------------------
# Arquivo de banco de dados SQLite para o problema da Clique Máximo com Pesos
class MWCPDbFile(DatabaseFile):
  def __init__(self, filename: str):
    super().__init__(path = filename)
    self.tablename = 'maxclique_executions'
    self.result_column = 'total_cost'


#-------------------------------------------------------------------------------
# Arquivo de banco de dados SQLite para o problema da Árvore de Steiner
class STPDbFile(DatabaseFile):
  def __init__(self, filename: str):
    super().__init__(path = filename)
    self.tablename = 'steiner_executions'
    self.result_column = 'total_costs'


#-------------------------------------------------------------------------------
# Arquivo de banco de dados SQLite para o problema da mochila multidimensional
class MKPDbFile(DatabaseFile):
  def __init__(self, filename: str):
    super().__init__(path = filename)
    self.tablename = 'mknap_executions'
    self.result_column = 'total_costs'

