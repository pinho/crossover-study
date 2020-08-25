# Crossovers Comparison

![Actions Status](https://github.com/pinho/crossover-research/workflows/C++%20CI/badge.svg)

Este projeto é resultado da pesquisa conduzida no 
_[Laboratory of Applied Artificial Intelligence](http://laai.ufpa.br)_ (LAAI)
acerca de operadores de cruzamento em algoritmos genéticos (AG) aplicados a
alguns problemas NP-Completos de Karp, problemas clássicos de otimização
combinatória em ciência da computação e pesquisa operacional. O trabalho visa
conhecer mais sobre o efeito dos operadores de crossover mais usados no processo
de busca de um AG no tipo de problema abordado (otimização combinatoria).

- [Instalando dependências](#Instalando-dependências) (Linux)
- [Compilando o projeto](#Compilando-o-projeto)
- [Executando](#executando)
- [Imagem Docker](#imagem-docker)

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
% cmake .. -DCMAKE_INSTALL_PREFIX=../dist
% make -j $(nproc)
% make install

# alvos para artefatos docker
% make image
% make volume
```

Projeto compilado! :)


## Executando

A compilação gera quatro binários executáveis - um para cada problema.
Todos seguem as mesma regras e opções de argumentos para a execução.

Veja as opções usando a flag `--help`

```console
% ./maxclique --help
Problema do Clique Máximo
Use: ./bin/crossoverstudy-mc -f [input-file] [ARGS] ...
ARGS:
  -f, --infile      Arquivo de instância do problema
  -d, --db          Arquivo .db para salvar os dados. Se não definido não salva
  -p, --popsize     Tamanho da população [default = 100]
  -g, --epochs      Número de épocas/gerações [default = 100]
  -x, --crossover   Operador de crossover utilizado com um ID [default = 0]
  -c, --xrate       Taxa de cruzamento (%) [default = 0.8]
  -m, --mrate       Taxa de mutação (%) [default = 0.05]
  -r, --ring        Tamanho do Ring do operador de seleção por torneio determinístico [default = 8]
  -h, --help        Mostra essa lista de opções
```

O único argumento obrigatório é o arquivo de entrada: `-f caminho/para/o/arquivo`

## Imagem Docker

_(Necessário ter o Docker instalado)._

A aplicação fornece um `Dockerfile` para construção de uma imagem docker para
execução do algoritmo. O docker permite manipular e limitar recursos de hardware
para os contêineres. 

Se o Docker estiver instalado no computador o comando cmake irá criar um alvo
para a build da imagem. Para construir a imagem padrão, use:

```console
% sudo make image
% sudo make volume
```

Para executar um comando em um contêiner baseado na imagem da aplicação, use:

```zsh
% docker run -d \
  --rm \
  --name ga_crossover \
  estudos <command>

# Por exemplo

% docker run -d \
  --rm \
  --name ga_crossover \
  estudos \
  crossoverstudy-mc -f /data/in/brock400_4.clq -x 32 --db /data/maxclique.sqlite
```


## Python Starter

> Deve ser executado como superuser

Na pasta `scripts` há um script Python criado para subir um container Docker com
a imagem da aplicação com um comando de algoritmo que pode ser executado `N`
vezes em sequência no mesmo contêiner.

Executar com `--help` para ver as opções:

```console
% sudo ./scripts/execOnContainer.py --help
```

## License

This work is licensed under
[CC BY-NC-SA](https://creativecommons.org/licenses/by-nc-sa/4.0/)
&copy; Ronaldd Pinho
