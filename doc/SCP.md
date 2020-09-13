# Problema da Cobertura de Conjuntos

Dados um conjunto de `N` elementos (conjunto universo) e um conjunto de `M`
subconjuntos que estão contidos no conjunto universo onde cada subconjunto
possui um custo associado, o problema consiste em encontrar a combinação de
subconjuntos que unidos possuam (cubram) todos os elementos do conjunto
universo.

As variáveis do problema podem ser representadas por uma matriz de valores
booleanos `NxM` onde as `N` linhas representam os elementos do conjuntos
universo e as `M` colunas representam os subconjuntos. Diz-se que um subconjunto
"cobre" uma linha quando a intersecção `matriz[n][m]` é igual a `"1"`.

É um problema de otimização combinatória NP-Completo bastante conhecido e faz
parte da lista de 21 problemas NP-Completos de Karp. Trata-se de um problema de
minimização restrito, onde o objetivo é minimizar o custo total de todas as
colunas (subconjuntos) escolhidas respeitando a restrição de que todas as linhas
(elementos) devem estar presentes na união de todas as colunas.

## Problemas na implementação

Foi encontrado um problema na implementação desse problema onde a convergência
estava lenta, prematura e longe das melhores soluções. O problema foi resolvido
diminuindo consideravelmente a taxa de mutação. Quando usando uma taxa de
mutação razoável de 5%, 4% ou 3%, o problema com a convergência permanecia,
com a diminuição dessa probabilidade para em torno de 0.02% o algoritmo genético
conseguiu se aproximar muito das soluções ótimas em grandes instâncias com uma
ligeira diferença entre os operadores de cruzamento utilizados, o que mantém a
viabilidade desse estudo.

Outro problema é que o ParadisEO possui duas probabilidades de mutação que devem
ser usadas em conjunto; 1) a *probabilidade de mutação por indivíduos* que
define quantos dos novos indivíduos podem sofrer mutação; 2) a *probabilidade
de mutação por genes* que, seja um indivíduo escolhido para sofrer mutação (com
a primeira probabilidade), define quantos genes podem ser mutados. Isso faz com
que indivíduos muitos grandes (instâncias com muitas colunas) tenham mais genes
mutados de uma só vez. Com isso, os valores para essas probabilidades foram
escolhidos
