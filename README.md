# libgraphviz
Biblioteca para interface com graphviz.

## Estruturas de Dados Suportadas
A Interface com o graphviz é feita utilizando-se das seguintes Estruturas de Dados:
- **Matriz de Adjacência**: Vetor short int bidimencional de tamanho n por n, onde n é o número de vértices no grafo;
- **Lista de Adjacência**: Lista simplificada com estrutura **_struct adj_list { int cod, struct adj_list * prox }_**, onde código corresponte ao número do vértice.

## Chamadas
É necessário, antes de mais nada, realizar a chamada da rotina **_void fill_colors( )_** para que uma estrutura hash seja preenchida com o código das cores e o codigo de vértice respectivo.

#### Rotinas Geradoras
Para que se realize a geração do grafo a partir de uma estrutura de dados previamente preenchida, é necessário chamar a rotina **_void gera_graphviz_matriz(int, short int[][], char*)_**, passando respectivamente o número de vértices, a matriz de adjacência e a título do grafo (pode ser qualquer string), ou realizar a chamada da rotina **_void gera_graphviz_matriz(int, struct adj_list[], char*)_**, que tem basicamente a mesma estrutura, só substituindo a matriz de adjacência por um array de lista de adjacência (um registro para cada vértice). 
