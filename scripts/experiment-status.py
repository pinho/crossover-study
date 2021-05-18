import argparse
import sqlite3 as lite
from string import Template

'''
Passe um arquivo de banco de dados com 1 ou mais tabelas de execuções e o script
irá mostrar informações de execuções nesse arquivo, como: quantas execuções para
cada problema e operador de crossover.
'''

parser = argparse.ArgumentParser()
parser.add_argument('dbfile')
parser.add_argument('--mcp', action='store_true', default=False, help='Mostrar informações para o problema do clique máximo')
parser.add_argument('--mkp', action='store_true', default=False, help='Mostrar informações para o problema da mochila multidimensional')
parser.add_argument('--scp', action='store_true', default=False, help='Mostrar informações para o problema da cobertura de conjuntos')
parser.add_argument('--stp', action='store_true', default=False, help='Mostrar informações para o problema da árvore de Steiner')
parser.add_argument('-a', '--all', action='store_true', default=False, help='Mostrar informações para todos os problemas no arquivo')

QUERY_TEMPLATE = Template('''select instance_file, crossover_name, crossover_rate, 
    count(id) as count, avg(total_costs) as mean_result from $t
    group by instance_file, crossover, crossover_rate;''')


def esc(code):
    return f'\033[{code}m'


def table_exists(con: lite.Connection, tablename: str) -> bool:
    try:
        cursor = con.cursor()
        cursor.execute(f'SELECT id FROM {tablename};')
        return True
    except:
        return False


def display_from(con: lite.Connection, tablename: str, title: str):
    table_existing = table_exists(con, tablename)
    print(80*'-')
    print(title, end=' ')
    if table_existing: 
        print(f'{esc("38;5;46")} OK! {esc(0)}')
    else:
        print(f'{esc("38;5;9")} Tabela não encontrada! {esc(0)}')
    print(80*'-')

    if table_existing:
        query = QUERY_TEMPLATE.substitute({ 't': tablename })
        cursor = con.cursor()
        for instance, crossover, crossover_rate, count, mean in cursor.execute(query):
            crossover_fmt = f'{crossover} ({int(crossover_rate*100)}%)'
            print(f'{crossover_fmt:<16}\t{instance}\t{count}\t{mean}')
    print('\n')
    return


def main():
    args = parser.parse_args()

    try:
        connection = lite.connect(args.dbfile)
    except:
        print("Erro ao conectar com o arquivo", args.dbfile)
        exit(1)

    if args.scp or args.all:
        display_from(connection, 'setcovering_executions', 'Problema da Cobertura de conjuntos')

    if args.stp or args.all:
        display_from(connection, 'steinertree_executions', 'Problema da Árvore de Steiner')

    if args.mcp or args.all:
        display_from(connection, 'maxclique_executions', 'Problema do Clique Máximo')

    if args.mkp or args.all:
        display_from(connection, 'mknap_executions', 'Problema da Mochila Multidimensional')

    connection.close()

if __name__ == '__main__':
    main()
