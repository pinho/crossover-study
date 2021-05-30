import argparse

parser = argparse.ArgumentParser()
parser.add_argument('filename')

def main():
	args = parser.parse_args()
	if not args.filename:
		print('Faltando o caminho para o arquivo')
		exit(1)

	with open(args.filename, 'r') as f:
		lines = f.readlines()

	try:
		num_vertices, num_edges = [ int(elem) for elem in lines[0].split() ]
		print(f'{num_vertices} vertices no total e {num_edges} arestas')
	except:
		print('Erro ao converter os valores de vertices e arestas')

	steiner_vertices = int(lines[num_edges+1])
	print(f'{steiner_vertices} vertices de Steiner')
	print(f'{num_vertices - steiner_vertices} vertices terminais')

	return

if __name__ == '__main__':
	main()