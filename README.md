# libgraphviz
Biblioteca para interface com graphviz.

## Importante:
Para que a biblioteca funcione corretamente, é necessário certificar-se de que:
- **Windows:** O graphviz está instalado e a variável de sistema **_PATH_** está preenchida com o caminho para a execução do *dot*;
- **Linux (Distribuições baseadas em Debian):** O graphviz está instalado. É possivel obter a última versão com o comando *apt-get install graphviz*.

#### Geração dos Arquivos
Os arquivos .gv e .png gerados pelas rotinas descritas mais abaixo serão encontrados no diretório gradosgerados no home do usuário logado no SO. É necessário que o programa que implemente a biblioteca tenha permissão para a criação do diretório/arquivos dentro do home. 

## Estruturas de Dados Suportadas
A Interface com o graphviz é feita utilizando-se das seguintes Estruturas de Dados:
- **Matriz de Adjacência**: Vetor short int bidimencional de tamanho n por n, onde n é o número de vértices no grafo;
- **Lista de Adjacência**: Lista simplificada com estrutura ```struct adj_list { int cod, struct adj_list * prox }``` onde código corresponte ao número do vértice.

## Chamadas
É necessário, antes de mais nada, realizar a chamada da rotina ```void fill_colors( )``` para que uma estrutura hash seja preenchida com o código das cores e o codigo de vértice respectivo.

#### Rotinas Geradoras
Para que se realize a geração do grafo a partir de uma estrutura de dados previamente preenchida, é necessário chamar a rotina ```void gera_graphviz_matriz(int, short int[][], char\*)```, passando respectivamente o número de vértices, a matriz de adjacência e a título do grafo (pode ser qualquer string), ou realizar a chamada da rotina ```void gera_graphviz_matriz(int, struct adj_list[], char\*)```, que tem basicamente a mesma estrutura, só substituindo a matriz de adjacência por um array de lista de adjacência (um registro para cada vértice). 
