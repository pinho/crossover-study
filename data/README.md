# Arquivos de instâncias

---
## Cobertura de Conjuntos

Arquivo      | No. Elementos (linhas) | No. Subconjuntos (colunas)  
-------------|------------------------|---------------------------
`scp41.txt`  | 200 | 1000
`scp42.txt`  | 200 | 1000
`scp43.txt`  | 200 | 1000
`scp44.txt`  | 200 | 1000
`scp51.txt`  | 200 | 2000
`scp52.txt`  | 200 | 2000
`scp53.txt`  | 200 | 2000
`scp53.txt`  | 200 | 2000


---
## Clique Máximo

Dado um grafo `G = (V, E)`, um clique `C = (Vc, Ec)` de `G` é subgrafo completo de `G`,
ou seja, um subgrafo onde todos os vértices de `Vc` estão conectados entre si. O Problema
do Clique Máximo com Pesos define 0.073valores para cada vértices, e o objetivo é encontrar um
clique cuja soma dos pesos de seus vértices seja a maior possível.

Arquivo            | Vértices |  Arestas  | Densidade do grafo
-------------------|----------|-----------|--------------------
`C250.9.clq`       |      250 |    27 984 | 0.9
`C500.9.clq`       |      500 |   112 332 | 0.9
`c-fat500-1.clq`   |      500 |     4 459 | 0.035
`c-fat500-2.clq`   |      500 |     9 139 | 0.073
`C1000.9.clq`      |     1000 |   450 079 | 0.901
`san1000.clq`      |     1000 |   250 500 | 0.501
`C2000.5.clq`      |     2000 |   999 836 | 0.5
`C2000.9.clq`      |     2000 | 1 799 532 | 0.9

**Novas execuções** - 16/11/2020

Arquivo            | Vértices |  Arestas  | Densidade do grafo
-------------------|----------|-----------|--------------------
`MANN_a81`         |     3321 | 5 506 380 | 0.9988
`MANN_a45`         |     1035 |   533 115 | 0.9962
`hamming6-2`       |     1024 |   518 656 | 0.9902
`hamming6-4`       |     1024 |   434 176 | 0.8289
`p-hat1000-3`      |     1000 |   371 746 | 0.7442


---
## Árvore de Steiner

Todo e qualquer arquivo de definição de um grafo para testes com o poblema da
árvore de Steiner deve estar na formatação definida pelos arquivos da OR-Library.

Arquivo         | Vértices (de Steiner) | Arestas
----------------|-----------------------|--------
`steinc4.txt`   | 500  (125)            | 625
`steinc5.txt`   | 500  (250)            | 625
`steind3.txt`   | 1000 (167)            | 1250
`steind4.txt`   | 1000 (250)            | 1250
`steind5.txt`   | 1000 (500)            | 1250
`steine3.txt`   | 2500 (250)            | 3125
`steine4.txt`   | 2500 (625)            | 3125
`steine5.txt`   | 2500 (1250)           | 3125

---
## Mochila Mutidimensional

Status | Arquivo     | Número de variáveis (itens) | Número de restrições (mochilas)
-------|-------------|-----------------------------|--------------------------------


---
## Fontes de arquivos-teste

- **OR-Library**, por Beasley. Disponível em: http://people.brunel.ac.uk/~mastjjb/jeb/orlib/files

- **DIMACS Challenges**. Disponível em: http://dimacs.rutgers.edu/programs/challenge
