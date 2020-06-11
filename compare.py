#!/bin/python

import click, time
import pyutils

@click.command()
@click.option('-c', '--config', default='config.yml', show_default=True,
              help='Define o arquivo de configuração dos parâmetros')
@click.option('-n', '--num', default=1, show_default=True, 
              help='Número de execuções para todas as combinações')
@click.option('--db', default='default.db', show_default=True, 
              help='Define o arquivo .db para salvar os dados')
def main(config, num, db):
    if db is None:
        click.echo("Arquivo .db não foi definido. Os dados das execuções não serão salvos")

    conf = pyutils.ConfigFile(config)
    print(f'{num*conf.num_combinations} chamadas serão executadas')

    r = pyutils.Runner(conf)

    begin = time.time()
    r.run(num, db)
    end = time.time()

    print(f'\nFinalizado')
    print(f'Todas as chamadas levaram um total de {round(end-begin, 3)} segundos em execução')



if __name__ == "__main__":
    try:
        main()
    except RuntimeError as e:
        print(e)