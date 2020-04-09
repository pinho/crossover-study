#!/bin/bash
#
# by R. Pinho <ronaldppinho@gmail.com>
#
# Build all the project
# -- check dependencies
# -- generate makefiles
# -- compile it (make)
# -- install (make)
#


function echo_ok() {
    echo -en "\e[38;5;112m:: $1\e[0m"
}

function echo_err() {
    echo -en "\e[38;5;9m:: $1\e[0m"
}

function green_log() {
    echo -e "\e[38;5;112m::\e[0m $1"
}

function install_from_github() {
    file=$1;
    echo -e ":: Baixando $file...";
    wget -c https://github.com/pinho/scpxx/archive/v1.0.2.zip -O scpxx.zip > /dev/null;
    unzip scpxx.zip > /dev/null;
    rm scpxx.zip;
    mkdir scpxx-1.0.2/build && cd scpxx-1.0.2/build
    echo -e ":: Compilando o projeto $file...";
    cmake .. > /dev/null;
    echo -e ":: Instalando $file...";
    make install > /dev/null;
}

function check_include() {
    green_log "Procurando por $1 ..."
    if [[ -e "/usr/local/include/$1" || -e "/usr/include/$1" ]]; then
        echo_ok " [encontrado]\n"
    else
        echo_err " [não-encontrado]\n"

    fi
}

function cmake_build() {
    mkdir -p build
    cd build
    cmake ..
}

# function ninja_build() {}

## Starting the running

green_log "Checando dependências..."

check_include scpxx
check_include paradiseo
check_include doctest