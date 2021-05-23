import logging
from argparse import ArgumentParser
from sqlite3 import Connection
from functions import plot_crossover_boxplots

FORMAT = '[%(asctime)-15s] %(message)s'
logging.basicConfig(format=FORMAT)
logger = logging.getLogger(__name__)
logger.info('Configuring queries on database')

parser = ArgumentParser(description='Plot and generate graphs in image files')
parser.add_argument('dbfilename', action='store', help='Database file to use')
parser.add_argument('--mcp', action='store_true', default=False, help='Plot for maximum clique problem')
parser.add_argument('--mkp', action='store_true', default=False, help='Plot for multidimensional knapsack')
parser.add_argument('--scp', action='store_true', default=False, help='Plot for set covering problem')
parser.add_argument('--stp', action='store_true', default=False, help='Plot for Steiner tree problem')

MCP_TABLENAME = 'maxclique_executions'
MKP_TABLENAME = 'mknap_executions'
SCP_TABLENAME = 'setcovering_executions'
STP_TABLENAME = 'steiner_executions'

MCP_INSTANCE_FILES = ['C1000.9.clq']
MKP_INSTANCE_FILES = ['mknapcb31.txt']
SCP_INSTANCE_FILES = ['scp41.txt', 'scp42.txt', 'scp43.txt', 'scp44.txt']
STP_INSTANCE_FILES = ['steind5.txt', 'steind10.txt', 'steind15.txt']

if __name__ == '__main__':
  args = parser.parse_args()
  con = Connection(args.dbfilename)

  num_figures_generated = 0
  figures = {} # key = name for file; value = Figure object
  query_config = {} # key = tablename; value = list of instances
  if args.mcp: query_config[MCP_TABLENAME] = MCP_INSTANCE_FILES
  if args.mkp: query_config[MKP_TABLENAME] = MKP_INSTANCE_FILES
  if args.scp: query_config[SCP_TABLENAME] = SCP_INSTANCE_FILES
  if args.stp: query_config[STP_TABLENAME] = STP_INSTANCE_FILES

  # print(query_config)
  for table in query_config:
    for instance in query_config[table]:
      try:
        fig, _ = plot_crossover_boxplots(con, table, instance=instance)
        instance_no_ext = instance.split('.')[0]
        figname = f'{table}__{instance_no_ext}.svg'
        logger.debug('Try generate {figname}')
        fig.savefig(figname, transparent=True)
      except:
        logger.warning(f"Didn't generate figure for table='{table}' and instance_file='{instance}'. [SKIP]")
        pass
      pass
  con.close()
  logger.info(f'Finished. Number of figures is {len(figures)}')
