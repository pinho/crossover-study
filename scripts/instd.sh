#!bin/bash
#
# INSTall Dependencies
#
# Este script instala softwares necessários para a compilação e/ou execução do
# projeto. Precisa de permissões de superuser para instalar pacotes e escrever
# em diretórios protegidos. Os projetos serão baixados e instalados a partir do
# códigos fonte. São:
# ParadisEO framework: http://paradiseo.gforge.inria.fr/
# Biblioteca SCPxx: https://github.com/pinho/scpxx/
#
# written by Ronaldd Pinho <ronaldppinho@gmail.com>

if [[ $EUID != 0 ]]; then
  echo -e "Run it as superuser"
  exit 1
fi

# xterm colors
COLOR="\e[38;5;49m"
OFF="\e[0m"

# Log file
logf='/tmp/instd.log'
rm -f $logf

# cmake specs
EO_ONLY='-DEO_ONLY=ON'
CMAKE_INSTALL_PREFIX=$PWD
CMAKE_FLAGS="-DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} -DCMAKE_BUILD_TYPE=Release"

# links to download
declare -A LINKS
LINKS['scpxx']='https://github.com/pinho/scpxx/archive/master.zip'
LINKS['paradiseo']='https://github.com/nojhan/paradiseo/archive/master.zip'

run() {
    CMD=$1
    echo -e "> ${COLOR}${CMD}${OFF}"
    $CMD >> /tmp/instd.log 2>&1

    if [ $? != 0 ]; then
        echo -e "[\e[38;5;1mErr\e[0m] Último comando finalizou sem êxito."
        echo -e "Veja o log em $logf"
        exit $?
    fi
}

getAndInstall() {
    package=$1

    # Download
    echo -e "Baixando código fonte de ${package} do github (arquivo zip)"
    zipfile="/tmp/${package}.zip"
    run "wget -c ${LINKS[$package]} -O ${zipfile}"
    # $CMD > $logf 2>&1

    # Compile and install
    echo -e "Desempacotando arquivo $package.zip"
    run "unzip $zipfile -d /tmp/$package"

    echo -e "Compilando $package"
    run "cd /tmp/$package/$package-master/"
    
    cmake_command="cmake . ${CMAKE_FLAGS}"
    if [ $package == 'paradiseo' ]; then
        run "$cmake_command $EO_ONLY"
    else 
        run "$cmake_command"
    fi
    run "make install"

    echo "Removendo arquivos gerados"
    run "rm -rv $zipfile /tmp/$package"
}

getAndInstall 'scpxx'
getAndInstall 'paradiseo'

echo -e "\nVeja o log dos comandos em $logf"
exit 0
