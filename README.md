# Crossovers Comparison

![Actions Status](https://github.com/pinho/crossover-research/workflows/C++%20CI/badge.svg)

Comparação de Opeardores de crossover em Algoritmos Genéticos aplicando a 
alguns problemas de otimização combinatória bem conhecidos.

## How to Build

Tenha certeza de ter o CMake instalado na versão 3.6+;

Use o script `install_dependencies.sh` para instalar dependências (bibliotecas e frameworks) necessárias para compilar o projeto:

```sh
% sudo ./install_dependencies.sh
```

OBS: É necessário ter instalado alguns pacotes básicos: `git`, `wget`, `zip`/`unzip`, `doxygen`(opcional).

O script baixará instalará os seguintes softwares:
- ParadisEO framework
- Yaml-Cpp
- Boost Graph Library

Tome um café e aguarde ;)

Com todas as dependências instaladas localmente, gere os Makefiles usando cmake:

```sh
% mkdir build && cd build # recomendado para manter o diretório do projeto limpo

% cmake .. [-DINSTALL_HEADERS=ON|OFF]

% make
```

OBS: A opção `INSTALL_HEADERS` inclui as regras de instalação dos arquivos de cabeçalho nos Makefiles, que instala arquivos no diretório de instalação padrão (`/usr/local/`);

O Diretório de instalação pode ser configurado através da opção `CMAKE_INSTALL_PREFIX` com

```sh
% cmake -DCMAKE_INSTALL_PREFIX=</diretorio/de/instalacao>
```

Após isso, o projeto estará compilado, e os executáveis, arquvos de biblioteca (e os arquivos de cabeçalho) instalados localmente.

## Programas

Com a compilação do projeto, é gerado um arquivo executável para cada problema implementado.

`ga4scp` executa o algoritmo genético para o problema da cobertura de conjuntos.

`ga4maxclique` executa o algoritmo genético para o problema do clique máximo.

...


## License

This work is licensed under
[CC BY-NC-SA](https://creativecommons.org/licenses/by-nc-sa/4.0/)
&copy; Ronaldd Pinho
