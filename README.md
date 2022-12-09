# Árvore Rubro Negra
<p>
Árvore rubro-negra (Red-Black tree) é uma estrutura de dados de programação criada em 1972 com o nome de árvores binárias simétricas. Como as árvores binárias comuns às rubro-negras possuem um conjunto de operações (inserção, remoção, busca), porém são geralmente mais eficientes devido ao fato da rubro-negra estar sempre balanceada. Este balanceamento se dá justamente pela característica que dá nome a árvore, que vem de um bit extra em cada nodo que determina se esta é "vermelha" ou "preta" dentro do conjunto de regras que rege a árvore. Além desde bit, cada nodo também conta com os campos dados do nodo, filho esquerdo do nodo, filho direito do nodo e pai do nodo. 
</p>

<h2>Implementação</h2>
<p> 
  A implementação segue os algoritmos do livro do Cormen, apresentado em sala de aula. Além disso, foi implementada a função que verifica se uma árvore é Rubro-Negra fazendo o cálculo das alturas **negras** das subárvores de cada nó e verifica se essas alturas são iguais. E por fim, possui uma função que conta a quantidade de nós de uma Árvore Rubro-Negra.
</p>

## Testes
<ol>
  <li>Deve-se criar 1.000  Árvores Rubro-Negras.</li>
  <li>Em cada Árvore Rubro-Negra deve-se inserir aleatoriamente 10.000 nós      onde a chave de cada nó está entre 0 e 100.000 (verificar se a Árvore Rubro-Negra possui os 10.000 pelo algoritmo de contagem de nós.</li>
  <li>Após todas as inserções verificar se a árvore continua Rubro-Negra pelo algoritmo de verificaçao.</li>
  <li>Remover 1.000 nós (verificar se a Árvore Rubro-Negra possui os 9.000 nós pelo algoritmo de contagem de nós).</li>
  <li>Após todas as remoções verificar se a árvore continua Rubro-Negra pelo algoritmo de verificação.</li>
</ol>
