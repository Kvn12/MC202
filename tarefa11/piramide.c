#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{ 
    char nome[21];
    int nivel;
    double capital;
    struct No *esq, *dir, *recrutador;
} No;

typedef struct Fila{ 
    struct No *raiz;
    struct Fila *prox;
} Fila;

typedef No* p_no;
typedef Fila *p_fila;

p_no calculaPagamentos(p_no raiz, p_no recrutador, double porcentagem);
p_no procuraRecrutador(p_no *raiz, char nome[21]);
p_no adiciona(p_no *piramide, p_no *novo, char recrutador[21]);
p_no recebeEventos(p_no piramide);
p_fila criarFila();
p_fila tirarFila(p_fila *fila);
p_fila adicionarFila(p_fila fila, p_no raiz);
int filaVazia(p_fila fila);
void imprime(p_no *raiz);
void destroiFila(p_fila fila);

p_no recebeEventos(p_no piramide){
    //Recebe as estradas e chama a funcao para adicionar na piramide o novo integrante. 
    p_no topo;
    double capital;
    char recrutador[21], nome[21], acao[8];
    topo = malloc(sizeof(No));
    scanf("%s %s %lf", recrutador, topo->nome, &(topo->capital));
    topo->dir = NULL;
    topo->esq = NULL;
    topo->nivel = 1;
    adiciona(&piramide, &topo, recrutador);
    while(scanf("%s %s %s %lf", recrutador, acao, nome, &capital) != EOF){
        p_no novo;
        novo = malloc(sizeof(No));
        strcpy(novo->nome, nome);
        novo->capital = capital;  
        novo->dir = NULL;
        novo->esq = NULL;
        adiciona(&piramide, &novo, recrutador);
    }
    return piramide;
}

p_no adiciona(p_no *piramide, p_no *novo, char recrutador[21]){
    //Recebe a piramide e o novo integrante e insere-o como filho do seu recrutador.
    p_no raiz;
    double bonificacao;
    char topo[5] = {"Topo"};
    if(strcmp(recrutador, topo)==0){ //se for o topo
        (*novo)->recrutador = NULL;
        *piramide = *novo;
        imprime(piramide);
    }
    else{
        raiz = procuraRecrutador(piramide, recrutador);
        bonificacao = ((*novo)->capital*0.10);
        raiz->capital -= bonificacao;
        (*novo)->capital += bonificacao;
        (*novo)->recrutador = raiz;
        if(raiz->esq == NULL){
            raiz->esq = (*novo);
            (*novo)->nivel = raiz->nivel + 1;
        }
        else{
            (*novo)->nivel = raiz->esq->nivel;
            raiz->dir = (*novo);
            raiz->capital += (raiz->dir->capital*0.06) + (raiz->esq->capital*0.06);
            raiz->dir->capital -= raiz->dir->capital*0.06; 
            raiz->esq->capital -= raiz->esq->capital*0.06; 
            calculaPagamentos(raiz, raiz->recrutador, 0.05);
        }
        imprime(piramide);        
    }
    return 0;
}

p_no procuraRecrutador(p_no *raiz, char nome[21]){
    //Percorre os nós da arvore e devolve o o nó procurado.
    p_no esq;

    if((*raiz) == NULL || strcmp((*raiz)->nome, nome)==0){
        return (*raiz);
    }
    esq = procuraRecrutador(&((*raiz)->esq), nome);
    if(esq != NULL){
        return esq;
    }
    return procuraRecrutador(&((*raiz)->dir), nome);
}

p_no calculaPagamentos(p_no raiz, p_no recrutador, double porcentagem){
    //Faz as operacoes de calculo da remuneracao para os niveis anteriores de forma recursiva.
    if(porcentagem == 0.00 || recrutador == NULL){ 
        return raiz;
    }
    recrutador->capital += raiz->capital*porcentagem;
    raiz->capital -= raiz->capital*porcentagem;
    return calculaPagamentos(recrutador, recrutador->recrutador, porcentagem-0.01);
}

void imprime(p_no *raiz){ 
    //Percorre a arvore lateralmente e imprime os seus nós, com base em seus niveis.
    int nivelAnterior = 0;
    p_fila fila;
    p_fila atual;
    fila = criarFila();
    fila = adicionarFila(fila, *raiz);
    while(!filaVazia(fila)){
        atual = tirarFila(&fila);
        if(atual != NULL){
            if(atual->raiz->esq != NULL){
                fila = adicionarFila(fila, atual->raiz->esq);
            }
            if(atual->raiz->dir != NULL){
                fila = adicionarFila(fila, atual->raiz->dir);
            }
            //impressao
            if(atual->raiz->nivel == nivelAnterior){
                printf(" [%s %.2lf]", atual->raiz->nome, atual->raiz->capital);
            }
            else{
                if(atual->raiz->nivel != 1){
                    printf("\n");
                }
                printf("Nivel %d: [%s %.2lf]", atual->raiz->nivel, atual->raiz->nome, atual->raiz->capital);
            }
            nivelAnterior = atual->raiz->nivel;
            free(atual);
        }
    }
    printf("\n");
    printf("\n");
    free(fila);
}

p_fila adicionarFila(p_fila fila, p_no raiz){
    //Adiciona um novo nó na fila que e auxiliar para a funcao de impressao.
    p_fila novo;
    p_fila atual;
    novo = malloc(sizeof(*fila));
    novo->raiz = raiz;
    novo->prox = NULL;
    if(fila == NULL){
        return novo;
    }
    else{
        for(atual=fila;atual->prox != NULL;atual=atual->prox){
        }
        atual->prox = novo;
    }    
    return fila;
}

p_fila tirarFila(p_fila *fila){ 
    //Tira o primeiro no da fila e retorna-o.
    p_fila retorno;
    retorno = *fila; 
    *fila = (*fila)->prox;
    return retorno;
}

p_fila criarFila(){
    return NULL;
}

int filaVazia(p_fila fila){
    //Verifica se a fila esta vazia, se sim retorna 1.
    if(fila == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

void destroiPiramide(p_no piramide){
    //Libera a memoria alocada para a arvore.
    if(piramide != NULL){
        destroiPiramide(piramide->esq);
        destroiPiramide(piramide->dir);
        free(piramide);
    }
}

int main(){
    p_no piramide;
    piramide = NULL;
    piramide = recebeEventos(piramide);
    destroiPiramide(piramide);
}