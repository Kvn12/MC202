#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{ 
    char IP[17]; 
    char dominio[101];
    int altura;
    struct No *esq, *dir;
} No;

typedef struct Requests{
    char ip[17];
    int acessos;
    int altura;
    struct Requests *esq, *dir;
} Requests; 

typedef No * p_no;
typedef Requests * p_req;

p_no recebeArvore(p_no raiz, int n);
p_no inserir(p_no raiz, char IP[17], char dominio[101]);
p_no rotacionaDir(p_no raiz);
p_no rotacionaEsq(p_no raiz);
int alt(p_no raiz);
int max(int x, int y);
int verBalanceamento(p_no raiz);
void recebeRequest(p_no raiz, int m, int u);
int buscarDominio(p_no raiz, char ipOrigem[17], char dominio[101], int *retorno);
void destroiArvore(p_no raiz);
void destroiArvore2(p_req raiz);
p_req inserirReq(p_req raiz, char ipOrigem[17], int *controle);
p_req rotacionaDir2(p_req raiz);
p_req rotacionaEsq2(p_req raiz);
int alt2(p_req raiz);
int verBalanceamento2(p_req raiz);

void imprime(p_no raiz);

p_no recebeArvore(p_no raiz, int n){
    int i; 
    char IP[17], dominio[101];
    for(i=0;i < n;i++){
        scanf("%s %s", dominio, IP);
        raiz = inserir(raiz, IP, dominio);
    }
    return raiz;
}

p_no inserir(p_no raiz, char IP[17], char dominio[101]){
    p_no novo;
    int balanceamento;
    if(raiz == NULL){
        novo = malloc(sizeof(No));
        novo->esq = novo->dir = NULL;
        novo->altura = 1;
        strcpy(novo->IP, IP);
        strcpy(novo->dominio, dominio);
        return novo;
    }
    if(strcmp(dominio, raiz->dominio) < 0){
        raiz->esq = inserir(raiz->esq, IP, dominio);
    }
    else {
        raiz->dir = inserir(raiz->dir, IP, dominio);
    }
    //corrige a arvore
    raiz->altura = 1 + max(alt(raiz->esq), alt(raiz->dir));
    balanceamento = verBalanceamento(raiz);

    if(balanceamento > 1 && strcmp(dominio, raiz->esq->dominio) < 0){
        return rotacionaDir(raiz);
    }
    if(balanceamento < -1 && strcmp(dominio, raiz->dir->dominio) > 0){
        return rotacionaEsq(raiz);
    }
    if(balanceamento > 1 && strcmp(dominio, raiz->esq->dominio) > 0){
        raiz->esq = rotacionaEsq(raiz->esq);
        return rotacionaDir(raiz);
    }
    if(balanceamento < -1 && strcmp(dominio, raiz->dir->dominio) < 0){
        raiz->dir = rotacionaDir(raiz->dir);
        return rotacionaEsq(raiz);
    }

    return raiz;
}

p_no rotacionaDir(p_no raiz){
    p_no x = raiz->esq;
    p_no y = x->dir;

    x->dir = raiz;
    raiz->esq = y;

    raiz->altura = max(alt(raiz->esq), alt(raiz->dir)) +1;
    x->altura = max(alt(x->esq), alt(x->dir)) +1;
    return x;
}

p_no rotacionaEsq(p_no raiz){

    // printf("rotaciona %s\n", raiz->dir->dominio);
    p_no x = raiz->dir;
    p_no y = x->esq;

    // printf("DENTRO um\n");
    
    x->esq = raiz;
    raiz->dir = y;

    raiz->altura = max(alt(raiz->esq), alt(raiz->dir)) +1;
    x->altura = max(alt(x->esq), alt(x->dir)) +1;
    return x;
}

int alt(p_no raiz){
    if(raiz == NULL){
        return 0;
    }
    else{
        return raiz->altura;
    }
}

int max(int x, int y){
    if(x > y){
        return x;
    }
    else{
        return y;
    }
}

int verBalanceamento(p_no raiz){
    if(raiz == NULL){
        return 0;
    }
    else{
        return alt(raiz->esq) - alt(raiz->dir);
    }
}

void recebeRequest(p_no raiz, int m, int u){ 
    p_req requests;
    requests = NULL;
    int i, retorno, controle;
    char get[4], dominio[101], ipOrigem[17], from[5];
    for(i=0;i < m;i++){
        retorno = 0;
        controle = 0;
        scanf("%s %s %s %s", get, dominio, from, ipOrigem);
        requests = inserirReq(requests, ipOrigem, &controle);
        if(controle <= u){   
            retorno = buscarDominio(raiz, ipOrigem, dominio, &retorno);
            if(retorno == 0){
                printf("NOTFOUND %s FROM %s\n", dominio, ipOrigem);
            }
        }
        else{
            printf("FORBIDDEN %s FROM %s\n", dominio, ipOrigem);
        }
    }
    destroiArvore2(requests);
}

