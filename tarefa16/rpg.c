#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    char nome[30];
    int forca, destreza, constituicao, inteligencia, sabedoria, carisma, cont;
    struct No *prox;
} No;

typedef No * p_no;

typedef struct{
    p_no *adj;
    int tamanho;
} Grafo;

typedef Grafo * p_grafo;

int comparaAtributos(p_no a, p_no b);
int pegaIndice(p_grafo celas, p_no atual);
int verificaIndice(int *vetor, int tamanho, int i);
void imprime(p_grafo celas, int qtdJogadores);
void destroiCelas(p_grafo celas);
void destroiLista(p_no listaAdj);
void recebeJogadores(p_grafo celas);
p_grafo recebeCelas();
p_grafo criaCelas(int tamanho);
p_grafo procuraAdj(p_grafo celas);
p_grafo simulaMovimentos(p_grafo celas, int pos);
p_grafo insereAresta(p_grafo celas, int pos, int forca, int destreza, int constituicao, int inteligencia, int sabedoria, int carisma, char nome[30]);

/*Recebe os atributos das celas e cria os vertices do grafo com os atributos.*/
p_grafo recebeCelas(){
    int qtd, i, forca, destreza, constituicao, inteligencia, sabedoria, carisma;
    char nome[30]; 
    p_grafo celas;
    scanf("%d", &qtd);
    celas = criaCelas(qtd);

    for(i=0;i < qtd;i++){
        scanf("%s %d %d %d %d %d %d", nome, &forca, &destreza, &constituicao, &inteligencia, &sabedoria, &carisma);
        celas = insereAresta(celas, i, forca, destreza, constituicao, inteligencia, sabedoria, carisma, nome);
    }
    return celas;
}

/*Recebe os atributos dos jogadores e simula as posiveis jogadas que ele pode fazer.*/
void recebeJogadores(p_grafo celas){
    int qtd, i, j, forca, destreza, constituicao, inteligencia, sabedoria, carisma;
    char nome[30];
    scanf("%d", &qtd);
    for(i=0;i < qtd;i++){
        scanf("%s %d %d %d %d %d %d", nome, &forca, &destreza, &constituicao, &inteligencia, &sabedoria, &carisma);
        for(j=0;j < celas->tamanho;j++){
            if(celas->adj[j]->carisma == carisma && celas->adj[j]->constituicao == constituicao && celas->adj[j]->destreza == destreza
            && celas->adj[j]->forca == forca && celas->adj[j]->inteligencia == inteligencia && celas->adj[j]->sabedoria == sabedoria){
                /*Jogador se encontra aqui*/
                simulaMovimentos(celas, j);
                break;
            }
        }
    }
    imprime(celas, qtd);
}

/*Aloca a memoria para os vertices do grafo.*/
p_grafo criaCelas(int tamanho){ 
    int i;
    p_grafo celas;
    celas = malloc(sizeof(Grafo));
    celas->tamanho = tamanho;
    celas->adj = malloc(tamanho * sizeof(p_no)); 
    for(i=0;i < tamanho;i++){
        celas->adj[i] = NULL;
    }
    return celas;
}

/*Insere uma nova aresta no vertice de posicao "pos".*/
p_grafo insereAresta(p_grafo celas, int pos, int forca, int destreza, int constituicao, int inteligencia, int sabedoria, int carisma, char nome[30]){  
    p_no atual;
    p_no novo = malloc(sizeof(No));
    novo->carisma = carisma; novo->constituicao = constituicao; novo->destreza = destreza; novo->forca = forca; novo->inteligencia = inteligencia; 
    novo->sabedoria = sabedoria, novo->cont = 0; 
    strcpy(novo->nome, nome);

    if(celas->adj[pos] != NULL){
        for(atual=celas->adj[pos];atual->prox != NULL;atual=atual->prox){
        }
        atual->prox = novo;
        novo->prox = NULL;
    }
    else{
        novo->prox = celas->adj[pos];
        celas->adj[pos] = novo;
    }
    return celas;
}

/*Percorre todos os vertices do grafo e verifica se podem ser adjacentes e adiciona arestas quando sao.*/
p_grafo procuraAdj(p_grafo celas){
    int i, j;
    for(i=0;i < celas->tamanho;i++){
        for(j=0;j < celas->tamanho;j++){
            if(i != j){
                if(comparaAtributos(celas->adj[i], celas->adj[j])){
                    insereAresta(celas, i, celas->adj[j]->forca, celas->adj[j]->destreza, celas->adj[j]->constituicao, celas->adj[j]->inteligencia,
                    celas->adj[j]->sabedoria, celas->adj[j]->carisma, celas->adj[j]->nome);
                }
            }
        }
    }
    return celas;
}

