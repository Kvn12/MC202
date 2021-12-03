#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INT_MAX 200000
#define PAI(i) ((i-1)/2)
#define F_ESQ(i) (2*i+1)
#define F_DIR(i) (2*i+2)

/*Struct No usada para o grafo e para a fila de prioridades tambem.*/
typedef struct No{
    char nome[50];
    int populacao;
    double dist, centralidade;
    struct No *prox;
    int ind_grafo;
    int apto;
} No;
typedef No * p_no;

/*Struct Grafo que representa o grafo.*/
typedef struct{
    p_no *adj;
    int tamanho;
} Grafo;
typedef Grafo * p_grafo;

/*Struct FP que representa a fila de prioridades.*/
typedef struct {
    No *v;
    int n, tamanho;
} FP; 
typedef FP * p_fp;

int vazia(p_fp fila);
int extrai_minimo(p_fp fila);
int particiona(p_no *vetor, int e, int d);
int procuraIndice(p_fp fila, char nome[50]);
int pegaIndice(p_grafo cidades, char atual[50]);
void troca(No *x, No *y);
void destroiFP(p_fp fila);
void imprimir(p_grafo cidades);
void sobeHeap(p_fp fila, int n);
void destroiLista(p_no listaAdj);
void desceHeap(p_fp fila, int k);
void destroiCidades(p_grafo Cidades);
void quickSort(p_no *vetor, int e, int d);
void insere(p_fp fila, int i, double dist, p_no cidade);
void diminuiprioridade(p_fp fila, int i, double dist);
double prioridade(p_fp fila, int k);
p_fp criar_fprio(int tamanho);
p_fp dijkstra(p_grafo cidades, int s);
p_grafo criaCidades(int qtdCidades);
p_grafo recebeCidades(int qtdCidades);
p_grafo recebeArestas(p_grafo cidades);
p_grafo calcCentralidade(p_grafo cidades);
p_grafo adicionaCidade(p_grafo cidades, int pos, char nome[50], int populacao);
p_grafo adicionaAresta(p_grafo cidades, char cidade_1[50], char cidade_2[50], double dist);

/*Recebe do scanf as informacoes das cidades e insere-as no graf atraves da funcao adicionaCidade.*/
p_grafo recebeCidades(int qtdCidades){
    p_grafo cidades;
    int i, populacao;
    char nome[50];

    cidades = criaCidades(qtdCidades);

    for(i=0;i < qtdCidades;i++){
        scanf("%s %d", nome, &populacao);
        cidades = adicionaCidade(cidades, i, nome, populacao);
    }
    return cidades;
}

/*Recebe do scanf as informacoes das cidades vizinhas e insere-as no grafo atraves da funcao adicionaAresta.*/
p_grafo recebeArestas(p_grafo cidades){
    char cidade_1[50], cidade_2[50];
    double dist;
    while(scanf("%s %s %lf", cidade_1, cidade_2, &dist) != EOF){
        cidades = adicionaAresta(cidades, cidade_1, cidade_2, dist);
    }
    return cidades;
}

/*Calcula a centralidade de cada cidade, com as menores distancias provindas da funcao Dijkstrta
e verifica se uma cidade e apta ou nao para ser capital.*/
p_grafo calcCentralidade(p_grafo cidades){  
    int i, j, populacaoTotal, populacaoAtendida;
    double divisor, dividendo;
    p_fp fila;

    for(i=0;i < cidades->tamanho;i++){ 
        divisor = 0.0; dividendo = 0.0; populacaoTotal = 0; populacaoAtendida = 0; 
        fila = dijkstra(cidades, i);
        for(j=0;j < cidades->tamanho;j++){ 
            populacaoTotal += fila->v[j].populacao;
            if(fila->v[j].dist != (double)INT_MAX){
                dividendo += fila->v[j].dist * fila->v[j].populacao;
                divisor += fila->v[j].populacao;
                populacaoAtendida += fila->v[j].populacao;
            }
        }
        if(populacaoAtendida >= populacaoTotal/2){  
            if(divisor != 0.0){
                cidades->adj[i]->centralidade = (dividendo / divisor);
            }
            cidades->adj[i]->apto = 1;
        }
        else{
            cidades->adj[i]->apto = 0;
        }
        destroiFP(fila);
    }
    return cidades;
}

/*Aloca memoria para o grafo de cidades.*/
p_grafo criaCidades(int qtdCidades){
    p_grafo Cidades;
    int i;

    Cidades = malloc(sizeof(Grafo));
    Cidades->tamanho = qtdCidades;
    Cidades->adj = malloc(qtdCidades * sizeof(p_no)); 
    for(i=0;i < qtdCidades;i++){
        Cidades->adj[i] = NULL;
    }
    return Cidades;
}

