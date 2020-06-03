# Crossovers Comparison

![Actions Status](https://github.com/pinho/crossover-research/workflows/C++%20CI/badge.svg)

Comparação de Opeardores de crossover em Algoritmos Genéticos aplicando a 
alguns problemas de otimização combinatória bem conhecidos.

- [Instalando dependências](#Instalando-dependências) (Linux)
- [Compilando o projeto](#Compilando-o-projeto)
- [Executando](#executando)
- [Utilitários Python](#Utilitários-python)
    * [Exemplo de execução](#exemplo-de-execução)

## Instalando dependências

### Arch Linux

```sh
sudo pacman -Sy --ignore cmake wget unzip doxygen boost boost-libs vsqlite++ 
sudo bash scripts/instd.sh
```

### Debian

```sh
sudo apt-get update
sudo apt-get install cmake wget unzip doxygen libboost-graph-dev libvsqlitepp-dev
sudo bash scripts/instd.sh
```

O script `instd.sh` baixa e instala outras dependências a partir do código fonte
usando `wget`, `unzip` e `cmake`, logo é independente de distribuição Linux e
gerenciador de pacotes.

## Compilando o projeto

Tenha certeza de ter o `cmake` instalado na versão 3.6+. Use o comando
`cmake --version` para verificar.

```sh
% mkdir build && cd build
% cmake .. -DCMAKE_INSTALL_PREFIX=..
% make -j $(nproc)
% make install
```

Projeto compilado! :)


## Executando

O binário executável é `gastart`, ele executa o algoritmo genético a partir de
um conjunto de parâmetros: tamanho da população, número de gerações, taxas de
cruzamento e mutação, operador de crossover, arquivo de instância, arquivo de
banco de dados para guardar os dados da execução.

Use `gastart --help` para ver as opções

```console
% ./bin/gastart --help
./bin/gastart [problem] -f [input-file] [ARGS]

Problems
  scp - Set Covering Problem
  mcp - Maximum Clique Problem
  mkp - Muldimensional Knapsack Problem
  stp - Steiner Tree Problem

ARGS:
  -d, --db          Define o arquivo .db para salvar os dados. Se não definido não salva
  -f, --infile      Arquivo de instância do problema
  -p, --popsize     Define o tamanho da população
  -g, --epochs      Define o número de épocas/gerações
  -x, --crossover   Define a taxa de cruzamento (%)
  -c, --xrate       Define a taxa de mutação (%)
  -m, --mrate       Define o operador de crossover utilizado com um ID
  -h, --help        Mostra essa lista de opções
```

## Utilitários Python

Um módulo Python simples foi desenvolvido para auxiliar no processo de execução
de muitas chamadas com diferentes combinações de parâmetros. O script
`compare.py` dispara uma sequeência de execuções no sistema usando um arquivo de
configuração para definir os parâmetros que serão combinados bem como o problema
e seu arquivo de instância e o arquivo de banco de dados para amazenamento de
dados de todas as execuções na sequência.

Os arquivos de configurações são do formato [YAML](https://yaml.org). Para um
exemplo, veja [config.yml](config.yml)

### Exemplo de execução

Para executar o script `compare.py`, certifique-se de que o caminho para o
arquivo de instância definido no arquivo yaml existe.

Faça uma cópia da estrutura do banco de dados para outro arquivo:

```console
cp database/model.db exemplo.db
```

Execute o `compare.py` no diretório raíz do projeto:

```console
./compare -n 10 --db exemplo.db
```

O script irá procurar por um arquivo `config.yml` no diretório atual e executará
cada combinação possível do parâmetros definidos no arquivo 10 vezes.

Para usar seu próprio arquivob de configuração use a opção `-c` do script:

```console
./compare -c myOwnConfig.yml -n 10 --db exemplo.db
```

## License

This work is licensed under
[CC BY-NC-SA](https://creativecommons.org/licenses/by-nc-sa/4.0/)
&copy; Ronaldd Pinho
