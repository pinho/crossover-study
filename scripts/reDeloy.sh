#!/bin/bash

# Apagar a pasta build se existir
rm -rfv build

# recriar a pasta build
mkdir build 
cd build

# Gerar arquivos de bild com cmake
cmake -DCMAKE_INSTALL_PREFIX=$HOME/.local ..

# Compilar e instalar
make -j $(nproc)
make install

cd ..

