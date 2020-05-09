FROM ronalddpinho/cpp-build-base AS build

WORKDIR /app
COPY . .

# Dependências
RUN apt-get install -y unzip doxygen
RUN bash install_dependencies.sh

# Compilar todo o projeto e instalar em /usr/local/bin
#RUN mkdir build && cd build && cmake ..
#RUN make
#RUN make install

COPY ./instances/set-covering/* /data/scp
COPY ./instances/clique/dimacs/* /data/maxclq
COPY . .

