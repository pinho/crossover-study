# Crossovers Comparison

![Actions Status](https://github.com/pinho/crossover-research/workflows/C++%20CI/badge.svg)

Comparação de Opeardores de crossover em Algoritmos Genéticos aplicando a 
alguns problemas de otimização combinatória bem conhecidos.

- [Instalando dependências](#Instalando-dependências) (Linux)
- [Compilando o projeto](#Compilando-o-projeto)
- [Arquivos gerados](#arquivos-gerados)
- [Utilitários Python](#Utilitários-python)

## Instalando dependências

### Arch Linux

```sh
% sudo pacman -S --ignore pacaur cmake wget unzip doxygen boost boost-libs vsqlite++ 

% pacaur -S doctest

% sudo chmod +x instd.sh

% sudo ./instd.sh
```

### Debian

```sh
% sudo apt-get update

% sudo apt-get install wget doxygen unzip cmake libboost-graph-dev doctest-dev libvsqlitepp-dev

% sudo chmod +x instd.sh

% sudo ./instd.sh
```

O script `instd.sh` baixa e instala outras dependências a partir do código fonte
usando `wget`, `unzip` e `cmake`, logo é independente de distribuição Linux e
gerenciador de pacotes.

## Compilando o projeto

Tenha certeza de ter o CMake instalado na versão 3.6+. Use o comando
`cmake --version` para verificar.

```sh
% mkdir build && cd build
% cmake .. -DCMAKE_INSTALL_PREFIX=..
% make
% make install
```

Projeto compilado! :)

Teste:
```
% ./bin/ga4scp -f instances/set-covering/scp44.txt
```

## Arquivos gerados

### Executáveis

Com a compilação do projeto, é gerado um arquivo executável para cada problema implementado.

`ga4scp` executa o algoritmo genético para o problema da cobertura de conjuntos.

`ga4maxclique` executa o algoritmo genético para o problema do clique máximo.

`ga4steintree` executa o algoritmo genético para o problema da árvore de Steiner.

`ga4multiknap` executa o algoritmo genético para o problema da mochila multidimensional.

## Utilitários Python

...

## License

This work is licensed under
[CC BY-NC-SA](https://creativecommons.org/licenses/by-nc-sa/4.0/)
&copy; Ronaldd Pinho
