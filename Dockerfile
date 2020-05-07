FROM ronalddpinho/cpp-build-base AS build

WORKDIR /usr/src
COPY . .

# Dependências
RUN apt-get install -y unzip doxygen
RUN bash install_dependencies.sh

# Compilar todo o projeto e instalar em /usr/local/bin
RUN cmake . -DCMAKE_INSTALL_PREFIX=/usr/local
RUN make
RUN make install

# Container para execução
FROM ubuntu:bionic

# Copiando os binários do projeto C++
COPY --from=build /usr/src/bin/ /usr/local/bin
COPY --from=build /usr/src/lib/ /usr/local/lib

WORKDIR /usr/app
COPY . .