p_req inserirReq(p_req raiz, char ipOrigem[17], int *controle){
    p_req novo;
    int balanceamento;
    if(raiz == NULL){
        novo = malloc(sizeof(Requests));
        novo->dir = novo->esq = NULL;
        strcpy(novo->ip, ipOrigem);
        novo->acessos = 1;
        novo->altura = 1;
        (*controle) = 1;
        return novo;
    }
    if(strcmp(raiz->ip, ipOrigem) == 0){
        raiz->acessos += 1;
        (*controle) = raiz->acessos;
        return raiz;
    }
    if(strcmp(ipOrigem, raiz->ip) < 0){
        raiz->esq = inserirReq(raiz->esq, ipOrigem, controle);
    }
    else {
        raiz->dir = inserirReq(raiz->dir, ipOrigem, controle);
    }
    //corrige a arvore
    raiz->altura = 1 + max(alt2(raiz->esq), alt2(raiz->dir));
    balanceamento = verBalanceamento2(raiz);

    if(balanceamento > 1 && strcmp(ipOrigem, raiz->esq->ip) < 0){
        return rotacionaDir2(raiz);
    }
    if(balanceamento < -1 && strcmp(ipOrigem, raiz->dir->ip) > 0){
        return rotacionaEsq2(raiz);
    }
    if(balanceamento > 1 && strcmp(ipOrigem, raiz->esq->ip) > 0){
        raiz->esq = rotacionaEsq2(raiz->esq);
        return rotacionaDir2(raiz);
    }
    if(balanceamento < -1 && strcmp(ipOrigem, raiz->dir->ip) < 0){
        raiz->dir = rotacionaDir2(raiz->dir);
        return rotacionaEsq2(raiz);
    }

    return raiz;
}

p_req rotacionaDir2(p_req raiz){
    p_req x = raiz->esq;
    p_req y = x->dir;

    x->dir = raiz;
    raiz->esq = y;

    raiz->altura = max(alt2(raiz->esq), alt2(raiz->dir)) +1;
    x->altura = max(alt2(x->esq), alt2(x->dir)) +1;
    return x;
}

p_req rotacionaEsq2(p_req raiz){

    // printf("rotaciona %s\n", raiz->dir->dominio);
    p_req x = raiz->dir;
    p_req y = x->esq;

    // printf("DENTRO um\n");
    
    x->esq = raiz;
    raiz->dir = y;

    raiz->altura = max(alt2(raiz->esq), alt2(raiz->dir)) +1;
    x->altura = max(alt2(x->esq), alt2(x->dir)) +1;
    return x;
}

int alt2(p_req raiz){
    if(raiz == NULL){
        return 0;
    }
    else{
        return raiz->altura;
    }
}

int verBalanceamento2(p_req raiz){
    if(raiz == NULL){
        return 0;
    }
    else{
        return alt2(raiz->esq) - alt2(raiz->dir);
    }
}

// p_req inserirReq(p_req raiz, char ipOrigem[17], int *controle){  
//     p_req novo;
//     if(raiz == NULL){
//         novo = malloc(sizeof(Requests));
//         novo->dir = novo->esq = NULL;
//         strcpy(novo->ip, ipOrigem);
//         novo->acessos = 1;
//         (*controle) = 1;
//         return novo;
//     }
//     if(strcmp(raiz->ip, ipOrigem) == 0){
//         raiz->acessos += 1;
//         (*controle) = raiz->acessos;
//         return raiz;
//     }
//     if(strcmp(raiz->ip, ipOrigem) < 0){
//         raiz->esq = inserirReq(raiz->esq, ipOrigem, controle);
//     }
//     else{
//         raiz->dir = inserirReq(raiz->dir, ipOrigem, controle);
//     }
//     return raiz;
// }

int buscarDominio(p_no raiz, char ipOrigem[17], char dominio[101], int *retorno){  
    if(raiz == NULL || strcmp(raiz->dominio, dominio) == 0){
        if(raiz != NULL && strcmp(raiz->dominio, dominio) == 0){  
            printf("ACCEPTED %s FROM %s RESPOND %s\n", dominio, ipOrigem, raiz->IP);
            *retorno = 1;
        }
        return *retorno;
    }
    if(strcmp(dominio, raiz->dominio) < 0){
        buscarDominio(raiz->esq, ipOrigem, dominio, retorno);
    }
    else{
        buscarDominio(raiz->dir, ipOrigem, dominio, retorno);
    }
    return *retorno;
}

void destroiArvore(p_no raiz){
    if(raiz != NULL){
        destroiArvore(raiz->esq);
        destroiArvore(raiz->dir);
        free(raiz);
    }
}

void destroiArvore2(p_req raiz){
    if(raiz != NULL){
        destroiArvore2(raiz->esq);
        destroiArvore2(raiz->dir);
        free(raiz);
    }
}

void imprime(p_no raiz){
    if(raiz != NULL){
        imprime(raiz->esq);
        printf("%s\n", raiz->dominio);
        imprime(raiz->dir);
    }
}

int main(){
    int u, n, m;
    p_no raiz;
    raiz = NULL;
    scanf("%d", &u);
    scanf("%d", &n);
    raiz = recebeArvore(raiz, n);

    scanf("%d", &m);
    recebeRequest(raiz, m, u); 
    destroiArvore(raiz); 
}