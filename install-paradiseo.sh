#!/bin/sh
#
# Esse script baixa o codigo-fonte e instala o ParadisEO framework a partir
# da branch master do repositorio oficial no Github.
# - R. Pinho. <ronaldppinho@gmail.com>

gray="\e[38;5;245m"
red="\e[38;5;9m"
green="\e[38;5;82m"
reset="\e[0m"

DEPS=(wget unzip cmake)

runcmd() {
  comando=$1
  echo -e "$ $comando $gray"
  $comando
  echo -e "$reset"
}

for d in ${DEPS[@]}; do
  if [[ -f /usr/bin/$d ]]; then
    echo -e "${gray}[ ${green}OK ${gray}] $d foi encontrado${reset}"
  else
    echo -e "Garanta que todos esses progrmas estejam instalados:\n- ${DEPS[@]}"
    exit 1
  fi
done

# Baixa o arquivo direto da branch master 
runcmd 'wget -c https://github.com/nojhan/paradiseo/archive/master.zip -O paradiseo.zip'

# Desempacota e entra no diretorio
if [[ -f paradiseo.zip ]]; then
  runcmd 'unzip paradiseo.zip'
  runcmd 'cd paradiseo-master'
  runcmd 'pwd'
else
  echo -e "${red}Arquivo paradiseo.zip nao foi criado${reset}"
  exit 1
fi

# Configurando os Makefiles e inicia a compilacao
runcmd 'cmake -DEO_ONLY=ON .'

if [ $EUID -eq 0 ]; then
  runcmd 'make install'
else
  runcmd 'sudo make install'
fi

cd ..
runcmd 'pwd'
runcmd 'rm -vr paradiseo.zip paradiseo-master'

exit 0
