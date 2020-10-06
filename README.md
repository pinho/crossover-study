# Crossovers Operators Comparisons

![Actions Status](https://github.com/pinho/crossover-research/workflows/C++%20CI/badge.svg)

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

<!-- TODO: Link para a OR-ibrary -->
Os quatro problemas foram implementados e executados usando instâncias de
problemas obtidas da [OR-Library](http://people.brunel.ac.uk/~mastjjb/jeb/info.html)
e da [networkrepository.com](https://networkrepository.com)

## Sumário

* [Instalando dependências](#Instalando-dependências) (Linux)
* [Compilando o projeto](#Compilando-o-projeto)
* [Executar os binários](#executando)
* [Imagem Docker](#imagem-docker)

## Instalando dependências externas

> OBS: O projeto foi desenvolvido e requer um ambiente Linux.

### Arch Linux

```sh
sudo pacman -Sy --ignore cmake wget unzip doxygen boost boost-libs vsqlite++
```

### Debian

```sh
sudo apt-get update
sudo apt-get install cmake wget unzip doxygen libboost-graph-dev libvsqlitepp-dev
```

<!-- O script `instd.sh` baixa e instala outras dependências a partir do código fonte -->
<!-- usando `wget`, `unzip` e `cmake`, logo é independente de distribuição Linux e -->
<!-- gerenciador de pacotes. -->

### ParadisEO

O ParadisEO é usado como submódulo (afinal, quem precisa de monorepo), o
repositório do ParadisEO é referenciado no caminho `include/paradiseo`.
O projeto também usa o CMake para confifurar a compilação porém usa algumas
definições de diretórios raíz do projeto que fazem com a compilação do ParadisEO
não possa ser incluída diretamente pelo `CMakeLists.txt` do diretório raíz desse
projeto (_crossover-study_). Portanto, é necessário compilar o ParadisEO
separadamente:

```sh
# pwd = **/crossover-study

# Cria um diretório para os arquivos de build
mkdir -p build/paradiseo

# Configura a compilação
cmake -B build/paradiseo -DEO_ONLY=ON -DCMAKE_INSTALL_PREFIX=. include/paradiseo-master

# Compila o ParadisEO
make -C build/paradiseo
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

_(Necessário ter o Docker instalado)._

Alvos para artefatos docker são configurados para fazer *build* da imagem docker
e criar o volume.

A aplicação fornece um `Dockerfile` para construção de uma imagem docker para
execução do algoritmo. O docker permite manipular e limitar recursos de hardware
para os contêineres. 

Se o Docker estiver instalado no computador o comando cmake irá criar um alvo
para a build da imagem. Para construir a imagem padrão, use:

> OBS: Requer o Docker instalado.
>
> Se o Docker for encontrado na máquina os alvos `image` e `volume` serão
> configurados. Porém, se não for encontrado, os alvos não serão configurados e
> os comandos abaixo não funcionarão.

```console
% sudo make image
% sudo make volume
```

## License

This work is licensed under
[CC BY-NC-SA](https://creativecommons.org/licenses/by-nc-sa/4.0/)
&copy; Ronaldd Pinho
