# Crossovers Comparison

![Actions Status](https://github.com/pinho/crossover-research/workflows/C++%20CI/badge.svg)

Comparação de Opeardores de crossover em Algoritmos Genéticos aplicando a 
alguns problemas de otimização combinatória bem conhecidos.

- [Build](#Build)
- [Executáveis](#Executáveis)
- [Script start.py](#Script-Start.py)

## Build

Tenha certeza de ter o CMake instalado na versão 3.6+;

Use o script `install_dependencies.sh` para instalar dependências (bibliotecas e frameworks) necessárias para compilar o projeto:

```sh
% sudo ./install_dependencies.sh
```

OBS: É necessário ter instalado alguns pacotes básicos: `git`, `wget`, `zip`/`unzip`, `doxygen`.

O script baixará instalará os seguintes softwares:
- ParadisEO framework
- Boost Graph Library
- [SCPxx](https://github.com/pinho/scpxx)

Tome um café e aguarde ;)

Com todas as dependências instaladas localmente, gere os Makefiles usando cmake:

```sh
% mkdir build && cd build # recomendado para manter o diretório do projeto limpo
% cmake .. -DCMAKE_INSTALL_PREFIX=..
% make
% make install
```

Projeto compilado! :)

Teste:
```
% ./bin/ga4scp -f instances/set-covering/scp44.txt
```

## Executáveis

Com a compilação do projeto, é gerado um arquivo executável para cada problema implementado.

`ga4scp` executa o algoritmo genético para o problema da cobertura de conjuntos.

`ga4maxclique` executa o algoritmo genético para o problema do clique máximo.

`ga4steintree` executa o algoritmo genético para o problema da árvore de Steiner.

`ga4multiknap` executa o algoritmo genético para o problema da mochila multidimensional.

## Script `start.py`

...

## License

This work is licensed under
[CC BY-NC-SA](https://creativecommons.org/licenses/by-nc-sa/4.0/)
&copy; Ronaldd Pinho
