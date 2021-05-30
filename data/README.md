# Arquivos de instâncias

As instâncias usadas para os estudos estão localizadas no diretório `instances` e organizadas
em subpastas nomeadas com as siglas dos problemas escolhidos para a aplicação dos estudos.
Foi definido que seriam usadas 4 instâncias para cada problema de otimização e que essas
instâncias buscariam incluir problemas de mais de um dimensão para não restringir demais os
estudos a um tamanho de instância.

Com isso, foram escolhidos 4 instâncias que foram obtidas de bases de dados conhecidas como a
_OR-Library_ e os problemas de clique máximo do _DIMACS_. As tabelas abaixo mostram as
informações sobre as instâncias escolhidas para cada problema de otimização. A árvore de
diretórios de arquivos de problemas ficou definida como a seguinte:

```text
data/instances
├── mkp
│   ├── mknapcb51.txt
│   ├── mknapcb61.txt
│   ├── mknapcb81.txt
│   └── mknapcb91.txt
├── mwcp
│   └── C2000.5.clq
├── scp
│   ├── scp41.txt
│   ├── scp42.txt
│   ├── scp51.txt
│   └── scp52.txt
└── stp
    ├── steind10.txt
    ├── steind15.txt
    ├── steine4.txt
    └── steine10.txt
```

---
## Cobertura de Conjuntos

Arquivo      | No. Elementos (linhas) | No. Subconjuntos (colunas)  
-------------|------------------------|---------------------------
`scp41.txt`  | 200 | 1000
`scp42.txt`  | 200 | 1000
`scp51.txt`  | 200 | 2000
`scp52.txt`  | 200 | 2000


---
## Clique Máximo

Dado um grafo `G = (V, E)`, um clique `C = (Vc, Ec)` de `G` é subgrafo completo de `G`,
ou seja, um subgrafo onde todos os vértices de `Vc` estão conectados entre si. O Problema
do Clique Máximo com Pesos define 0.073valores para cada vértices, e o objetivo é encontrar um
clique cuja soma dos pesos de seus vértices seja a maior possível.

Arquivo            | Vértices |  Arestas  | Densidade do grafo
-------------------|----------|-----------|--------------------
`C250.9.clq`       |      250 |    27 984 | 90%
`C500.9.clq`       |      500 |   112 332 | 90%
`c-fat500-1.clq`   |      500 |     4 459 | 3,5%
`c-fat500-2.clq`   |      500 |     9 139 | 7,3%
`C1000.9.clq`      |     1000 |   450 079 | 90,1%
`san1000.clq`      |     1000 |   250 500 | 50,1%
`C2000.5.clq`      |     2000 |   999 836 | 50%
`C2000.9.clq`      |     2000 | 1 799 532 | 90%
`MANN_a81`         |     3321 | 5 506 380 | 0.9988
`MANN_a45`         |     1035 |   533 115 | 0.9962
`hamming6-2`       |     1024 |   518 656 | 0.9902
`hamming6-4`       |     1024 |   434 176 | 0.8289
`p-hat1000-3`      |     1000 |   371 746 | 0.7442


---
## Árvore de Steiner

Todo e qualquer arquivo de definição de um grafo para testes com o poblema da
árvore de Steiner deve estar na formatação definida pelos arquivos da OR-Library.

Arquivo         | Steiner + Terminais | Total de vértices | Total de Arestas
----------------|---------------------|-------------------|------------------
`steind10.txt`  | 500 + 500           | 1000              | 2000
`steind15.txt`  | 500 + 500           | 1000              | 5000
`steine4.txt`   | 625 + 1875          | 2500              | 3125
`steine10.txt`  | 1250 + 1250         | 2500              | 5000

---
## Mochila Mutidimensional

Arquivo      | Número de itens (variáveis) | Número de mochilas (restrições)
-------------|-----------------------------|---------------------------------


---
## Fontes de arquivos-teste

- **OR-Library**, por Beasley. Disponível em: http://people.brunel.ac.uk/~mastjjb/jeb/orlib/files

- **DIMACS Challenges**. Disponível em: http://dimacs.rutgers.edu/programs/challenge