/*Adiona uma nova cidade no grafo.*/
p_grafo adicionaCidade(p_grafo cidades, int pos, char nome[50], int populacao){  
    p_no novo = malloc(sizeof(No));
    novo->populacao = populacao, novo->centralidade = 0.0; novo->dist = 0.0; 
    strcpy(novo->nome, nome);
    novo->prox = cidades->adj[pos];
    cidades->adj[pos] = novo;
    return cidades;
}

/*Adiciona uma aresta na lista de adjacencia do grafo das duas cidades envolvidas.*/
p_grafo adicionaAresta(p_grafo cidades, char cidade_1[50], char cidade_2[50], double dist){  
    int ind_1, ind_2;
    p_no atual;

    if(strcmp(cidade_1, cidade_2) != 0){ 
        p_no cidade1 = malloc(sizeof(No));
        p_no cidade2 = malloc(sizeof(No));
        ind_1 = pegaIndice(cidades, cidade_1);
        ind_2 = pegaIndice(cidades, cidade_2);   
        cidade1->populacao = cidades->adj[ind_1]->populacao; cidade1->dist = dist; cidade1->centralidade = 0.0; 
        cidade2->populacao = cidades->adj[ind_2]->populacao; cidade2->dist = dist; cidade2->centralidade = 0.0; 
        strcpy(cidade1->nome, cidade_1);
        strcpy(cidade2->nome, cidade_2);

        /*Cidade 1*/
        if(cidades->adj[ind_1] != NULL){
            for(atual=cidades->adj[ind_1];atual->prox != NULL;atual=atual->prox){
            }
            atual->prox = cidade2;
            cidade2->prox = NULL;
        }
        else{
            cidade2->prox = cidades->adj[ind_1];
            cidades->adj[ind_1] = cidade2;
        }
        /*Cidade 2*/
        if(cidades->adj[ind_2] != NULL){
            for(atual=cidades->adj[ind_2];atual->prox != NULL;atual=atual->prox){
            }
            atual->prox = cidade1;
            cidade1->prox = NULL;
        }
        else{
            cidade1->prox = cidades->adj[ind_2];
            cidades->adj[ind_2] = cidade1;
        }
    }
    else{
        p_no cidade1 = malloc(sizeof(No));
        ind_1 = pegaIndice(cidades, cidade_1);
        cidade1->populacao = cidades->adj[ind_1]->populacao; cidade1->dist = 0.0; cidade1->centralidade = 0.0; 
        strcpy(cidade1->nome, cidade_1);
        if(cidades->adj[ind_1] != NULL){
            for(atual=cidades->adj[ind_1];atual->prox != NULL;atual=atual->prox){
            }
            atual->prox = cidade1;
            cidade1->prox = NULL;
        }
        else{
            cidade1->prox = cidades->adj[ind_1];
            cidades->adj[ind_1] = cidade1;
        }
    }
    return cidades;
}

/*Percorre todas a possibilidades de caminhos de uma cidade s ate as outras cidades e devolve uma fila de prioridades com os menores caminhos
possiveis.*/
p_fp dijkstra(p_grafo cidades, int s) {
    int i, ind, k;
    p_no atual;
    p_fp fila = criar_fprio(cidades->tamanho);

    for(i=0;i < cidades->tamanho; i++) {
        insere(fila, i, (double)INT_MAX, cidades->adj[i]); 
    }
    diminuiprioridade(fila, s, 0); //diminui prioridade do vertice s para 0;
    while (!vazia(fila)) {  
        k = extrai_minimo(fila);  //pega o menor
        if (prioridade(fila, k) != INT_MAX){
            for(atual = cidades->adj[fila->v[k].ind_grafo]; atual != NULL; atual = atual->prox){  
                ind = procuraIndice(fila, atual->nome);  

                if(prioridade(fila, k)+atual->dist < prioridade(fila, ind)){                    
                    diminuiprioridade(fila,ind,prioridade(fila, k)+atual->dist);
                }
            }
        }
    }
    return fila;
}

/*Extrai o primeiro elemento do heap, que e o menor e joga-o para a ultima posicao.*/
int extrai_minimo(p_fp fila){
    troca(&fila->v[0], &fila->v[fila->n-1]);
    fila->n--;
    desceHeap(fila, 0);
    return fila->n;
}

/*Recebe a posicao k de um elemento e sobe-o no heap.*/
void sobeHeap(p_fp fila, int n){
    if(n > 0 && fila->v[PAI(n)].dist > fila->v[n].dist){
        troca(&fila->v[n], &fila->v[PAI(n)]);
        sobeHeap(fila, PAI(n));
    }
}

/*Recebe a posicao k de um elemento e desce-o no heap.*/
void desceHeap(p_fp fila, int k){
    int menor;
    if(F_ESQ(k) < fila->n){
        menor = F_ESQ(k);
        if(F_DIR(k) < fila->n && fila->v[F_ESQ(k)].dist > fila->v[F_DIR(k)].dist){
            menor = F_DIR(k);
        }
        if(fila->v[k].dist > fila->v[menor].dist){
            troca(&fila->v[k], &fila->v[menor]);
            desceHeap(fila, menor);
        }
    }
}

