import click
import sqlite3 as lite
import pandas as pd
from sys import argv
from matplotlib import pyplot as plt

## Nomes dos aqrquivos de instancia
scp_instance_files = ['scp41.txt', 'scp42.txt', 'scp43.txt', 'scp44.txt']
mcp_instance_files = ['C1000.9.clq', 'san1000.clq', 'p_hat1000-1.clq', 'p_hat1000-2.clq']


class OptProblemData:
    def __init__(self, table_name, instance_files, result_column):
        self.table_name = table_name
        self.instance_files = instance_files
        self.result_column = result_column

    def create_dataframes_from_db(self, dbfilename, crossover_rate=1.0):
        db_connection = lite.connect(dbfilename)
        query = f'''
        SELECT instance_file, crossover, crossover_name, crossover_rate, 
                count(id) as count, avg({self.result_column}) as mean_result
            FROM {self.table_name}
            WHERE crossover_rate == {crossover_rate}
            GROUP BY instance_file, crossover, crossover_name, crossover_rate;'''
        df = pd.read_sql(query, db_connection)

        # Lista de DataFrames, onde cada dataframe e de um arquivo de instancia especifico
        dataframes = [ df.loc[df['instance_file'] == file_] for file_ in self.instance_files]
        
        return dataframes


def get_dbfilename() -> str:
    if len(argv) < 2:
        return input('Insira o nome do arquivo SQLite: ')
    else: return argv[1]


@click.command()
@click.argument('dbfilename')
@click.option('--table', type=str)
@click.option('-I', '--instance-list', multiple=True)
@click.option('--result-column', type=str)
@click.option('-R', '--yrange', nargs=2)
def main(dbfilename, table, instance_list, result_column, yrange):
    # dbfilename = get_dbfilename()
    # problem_data = OptProblemData('setcovering_executions', instance_files=scp_instance_files, result_column='total_costs')

    if len(instance_list) == 0:
        print('Nao pode consultar base sem nehum arquivo de instancia definido. Use -I <arquivo>')
        exit(1)

    problem_data = OptProblemData(table, instance_files=instance_list, result_column=result_column)
    df_list = problem_data.create_dataframes_from_db(dbfilename)

    for df in df_list:
        s = list(set(df['instance_file']))[0]
        print('Criando plot para a instancia', s)
        ax = df.plot.bar(x='crossover_name', y='mean_result', color='r', width=0.2)
        ax.set_title(f'Instancia: {s}')
        ax.grid(True, axis='y', color='gray', linestyle=':')
        if len(yrange) == 2:
            ax.set_ylim([int(yrange[0]), int(yrange[1])])
        pass

    plt.show()
    return

if __name__ == '__main__':
    main()
