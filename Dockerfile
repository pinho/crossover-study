# FROM ronalddpinho/cpp-build-base
FROM ubuntu:latest

RUN apt-get update -y
RUN apt-get install -y gcc build-essential cmake wget unzip doxygen libboost-graph-dev libvsqlitepp-dev

WORKDIR /app

COPY ./scripts/instd.sh .
RUN bash instd.sh

COPY . .

COPY ./instances/scp /data/scp
COPY ./instances/clique /data/mcp
COPY ./instances/multiknap /data/mkp

RUN mkdir build && cd build && cmake ..
RUN cd /app/build && make && make install
