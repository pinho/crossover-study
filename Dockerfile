FROM ronalddpinho/cpp-build-base

# Dependências
RUN apt-get install -y unzip doxygen libvsqlitepp-dev libboost-graph-dev

COPY ./install_dependencies.sh .
RUN bash install_dependencies.sh

WORKDIR /app
COPY . .

RUN mkdir build && cd build && cmake -DINSTALL_HEADERS=ON ..
RUN cd /app/build && make && make install