/*Recebe as informacoes e coloca-as no No da fila de prioridades.*/
void insere(p_fp fila, int i, double dist, p_no cidade){
    fila->v[i].populacao = cidade->populacao;  
    strcpy(fila->v[i].nome, cidade->nome);
    fila->v[i].dist = dist; 
    fila->v[i].ind_grafo = i;
    fila->n++;
}

/*Aloca memoria para a fila de prioridades.*/
p_fp criar_fprio(int tamanho){
    p_fp fila = malloc(sizeof(FP));
    fila->v = malloc(tamanho*sizeof(No));
    fila->n = 0;
    fila->tamanho = tamanho;
    return fila;
}

/*Substitui o valor da distacia do No i na fila prioridades e sobe-o no heap.*/
void diminuiprioridade(p_fp fila, int i, double dist){ 
    fila->v[i].dist = dist;
    sobeHeap(fila, i);
}

/*Verifica se a fila de prioridades esta vazia e retorna.*/
int vazia(p_fp fila){
    if(fila->n == 0){  
        return 1;
    }
    return 0;
}

/*Devolve a prioridade 'dist' do Nó da posicao 'k'.*/
double prioridade(p_fp fila, int k){
    return fila->v[k].dist;
}

/*Troca de posição dois Nós da fila de prioridades.*/
void troca(No *x, No *y){
    No aux = *x;
    *x = *y;
    *y = aux;
}

/*Percorre a fila de prioridades e devolve o indice do no que tem o nome 'nome'.*/
int procuraIndice(p_fp fila, char nome[50]){
    int i;
    for(i=0;i < fila->tamanho;i++){
        if(strcmp(nome, fila->v[i].nome) == 0){
            return i;
        }
    }
    return 0;
}

/*Percorre os vertices do grafo e retorna o indice do vertice "atual" desejado.*/
int pegaIndice(p_grafo cidades, char atual[50]){
    int i;    
    for(i=0;i < cidades->tamanho;i++){
        if(strcmp(cidades->adj[i]->nome, atual) == 0){
            return i;
        }
    }
    return 0;
}

/*Ordena o vetor em ordem crescente pelo metodo quicksort.*/
void quickSort(p_no *vetor, int e, int d){
    int i;
    if(d <= e){
        return;
    }
    i = particiona(vetor, e, d);
    quickSort(vetor, e, i-1);
    quickSort(vetor, i+1, d);
}

/*Particiona o vetor e ordena os termos em ordem decressiva em funcao a um pivo do vetor para ordena-los com base no valor 'qtd', e se este for igual, 
ordena lexicograficamente.*/
int particiona(p_no *vetor, int e, int d){
    int i, pos = d+1;
    double pivo = vetor[e]->centralidade;
    p_no aux;
    for(i=d;i > e;i--){ 
        if(vetor[i]->centralidade > pivo || (vetor[i]->centralidade == pivo && strcmp(vetor[i]->nome, vetor[e]->nome) > 0)){
            pos -= 1;
            aux = vetor[pos];
            vetor[pos] = vetor[i];  
            vetor[i] = aux;
        }
    }
    aux = vetor[pos-1];
    vetor[pos-1] = vetor[e];
    vetor[e] = aux;
    return pos-1;
}

/*Imprime as cidades que podem ser capitais e suas centralidades.*/
void imprimir(p_grafo cidades){
    int i;
    for(i=0;i < cidades->tamanho;i++){
        if(cidades->adj[i]->centralidade != 0 && cidades->adj[i]->apto){
            printf("%s %.2lf\n", cidades->adj[i]->nome, cidades->adj[i]->centralidade);
        }
    }
}

/*Libera a memoria alocada para o grafo.*/
void destroiCidades(p_grafo Cidades){
    int i;
    for(i=0;i < Cidades->tamanho;i++){
        destroiLista(Cidades->adj[i]);
    }
    free(Cidades->adj);
    free(Cidades);
}

/*Libera a memoria alocada para as listas de adjacencia do grafo.*/
void destroiLista(p_no listaAdj){
    if(listaAdj != NULL){
        destroiLista(listaAdj->prox);
        free(listaAdj);
    }
}

/*Libera a memoria alocada para a fila de prioridade.*/
void destroiFP(p_fp fila){
    free(fila->v);
    free(fila);
}

int main(){
    int qtdCidades;
    p_grafo cidades;

    scanf("%d", &qtdCidades);
    cidades = recebeCidades(qtdCidades);
    cidades = recebeArestas(cidades);
    cidades = calcCentralidade(cidades); 

    quickSort(cidades->adj, 0, cidades->tamanho-1);
    imprimir(cidades);

    destroiCidades(cidades);
}