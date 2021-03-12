![made-with-Cpp](https://img.shields.io/badge/Made%20with-C++-1f425f.svg?style=flat-square)
![Actions Status](https://github.com/pinho/crossover-research/workflows/C++%20CI/badge.svg)

# Crossovers Operators Comparisons

Este projeto é resultado da pesquisa conduzida no 
_[Laboratory of Applied Artificial Intelligence](http://laai.ufpa.br)_ (LAAI)
acerca de operadores de cruzamento em algoritmos genéticos (AG) aplicados a
alguns [problemas NP-Completos de Karp](), problemas clássicos de otimização
combinatória em ciência da computação e pesquisa operacional. O trabalho visa
conhecer mais sobre o efeito dos operadores de crossover mais usados no processo
de busca de um AG no tipo de problema abordado (otimização combinatória).

Os estudos foram executados para os seguintes problemas:
- Árvore de Steiner
- Clique Máximo
- Mochila Multidimensional
- Cobertura de Conjuntos


Os quatro problemas foram implementados e executados usando arquivos de
instâncias obtidas principalmente das bases de dados da
[OR-Library](http://people.brunel.ac.uk/~mastjjb/jeb/info.html)
e do [DIMACS](http://dimacs.rutgers.edu/programs/challenge).


## Sumário

* [Instalando dependências externas](#Instalação-de-dependências-externas)
* [Instalando o ParadisEO](#Instalando-o-ParadisEO)
* [Compilando o projeto](#Compilando-o-projeto)
* [Imagem Docker](#imagem-docker)

## Instalação de dependências externas

Arch Linux:

```sh
sudo pacman -Sy --ignore cmake docker doxygen boost boost-libs vsqlite++
```

Debian:

```sh
sudo apt-get update
sudo apt-get install cmake docker doxygen libboost-graph-dev libvsqlitepp-dev
```

### Instalando o ParadisEO

O ParadisEO é umm framework C++ para computação evolutiva, para que o projeto
seja compilado com sucesso é necessário a instalação do framework e no geral
ele não está presente de forma padrão nos repositórios de gerenciadores de
pacotes das distribuições Linux. Portanto é recomendado fazer a instalação a
partir do código fonte, é só usar os comandos a abaixo:

```sh
wget -c https://github.com/nojhan/paradiseo/archive/master.zip -O paradiseo.zip
unzip paradiseo.zip && cd paradiseo-master
mkdir -p build && cd build
cmake -DEO_ONLY=ON ..
sudo make install
```

## Compilando o projeto

Tenha certeza de ter o `cmake` instalado na versão 3.6+. Use o comando
`cmake --version` para verificar.

```sh
# Compilação do projeto inteiro
cmake -B build .
make -C build

# Compila e instala os binários e libs
make install
```

Projeto compilado! :)

## Imagem Docker

**OBS**: _Necessário ter o Docker instalado e 5GB de espaço em disco para
construir a imagem Docker._

Alvos para artefatos docker são configurados para fazer *build* da imagem docker
e criar o volume.

A aplicação fornece um `Dockerfile` para construção de uma imagem docker para
execução do algoritmo. O docker permite manipular e limitar recursos de hardware
para os contêineres. 

Se o Docker estiver instalado no computador o comando CMake irá criar os seguintes
alvos para a build da imagem e do volume Docker: `image` e `volume`.

> OBS: Requer o Docker instalado.
>
> Se o Docker não for encontrado na máquina os alvos `image` e `volume` não serão
> configurados, logo, os comandos abaixo não funcionarão.

```sh
# use "-C build" se no diretório raíz do projeto
sudo make image 
sudo make volume
```

## Script _experiment.py_

O script `scripts/experiment.py` foi criado para automatizar a inicialização de
execuções em contêineres Docker. É necessário que a imagem `crossoverstudy` e o
volume `studyvol` tenham sido construídos seguindo os passos da
[seção anterior](#Imagem-Docker).

O script usa um arquivo de configuração em formato YAML (_config.yml_) para
definir os argumentos para o comando a ser executado no contêiner. A configuração
permite que se possa passar uma lista de argumentos para uma mesma opção no
arquivo, o script se certificará de criar vários comandos combinando cada
argumento de listas com os argumentos das outras opções criando assim um conjunto
de várias combinações de parâmetros, sendo cada uma executada em um contêiner
diferente.

A opção `-n` define quantas vezes um comando deve ser executado dentro de um
contêiner. Isso é usado para fazer as várias execuções do algoritmo com uma mesma
configuração de parâmetros.

Com a opção `--max-con` o script define um número de contêineres máximo a serem
executados ao mesmo tempo, quando o número total de contêineres escalonados é
maior que o valor dessa opção o script espera até que algum contêiner rodando
termine de executar para então subir um novo. O valor padrão dessa opção é 2.

A opção `--waittime` ou `-t` do script define a quantidade de segundos o script
espera para verificar se há disponibilidade de executar um novo contêiner dado o
número máximo de contêineres permitido.

Uma dica como usar o script:

```console
sudo python scripts/experiment.py "setcovering" -n 50 --waittime 300
```

Para ver as opção use `python scrpits/experiment.py --help`

## License

This work is licensed under
[CC BY-NC-SA](https://creativecommons.org/licenses/by-nc-sa/4.0/)
&copy; Ronaldd Pinho
