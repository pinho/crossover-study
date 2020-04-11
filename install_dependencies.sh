#!/bin/bash
#
# @pinho
# Install all dependencies of the project in local machine
# Retrieve libraries from web and install it from sources
# Requires root permissions, run it with sudo or as in root user
if [ $EUID != 0 ]; then
    echo "Run this script with sudo."
    exit 2
fi

# Console colors -- xterm
declare -A COLORS
COLORS[R]="\e[38;5;9m"
COLORS[G]="\e[38;5;112m"
COLORS[OFF]="\e[0m"

# Check if needed tools is installed
check_tool() {
    if [ -f "/usr/bin/$1" ]; then
        echo "$1 ok" > /dev/null
    else
        echo "Que embaraçoso. Preciso do $1, mas não o encotrei na sua máquina"
        echo "Seria legal pra mim se você instalasse ;)"
        exit 1
    fi
}
check_tool unzip
check_tool wget
check_tool cmake

# Download links
declare -A LINKS
LINKS[paradiseo]='https://github.com/pinho/paradiseo/archive/master.zip'
LINKS[yaml-cpp]='https://github.com/jbeder/yaml-cpp/archive/yaml-cpp-0.6.3.zip'
LINKS[doctest]='https://github.com/onqtam/doctest/archive/2.3.7.zip'

# Deps to install
declare -a DEP_ARRAY


#------------------------------------------------------------------------------#
# Functions

function echo_ok() {
    echo -en "${COLORS[G]}$1${COLORS[OFF]}"
}

function echo_err() {
    echo -en "${COLORS[R]}$1${COLORS[OFF]}"
}

function default_log() {
    echo -en "${COLORS[G]}:: ${COLORS[OFF]}$1"
}


function check_include() {
    default_log "Procurando por $1..."
    if [[ -e "/usr/local/include/$1" || -e "/usr/include/$1" || -e "/usr/bin/$1" ]]; then
        echo_ok "\t[encontrado]\n"
    else
        echo_err "\t[não-encontrado]\n"
        DEP_ARRAY+=("$1")
    fi
}

function download() {
    DEP=$1
    default_log "Baixando ${COLORS[G]}$DEP${COLORS[OFF]}...\n"
    wget -c "${LINKS[$DEP]}" -O "/tmp/$DEP.zip" > /dev/null
}

# Install boost libraries
function install_boost() {
    if [ -f '/etc/arch-release' ]; then
        default_log "Instalando boost com o pacman\n"
        pacman -S --noconfirm boost > /dev/null
    elif [ -f '/etc/debian_release' ]; then
        default_log "Instalando boost com apt-get\n"
        apt-get install -y libboost-dev > /dev/null
    fi
}

function install() {
    ARG=$1
    unzip "/tmp/$ARG.zip" -d "$ARG" > /dev/null
    default_log "Arquivo $ARG.zip desempacotado\n"
    cd "/tmp/$ARG"
    if [ "$ARG" == "paradiseo" ]; then
        cd paradiseo-master/
    elif [ "$ARG" == "yaml-cpp" ]; then
        cd yaml-cpp-yaml-cpp-0.6.3/
    elif [ "$ARG" == "doctest" ]; then
        cd doctest-2.3.7/
    fi
    cmake . > /dev/null
    default_log "Compilando $ARG...\n"
    make > /dev/null
    default_log "Instalando...\n"
    make install > /dev/null
    cd /tmp
    rm -r $ARG.zip $ARG
}

check_all() {
    check_include 'paradiseo'
    check_include 'yaml-cpp'
    check_include 'doctest'
    check_include 'boost/graph'
}

SOURCE_DIR=${PWD}
cd /tmp

echo 'Checando dependências...'
check_all

echo 'Obtendo dependências...'
for dep in ${DEP_ARRAY[*]}; do
    if [ $dep == 'boost/graph' ]; then
        install_boost
    else 
        download $dep
    fi
done
default_log "[${DEP_ARRAY[*]}] obtidos.\n"

echo 'Instalando dependências...'
# Instalando e Removendo arquivos e pastas geradas
for D in ${DEP_ARRAY[*]}; do
    if [ $D == 'boost/graph' ]; then
        continue
    fi
    install $D
    default_log "${COLORS[G]}$D instalado${COLORS[OFF]}\n"
done

cd $SOURCE_DIR
exit 0