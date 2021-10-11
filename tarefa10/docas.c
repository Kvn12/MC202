#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct navio{
    int qtd_inicial, qtd_atual;
    char nome[21], acao[12], mercadoria[21];
    struct navio *prox;
} Navios;

typedef struct docas{
    int topo;
    char **pilha; 
} Doca;

typedef Doca* p_doca;
typedef Navios* p_navio;

p_navio recebeNavios(p_navio fila, int num_navios);
p_doca criaPorto(p_doca *porto, int num_docas, int capaci_docas);
int verificaFim(p_navio fila);
int carregar(p_doca *porto, p_navio atual, int num_docas, char mercadoria[21]);
int descarrega(p_doca *porto, p_navio atual, int num_docas, int capaci_docas);
p_navio criaFila();

p_navio recebeNavios(p_navio fila, int num_navios){
    //Recebe os navios com suas mercadoria em uma lista ligada.
    int i;
    p_navio aux;
    for(i=0;i < num_navios;i++){
        p_navio novo;
        novo = malloc(sizeof(Navios));
        novo->qtd_atual = 0;
        scanf("%s %s %s %d", novo->nome, novo->acao, novo->mercadoria, &novo->qtd_inicial);
        if(fila == NULL){                                //se for o primeiro
            novo->prox = NULL;
            fila = novo;        
        }
        else{ 
            for(aux=fila;aux != NULL;aux = aux->prox){
                if(aux->prox == NULL){
                    novo->prox = NULL;
                    aux->prox = novo;
                    break;
                }
            }
        }
    }
    return fila;
}

void inserirPilha(p_doca doca, char mercadoria[21]){
    //Insere a mercadoria no topo da pilha de determinada doca.
    doca->topo ++;
    strcpy(doca->pilha[doca->topo], mercadoria);
}

p_doca criaPorto(p_doca *porto, int num_docas, int capaci_docas){ // ver isso certinho
    //Aloca memória e cria o porto, onde cada posicao é uma doca com uma pilha.
    int i, j;
    for(i=0;i < num_docas;i++){
        porto[i] = malloc(sizeof(Doca));
        porto[i]->topo = -1;
        porto[i]->pilha = malloc(capaci_docas*sizeof(char*));
        for(j=0;j < capaci_docas;j++){
            porto[i]->pilha[j] = malloc(21*sizeof(char));

        }
    }
    return *porto;
}

int verificaFim(p_navio fila){
    //Verifica quantos navios ficaram sem finalizar as suas tarefas.
    int soma = 0;
    p_navio atual;
    for(atual=fila;atual != NULL;atual=atual->prox){  
        if(atual->qtd_atual != atual->qtd_inicial){
            soma += 1;
        }
    }
    return soma;
}

int carregar(p_doca *porto, p_navio atual, int num_docas, char mercadoria[21]){ 
    //Realiza a acao de carregar os navios com base na mercadoria desejada mas somente se a mercadoria existir for o topo da pilha.
    //Retorna 1 se o navio carrgou alguma coisa, e retorna 0 se nao carregou nada.
    int i;
    int carregado = 0;
    for(i=0;i < num_docas;i++){
        if(porto[i]->topo != -1){
            if(strcmp(porto[i]->pilha[porto[i]->topo], mercadoria) == 0){
                while(porto[i]->topo != -1 && strcmp(porto[i]->pilha[porto[i]->topo], mercadoria) == 0 && atual->qtd_atual < atual->qtd_inicial){ 
                    atual->qtd_atual += 1; 
                    porto[i]->topo -=1;         
                    carregado +=1;
                }
                printf("%s carrega %s doca: %d conteineres: %d\n", atual->nome, atual->mercadoria, i, carregado); 
                return 1;
            }
        }
    }
    return 0;
}

int descarrega(p_doca *porto, p_navio atual, int num_docas, int capaci_docas){
    //Realiza a acao de descarregar um navio e colocar as mercadorias na doca q estiver disponivel.
    //Retorna 1 se deu para descarregar algo, e retorna 0 se nao descarregou nada.
    int i;
    int descarregado = 0;
    for(i=0;i < num_docas;i++){
        if(porto[i]->topo+1 < capaci_docas){  
            while(porto[i]->topo+1 < capaci_docas && atual->qtd_atual < atual->qtd_inicial){  
                inserirPilha(porto[i], atual->mercadoria);
                atual->qtd_atual += 1;
                descarregado += 1;
            }
            printf("%s descarrega %s doca: %d conteineres: %d\n", atual->nome, atual->mercadoria, i, descarregado);
            return 1;                                       
        }
    }
    return 0; 
}

void fluxoPorto(p_navio fila, p_doca *porto, int num_docas, int num_navios, int capaci_docas){ 
    //Simula o fluxo do porto, onde chega a vez de cada navio e este tenta realizar a sua acao em uma doca disponivel,
    //após algumas rodadas, se nenhum navio fez nada, ele confere se algum navio ainda tem a algo a fazer e imprime uma mensagem de erro,
    //se algum navio nao completou a sua tarefa. 
    int i, movimentacao;
    int remanescentes = 0;
    p_navio atual;
    char carrega[9] = {"carrega"}; 
    while(movimentacao != 0 ){ 
        movimentacao = 0;
        atual = fila;
        for(i=0;i < num_navios;i++){
            if(strcmp(atual->acao, carrega) == 0){  //carregar
                    if(atual->qtd_atual < atual->qtd_inicial){
                        if(carregar(porto, atual, num_docas, atual->mercadoria)){      
                            movimentacao +=1;                               
                        }
                    }
            }
            else{   //descarrega
                if(atual->qtd_atual < atual->qtd_inicial){
                    if(descarrega(porto, atual, num_docas, capaci_docas)){
                        movimentacao += 1;
                    }
                }
            }
            atual = atual->prox;
        }
    }
    remanescentes = verificaFim(fila);
    if(remanescentes){                  
        printf("ALERTA: impossivel esvaziar fila, restam %d navios.", remanescentes);
    }
}

p_navio criaFila(){
    return NULL;
}

void destroiPorto(p_doca *porto, int num_docas, int capaci_docas){  // arrumar isso
    //Libera toda a memoria alocada para a construcao do porto.
    int i, j;
    for(i=0;i < num_docas;i++){
        for(j=0;j < capaci_docas;j++){
            free(porto[i]->pilha[j]);
        }
        free(porto[i]);
    }
    free(porto);
}

void destroiFila(p_navio fila){
    //Libera toda a memoria alocada para a construcao da fila de navios.
    p_navio atual;
    p_navio aux;
    atual = fila;
    while(atual->prox != NULL){
        aux = atual->prox;
        free(atual);
        atual = aux;
    }
    free(atual);
}

int main(){
    int num_docas, capaci_docas, num_navios;
    p_doca *porto;
    p_navio fila;
    fila = criaFila();
    scanf("%d", &num_docas);
    scanf("%d", &capaci_docas);
    scanf("%d", &num_navios);
    porto = malloc(num_docas*sizeof(p_doca));
    fila = recebeNavios(fila, num_navios);
    *porto = criaPorto(porto, num_docas, capaci_docas);
    fluxoPorto(fila,porto, num_docas, num_navios, capaci_docas);
    destroiFila(fila); 
    destroiPorto(porto, num_docas, capaci_docas);
}