/*Compara os atributos de dois vertices e se der para um jogador se locomover do vertice a para o b retorna 1, de modo a serem adjacentes.*/
int comparaAtributos(p_no a, p_no b){ 
    if((a->carisma +1 >= b->carisma && a->constituicao >= b->constituicao && a->destreza >= b->destreza &&  a->forca >= b->forca && 
    a->inteligencia >= b->inteligencia && a->sabedoria >= b->sabedoria) ||
    (a->carisma >= b->carisma && a->constituicao+1 >= b->constituicao && a->destreza >= b->destreza &&  a->forca >= b->forca && 
    a->inteligencia >= b->inteligencia && a->sabedoria >= b->sabedoria) ||
    (a->carisma >= b->carisma && a->constituicao >= b->constituicao && a->destreza+1 >= b->destreza &&  a->forca >= b->forca && 
    a->inteligencia >= b->inteligencia && a->sabedoria >= b->sabedoria) ||
    (a->carisma >= b->carisma && a->constituicao >= b->constituicao && a->destreza >= b->destreza &&  a->forca+1 >= b->forca && 
    a->inteligencia >= b->inteligencia && a->sabedoria >= b->sabedoria) ||
    (a->carisma >= b->carisma && a->constituicao >= b->constituicao && a->destreza >= b->destreza &&  a->forca >= b->forca && 
    a->inteligencia+1 >= b->inteligencia && a->sabedoria >= b->sabedoria) ||
    (a->carisma >= b->carisma && a->constituicao >= b->constituicao && a->destreza >= b->destreza &&  a->forca >= b->forca && 
    a->inteligencia >= b->inteligencia && a->sabedoria+1 >= b->sabedoria)){
        return 1;
    }
    else{
        return 0;
    }
}

/*Simula as possiveis movimentacoes de um jogador ao adicionar o valor 1 no contador dos vertices que ele pode ir em ate 2 rodadas.*/
p_grafo simulaMovimentos(p_grafo celas, int pos){
    p_no atual1, atual2;
    int indice1, indice2, i = 0, j;
    int *indVisitados;

    indVisitados = malloc(celas->tamanho*sizeof(int));
    for(j=0;j < celas->tamanho;j++){
        indVisitados[j] = -1;
    }
    for(atual1=celas->adj[pos]->prox;atual1 != NULL;atual1=atual1->prox){ 
        indice1 = pegaIndice(celas, atual1);
        if(!verificaIndice(indVisitados, celas->tamanho, indice1)){
            indVisitados[i] = indice1;
            celas->adj[indice1]->cont += 1;
            i ++;
        }
        for(atual2=celas->adj[indice1]->prox;atual2 != NULL;atual2=atual2->prox){   
            indice2 = pegaIndice(celas, atual2);
            if(!verificaIndice(indVisitados, celas->tamanho, indice2)){
                indVisitados[i] = indice2;
                celas->adj[indice2]->cont += 1;
                i ++;
            }
        }
    }
    free(indVisitados);
    return celas;
}

/*Percorre os vertices do grafo e retorna o indice do vertice "atual" desejado.*/
int pegaIndice(p_grafo celas, p_no atual){
    int i;    
    for(i=0;i < celas->tamanho;i++){
        if(strcmp(celas->adj[i]->nome, atual->nome) == 0){
            return i;
        }
    }
    return 0;
}

/*Pecorre o vetor auxiliar a funcao "simulaMovimentos e se encontrar o valor i em alguma posicao retorna 1.*/
int verificaIndice(int *vetor, int tamanho, int i){ 
    int j;
    for(j=0;j < tamanho;j++){
        if(vetor[j] == i){
            return 1;
        }
    }
    return 0;
}

/*Percorre os vertices do grafo e imprime os que todos os jogadores conseguem percorrer em ate duas jogadas.*/
void imprime(p_grafo celas, int qtdJogadores){
    int i;
    int controle = 0;
    for(i=0;i < celas->tamanho;i++){
        if(celas->adj[i]->cont >= qtdJogadores){
            printf("%s\n", celas->adj[i]->nome);
            controle +=1 ;
        }
    }
    if(controle == 0){
        printf("\nImpossivel terminar em duas rodadas.\n");
    }
}

/*Libera a memoria alocada para o grafo.*/
void destroiCelas(p_grafo celas){
    int i;
    for(i=0;i < celas->tamanho;i++){
        destroiLista(celas->adj[i]);
    }
    free(celas->adj);
    free(celas);
}

/*Libera a memoria alocada para as listas de adjacencia do grafo.*/
void destroiLista(p_no listaAdj){
    if(listaAdj != NULL){
        destroiLista(listaAdj->prox);
        free(listaAdj);
    }
}

int main(){
    p_grafo celas;
    celas = recebeCelas();
    celas = procuraAdj(celas);
    recebeJogadores(celas);
    destroiCelas(celas);
}