#!/bin/bash

manageDirs() {
  # Apagar a pasta build se existir
  rm -rfv build
  # recriar a pasta build
  mkdir build 
}

cd build

# flag para nao gerar novamente os Makefiles
if [ $# == 1 ]; then
  if [ $1 == --no-cmake ]; then
    echo 'Pulando geração dos Makefiles'
  fi
else
  manageDirs
  cmake -DCMAKE_INSTALL_PREFIX=$HOME/.local ..
fi

# Compilar e instalar
make -j $(nproc)
make install

cd ..

