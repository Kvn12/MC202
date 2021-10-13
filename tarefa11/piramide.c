#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    char nome[21];
    float capital;
    struct No *esq, *dir, *recrutador;
} No;

typedef struct Fila{
    // char nome[21];
    // float capital;
    struct No *raiz;
    struct Fila *prox;
} Fila;

typedef No* p_no;
typedef Fila *p_fila;

p_no calculaPagamentos(p_no raiz, p_no recrutador, float porcentagem);
p_no procuraRecrutador(p_no raiz, char nome[21]);
p_no adiciona(p_no piramide, p_no novo, char recrutador[21]);
p_fila criarFila();
p_no tirarFila(p_fila fila);
int filaVazia(p_fila fila);

void adicionarFila(p_fila fila, p_no raiz){
    p_fila novo;
    p_fila atual;
    novo = malloc(sizeof(fila));
    novo->raiz = raiz;
    novo->prox = NULL;
    if(fila == NULL){
        fila = novo;
    }
    else{
        for(atual=fila;atual->prox != NULL;atual=atual->prox){
        }
        atual->prox = novo;
    }
}

void destroiFila(p_fila fila){
    //libera a memoria alocada para a fila
    if(fila != NULL){
        destroiFila(fila->prox);
        free(fila);
    }
}


void recebeEventos(p_no piramide){
    p_no topo;
    float capital;
    char recrutador[21], nome[21], acao[8];
    topo = malloc(sizeof(No));
    scanf("%s %s %f", recrutador, topo->nome, &topo->capital);
    topo->dir = NULL;
    topo->esq = NULL;
    adiciona(piramide, topo, recrutador);
    while(scanf("%s %s %s %f", recrutador, acao, nome, &capital) != EOF){
        p_no novo;
        novo = malloc(sizeof(No));
        strcpy(novo->nome, nome);
        novo->capital = capital;  
        novo->dir = NULL;
        novo->esq = NULL;
        adiciona(piramide, novo, recrutador);
    }
}

void imprime(p_no raiz){ //colocar os niveis e tal
    // int nivel = 1;
    p_fila fila;
    fila = criarFila();
    adicionarFila(fila, raiz);
    while(!filaVazia(fila)){
        raiz = tirarFila(fila);
        if(raiz != NULL){
            adicionarFila(fila, raiz->esq);
            adicionarFila(fila, raiz->dir);
            printf("%s %.2f\n", raiz->nome, raiz->capital);
        }
    }
    destroiFila(fila);
}


void destroiPiramide(p_no piramide){

}

p_no calculaPagamentos(p_no raiz, p_no recrutador, float porcentagem){
    if(porcentagem < 0.01 || recrutador == NULL){ 
        return raiz;
    }
    recrutador->capital = raiz->capital*porcentagem;
    return calculaPagamentos(recrutador, recrutador->recrutador, porcentagem-0.01);
}

p_no procuraRecrutador(p_no raiz, char nome[21]){
    p_no esq;

    printf("RaizNome%s\n", raiz->nome);
    printf("Nome %s\n", nome);

    if(raiz == NULL || strcmp(raiz->nome, nome)==0){
        return raiz;
    }
    esq = procuraRecrutador(raiz->esq, nome);
    if(esq != NULL){
        return esq;
    }
    return procuraRecrutador(raiz->dir, nome);
}

p_no adiciona(p_no piramide, p_no novo, char recrutador[21]){
    p_no raiz;
    float bonificacao;
    char topo[5] = {"Topo"};
    if(strcmp(recrutador, topo)==0){ //se for o topo
        novo->recrutador = NULL;
        piramide = novo;
        // imprime(piramide);
    }
    else{
        printf("Else %s\n", piramide->nome);
        raiz = procuraRecrutador(piramide, recrutador);
        bonificacao = (novo->capital*0.10);
        raiz->capital -= bonificacao;
        novo->capital += bonificacao;
        novo->recrutador = raiz;
        if(raiz->esq == NULL){
            raiz->esq = novo;
        }
        else{
            raiz->dir = novo;
            raiz->capital += (raiz->dir->capital*0.06) + (raiz->esq->capital*0.06);;
            calculaPagamentos(raiz, raiz->recrutador, 0.05);
        }
        imprime(raiz);        
    }
    return 0;
}

p_fila criarFila(){
    return NULL;
}

p_no tirarFila(p_fila fila){ //liberar memoria aqui
    p_fila retorno;
    retorno = fila;
    fila = fila->prox;
    return retorno->raiz;
}

int filaVazia(p_fila fila){
    if(fila == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int main(){
    p_no piramide;
    piramide = malloc(sizeof(No));
    recebeEventos(piramide);
}