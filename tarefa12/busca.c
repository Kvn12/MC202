#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    char nome[21]; 
    int codigo;
    double valor;
    struct No *esq, *dir;
} No;

typedef No* p_no;

p_no recebeProdutos(int n, p_no produtos);
p_no inserirArvore(p_no raiz, char nome[21], int codigo, double valor);
int  buscaOfertas(p_no raiz, double oferta, int codigo, int *qtd);
p_no arvoreImpressao(p_no raiz, char nome[21], int codigo, double valor);
void imprime(p_no raiz, int codigo);
void destroiArvore(p_no raiz);
void imprimeArvore(p_no raiz);

p_no recebeProdutos(int n, p_no raiz){ 
    int i, codigo;
    double valor;
    char nome[21];
    for(i=0;i < n;i++){
        scanf("%s %d %lf", nome, &codigo, &valor);
        raiz = inserirArvore(raiz, nome, codigo, valor);
    }
    return raiz;
}

// p_no inserirArvore(p_no raiz, char nome[21], int codigo, double valor){  
//     p_no novo;
//     if(raiz == NULL){
//         novo = malloc(sizeof(No));
//         novo->esq = novo->dir = NULL;
//         novo->codigo = codigo;
//         novo->valor = valor;
//         strcpy(novo->nome, nome);
//         return novo;
//     }
//     if(valor < raiz->valor){
//         raiz->esq = inserirArvore(raiz->esq, nome, codigo, valor);
//     }
//     else{
//         raiz->dir = inserirArvore(raiz->dir, nome, codigo, valor);
//     }
//     return raiz;
// }

// p_no buscaOfertas(p_no raiz, p_no impressao, float oferta, int codigo){
//     while(raiz != NULL && raiz->valor < (1.1*oferta)){
//         if(raiz->valor <= (1.1*oferta)){
//             if(raiz->codigo == codigo){
//             impressao = arvoreImpressao(impressao, raiz->nome, raiz->codigo, raiz->valor);
//             }
//             raiz = raiz->esq;
//         }
//         else{
//             raiz = raiz->dir;
//         }
//     }
//     return impressao;
// }

// p_no buscaOfertas(p_no raiz, p_no impressao, float oferta, int codigo){ //recursiva
//     if(raiz == NULL){
//         return impressao;
//     }
//     printf("Percorrendo: %s %d %.2f\n",raiz->nome, raiz->codigo, raiz->valor);
//     if(raiz->valor <= (1.1*oferta)){
//         if(raiz->codigo == codigo){
//         impressao = arvoreImpressao(impressao, raiz->nome, raiz->codigo, raiz->valor);
//         }
//         buscaOfertas(raiz->esq, impressao, oferta, codigo);
//     }
//     // printf("AntesIF: %s %d %.2f\n",raiz->nome, raiz->codigo, raiz->valor);
//     if(raiz->dir != NULL && raiz->dir->valor <= (1.1*oferta)){
//         printf("SIIIIIIM\n");
//         buscaOfertas(raiz->dir, impressao, oferta, codigo);
//     }        
//     return impressao;
// }

int buscaOfertas(p_no raiz, double oferta, int codigo, int *qtd){ //recursiva
    if(raiz == NULL){
        return *qtd;
    }
    buscaOfertas(raiz->esq, oferta, codigo, qtd);
    if(raiz->valor <= (1.1*oferta) && raiz->codigo == codigo){
        *qtd += 1;
        printf("%s %d %.2f\n",raiz->nome, raiz->codigo, raiz->valor);
    }       
    buscaOfertas(raiz->dir, oferta, codigo, qtd); 
    return *qtd;
}

p_no inserirArvore(p_no raiz, char nome[21], int codigo, double valor){  
    p_no novo;
    if(raiz == NULL){
        novo = malloc(sizeof(No));
        novo->esq = novo->dir = NULL;
        novo->codigo = codigo;
        novo->valor = valor;
        strcpy(novo->nome, nome);
        return novo;
    }
    if(/*valor < raiz->valor*/strcmp(nome, raiz->nome) < 0){
        raiz->esq = inserirArvore(raiz->esq, nome, codigo, valor);
    }
    else{
        raiz->dir = inserirArvore(raiz->dir, nome, codigo, valor);
    }
    return raiz;
}

void imprimeArvore(p_no raiz){
    if(raiz != NULL){
        imprimeArvore(raiz->esq);
        printf("%s %d %.2f\n",raiz->nome, raiz->codigo, raiz->valor);
        imprimeArvore(raiz->dir);
    }
}

//Libera a memoria alocada para a arvore.
void destroiArvore(p_no raiz){
    if(raiz != NULL){
        destroiArvore(raiz->esq);
        destroiArvore(raiz->dir);
        free(raiz);
    }
}

int main(){
    int n, m, i, qtd;
    int codigoProduto;
    double oferta;
    p_no raiz;
    raiz = NULL;
    scanf("%d", &n);
    raiz = recebeProdutos(n, raiz);
    scanf("%d", &m);
    for(i=0;i < m;i++){
        qtd = 0;
        scanf("%d %lf", &codigoProduto, &oferta);
        printf("OFERTAS para %d:\n", codigoProduto);
        qtd = buscaOfertas(raiz, oferta, codigoProduto, &qtd);
        if(qtd == 0){
            printf("nenhuma boa oferta foi encontrada\n");
        }
        if(i+1!=m){
        printf("\n");
        }
    }
    destroiArvore(raiz);
}
