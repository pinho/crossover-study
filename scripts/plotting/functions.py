import sqlite3 as sql
from string import Template
from pandas import read_sql_query
from matplotlib.pyplot import subplots
# relative imports
from data import DataSolver
from boxplot_styles import black_boxes

# Contrói um Query SQL padrão baseada na tabela e no operador de crossover.
# A query consulta o arquivo de instância, o crossover, a taxa de cruzamento, os
# custos da solução e a convergência da busca em uma tabela defininda por
# "tablename".
def build_query(tablename, crossover, crossover_rate=1.0, mutation_rate=None):
    columns = '''instance_file, crossover, crossover_rate, total_costs, convergence '''
    t = Template('select ' + columns + 'from $table where crossover = $xover and crossover_rate = $cr')
    query = t.substitute({"table": tablename, "xover": crossover, "cr": crossover_rate})
    return query

# Plota um gráfico de Boxplot comparando os resultados dos 5 operadores de
# crossover principais estudados. Aplica uma estilização customizado nos boxplots
# Recece um objeto de conexão com um arquivo SQLite o nome da tabela e o nome da
# instância do problema.
def plot_crossover_boxplots(con: sql.Connection, tablename, instance=None, figsize=(11,8)):
    '''Plota grafico de barras com a comparacao dos resultados do crossovers
    '''
    columns = 'instance_file, crossover, crossover_rate, total_costs '
    query = f'select {columns} from {tablename}'
    if instance is not None:
        query += f" where instance_file = '{instance}'"
    
    # Constroi o DataFrame com todas as linhas
    df = read_sql_query(query, con)
    
    # Constroi um DataFrame para cada operador de crossover
    crossover_ids = [0, 1, 2, 4, 8]
    dataframes = dict()
    for _id in crossover_ids:
        dataframes[_id] = df.loc[df['crossover'] == _id]
    
    # Extrai as series de custos como listas, de cada operador
    all_result_lists = list()
    for _id in dataframes:
        all_result_lists.append(list(dataframes[_id]['total_costs']))
        
    # Plota as os boxplots
    fig, ax = subplots(1, 1, figsize=figsize)
    boxplot = ax.boxplot(all_result_lists,
            patch_artist=True,
            showmeans=True,
            labels=[ DataSolver.resolve_crossover_name(x) for x in [0, 1, 2, 4, 8] ])
    black_boxes(boxplot)
    ax.set_title(f'Resultados para a instância {instance}', fontsize=15)
    return fig, ax
