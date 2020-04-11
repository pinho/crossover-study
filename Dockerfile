FROM ubuntu:latest

LABEL maintainer="ronaldd"
LABEL version="0.1"

RUN apt-get update -y &&\
 apt-get install -y curl wget unzip gcc build-essential cmake doxygen libboost-graph-dev

WORKDIR /app

COPY . .

RUN bash install_dependencies.sh
