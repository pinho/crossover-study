# Usando Docker Multi-stage build resource.
# As compilações de vários estágios são um novo recurso que requer o Docker 17.05
# ou superior no daemon e no cliente. As compilações de vários estágios são úteis
# para quem luta para otimizar os Dockerfiles, mantendo-os fáceis de ler e manter.
FROM ronalddpinho/cpp-build-base AS build

RUN apt-get update -y
RUN apt-get install -y wget unzip libvsqlitepp-dev libboost-dev

WORKDIR /usr/src

# Copiar os arquivos do projeto para o contêiner
COPY . .

# Executar o script para instalar dependências a partir do github
# RUN bash scripts/instd.sh

# Instalar e contruir dependências externas (ParadisEO)
RUN mkdir -p build/paradiseo
RUN cmake -B build/paradiseo \
    -DEO_ONLY=ON \
    -DCMAKE_INSTALL_PREFIX=. \
    include/paradiseo-master
    
RUN make -C build/paradiseo install

# Compilação do projeto completo
RUN cmake -B build .
RUN make -C build install


# Imagem de produção será contruída a parte e copia somente o necessário da
# imagem de build para execuções, como os binários, bibliotecas e arquivos
# de instâncias para testes
FROM ubuntu:latest

RUN apt-get update -y
RUN apt-get install -y libvsqlitepp-dev

# Copia somente os executáveis gerados na imagem de build
COPY --from=build /usr/local/bin/run /usr/bin
COPY --from=build /usr/local/bin/maxclique /usr/bin
COPY --from=build /usr/local/bin/multiknap /usr/bin
COPY --from=build /usr/local/bin/steintree /usr/bin
COPY --from=build /usr/local/bin/setcovering /usr/bin

# Coiando arquivos de instância para a imagem em /data/in e definindo o
# diretório "data" como um volume. Esse diretório deve ser usado para armazenar
# os arquivos de banco de dados (.sqlite) das execuções
# COPY --from=build /usr/src/data/mcp /data/mcp
COPY --from=build /usr/src/data/mkp /data/mkp
COPY --from=build /usr/src/data/mwcp /data/mwcp
COPY --from=build /usr/src/data/stp /data/stp
COPY --from=build /usr/src/data/scp /data/scp

VOLUME [ "/db" ]
# OBS: O ponto de montagem no host deve ser especificada ao subir o contêiner
