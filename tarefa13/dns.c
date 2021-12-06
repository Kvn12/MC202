// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// //Struct para a arvore AVL de dominios.
// typedef struct No{ 
//     char IP[17]; 
//     char dominio[101];
//     int altura;
//     struct No *esq, *dir;
// } No;

// //Struct para a arvore AVL de requisitantes.
// typedef struct Requests{
//     char ip[17];
//     int acessos;
//     int altura;
//     struct Requests *esq, *dir;
// } Requests; 

// typedef No * p_no;
// typedef Requests * p_req;

// p_no recebeArvore(p_no raiz, int n);
// p_no inserir(p_no raiz, char IP[17], char dominio[101]);
// p_no rotacionaDir(p_no raiz);
// p_no rotacionaEsq(p_no raiz);
// int alt(p_no raiz);
// int max(int x, int y);
// int verBalanceamento(p_no raiz);
// void recebeRequest(p_no raiz, int m, int u);
// int buscarDominio(p_no raiz, char ipOrigem[17], char dominio[101], int *retorno);
// void destroiArvore(p_no raiz);
// void destroiArvore2(p_req raiz);
// p_req inserirReq(p_req raiz, char ipOrigem[17], int *controle);
// p_req rotacionaDir2(p_req raiz);
// p_req rotacionaEsq2(p_req raiz);
// int alt2(p_req raiz);
// int verBalanceamento2(p_req raiz);

// //Abre uma entrada para cada dominio e direciona os para serem inseridos em uma arvore balanceada AVL.
// p_no recebeArvore(p_no raiz, int n){
//     int i; 
//     char IP[17], dominio[101];
//     for(i=0;i < n;i++){
//         scanf("%s %s", dominio, IP);
//         raiz = inserir(raiz, IP, dominio);
//     }
//     return raiz;
// }

// //Insere recursivamente os novos dominios na arvore balanceada AVL.
// p_no inserir(p_no raiz, char IP[17], char dominio[101]){
//     p_no novo;
//     int balanceamento;
//     if(raiz == NULL){
//         novo = malloc(sizeof(No));
//         novo->esq = novo->dir = NULL;
//         novo->altura = 1;
//         strcpy(novo->IP, IP);
//         strcpy(novo->dominio, dominio);
//         return novo;
//     }
//     if(strcmp(dominio, raiz->dominio) < 0){
//         raiz->esq = inserir(raiz->esq, IP, dominio);
//     }
//     else {
//         raiz->dir = inserir(raiz->dir, IP, dominio);
//     }
//     //corrige a arvore
//     raiz->altura = 1 + max(alt(raiz->esq), alt(raiz->dir));
//     balanceamento = verBalanceamento(raiz);

//     if(balanceamento > 1 && strcmp(dominio, raiz->esq->dominio) < 0){
//         return rotacionaDir(raiz);
//     }
//     if(balanceamento < -1 && strcmp(dominio, raiz->dir->dominio) > 0){
//         return rotacionaEsq(raiz);
//     }
//     if(balanceamento > 1 && strcmp(dominio, raiz->esq->dominio) > 0){
//         raiz->esq = rotacionaEsq(raiz->esq);
//         return rotacionaDir(raiz);
//     }
//     if(balanceamento < -1 && strcmp(dominio, raiz->dir->dominio) < 0){
//         raiz->dir = rotacionaDir(raiz->dir);
//         return rotacionaEsq(raiz);
//     }
//     return raiz;
// }

// //Realiza a rotacao para a direita dos nos na arvore.
// p_no rotacionaDir(p_no raiz){
//     p_no x = raiz->esq;
//     p_no y = x->dir;

//     x->dir = raiz;
//     raiz->esq = y;

//     raiz->altura = max(alt(raiz->esq), alt(raiz->dir)) +1;
//     x->altura = max(alt(x->esq), alt(x->dir)) +1;
//     return x;
// }

// //Realiza a rotacao para a esquerda dos nos da arvore.
// p_no rotacionaEsq(p_no raiz){
//     p_no x = raiz->dir;
//     p_no y = x->esq;
    
//     x->esq = raiz;
//     raiz->dir = y;

//     raiz->altura = max(alt(raiz->esq), alt(raiz->dir)) +1;
//     x->altura = max(alt(x->esq), alt(x->dir)) +1;
//     return x;
// }

// //Recebe um no e devolve a sua altura.
// int alt(p_no raiz){
//     if(raiz == NULL){
//         return 0;
//     }
//     else{
//         return raiz->altura;
//     }
// }

// //Dados dois inteiros, compara-os e devolve o maior.
// int max(int x, int y){
//     if(x > y){
//         return x;
//     }
//     else{
//         return y;
//     }
// }

// //Dado um no, devolve a diferenca de alturas de seus nos filhos.
// int verBalanceamento(p_no raiz){
//     if(raiz == NULL){
//         return 0;
//     }
//     else{
//         return alt(raiz->esq) - alt(raiz->dir);
//     }
// }

// //Abre uma entrada para cada requerimento de acesso aos dominios, e insere os requisitantes em uma outra arvore balanceada AVL.
// void recebeRequest(p_no raiz, int m, int u){ 
//     p_req requests;
//     requests = NULL;
//     int i, retorno, controle;
//     char get[4], dominio[101], ipOrigem[17], from[5];
//     for(i=0;i < m;i++){
//         retorno = 0;
//         controle = 0;
//         scanf("%s %s %s %s", get, dominio, from, ipOrigem);
//         requests = inserirReq(requests, ipOrigem, &controle);
//         if(controle <= u){   
//             retorno = buscarDominio(raiz, ipOrigem, dominio, &retorno);
//             if(retorno == 0){
//                 printf("NOTFOUND %s FROM %s\n", dominio, ipOrigem);
//             }
//         }
//         else{
//             printf("FORBIDDEN %s FROM %s\n", dominio, ipOrigem);
//         }
//     }
//     destroiArvore2(requests);
// }

// //Procura recursivamente por um requisitante na arvore, se ele existir, aumenta em 1 o seu numero de acessos e copia esse numero 
// //para uma variavel controle, que sera usada na funcao anterior; porem se o requisitante nao existir, cria-se um novo no para ele
// //e insere-o de modo a manter o balanceamento da arvore.
// p_req inserirReq(p_req raiz, char ipOrigem[17], int *controle){
//     p_req novo;
//     int balanceamento;
//     if(raiz == NULL){
//         novo = malloc(sizeof(Requests));
//         novo->dir = novo->esq = NULL;
//         strcpy(novo->ip, ipOrigem);
//         novo->acessos = 1;
//         novo->altura = 1;
//         (*controle) = 1;
//         return novo;
//     }
//     if(strcmp(raiz->ip, ipOrigem) == 0){
//         raiz->acessos += 1;
//         (*controle) = raiz->acessos;
//         return raiz;
//     }
//     if(strcmp(ipOrigem, raiz->ip) < 0){
//         raiz->esq = inserirReq(raiz->esq, ipOrigem, controle);
//     }
//     else {
//         raiz->dir = inserirReq(raiz->dir, ipOrigem, controle);
//     }
//     //corrige a arvore
//     raiz->altura = 1 + max(alt2(raiz->esq), alt2(raiz->dir));
//     balanceamento = verBalanceamento2(raiz);

//     if(balanceamento > 1 && strcmp(ipOrigem, raiz->esq->ip) < 0){
//         return rotacionaDir2(raiz);
//     }
//     if(balanceamento < -1 && strcmp(ipOrigem, raiz->dir->ip) > 0){
//         return rotacionaEsq2(raiz);
//     }
//     if(balanceamento > 1 && strcmp(ipOrigem, raiz->esq->ip) > 0){
//         raiz->esq = rotacionaEsq2(raiz->esq);
//         return rotacionaDir2(raiz);
//     }
//     if(balanceamento < -1 && strcmp(ipOrigem, raiz->dir->ip) < 0){
//         raiz->dir = rotacionaDir2(raiz->dir);
//         return rotacionaEsq2(raiz);
//     }
//     return raiz;
// }

// //Realiza a rotacao para a direita dos nos na arvore dos requisitantes.
// p_req rotacionaDir2(p_req raiz){
//     p_req x = raiz->esq;
//     p_req y = x->dir;

//     x->dir = raiz;
//     raiz->esq = y;

//     raiz->altura = max(alt2(raiz->esq), alt2(raiz->dir)) +1;
//     x->altura = max(alt2(x->esq), alt2(x->dir)) +1;
//     return x;
// }

// //Realiza a rotacao para a esquerda dos nos na arvore dos requisitantes.
// p_req rotacionaEsq2(p_req raiz){
//     p_req x = raiz->dir;
//     p_req y = x->esq;

//     x->esq = raiz;
//     raiz->dir = y;

//     raiz->altura = max(alt2(raiz->esq), alt2(raiz->dir)) +1;
//     x->altura = max(alt2(x->esq), alt2(x->dir)) +1;
//     return x;
// }

// //Recebe um no da arvore de requisitantes e devolve a sua altura.
// int alt2(p_req raiz){
//     if(raiz == NULL){
//         return 0;
//     }
//     else{
//         return raiz->altura;
//     }
// }

// //Dado um no da arvore de requisitantes, devolve a diferenca de alturas de seus nos filhos.
// int verBalanceamento2(p_req raiz){
//     if(raiz == NULL){
//         return 0;
//     }
//     else{
//         return alt2(raiz->esq) - alt2(raiz->dir);
//     }
// }

// //Realiza uma busca binaria na arvore de dominios e imprime se o dominio foi encontrado.
// int buscarDominio(p_no raiz, char ipOrigem[17], char dominio[101], int *retorno){  
//     if(raiz == NULL || strcmp(raiz->dominio, dominio) == 0){
//         if(raiz != NULL && strcmp(raiz->dominio, dominio) == 0){  
//             printf("ACCEPTED %s FROM %s RESPOND %s\n", dominio, ipOrigem, raiz->IP);
//             *retorno = 1;
//         }
//         return *retorno;
//     }
//     if(strcmp(dominio, raiz->dominio) < 0){
//         buscarDominio(raiz->esq, ipOrigem, dominio, retorno);
//     }
//     else{
//         buscarDominio(raiz->dir, ipOrigem, dominio, retorno);
//     }
//     return *retorno;
// }

// //Libera a memoria alocada para a arvore de dominios.
// void destroiArvore(p_no raiz){
//     if(raiz != NULL){
//         destroiArvore(raiz->esq);
//         destroiArvore(raiz->dir);
//         free(raiz);
//     }
// }

// //Libera a memoria alocada para a arvore de requisitantes.
// void destroiArvore2(p_req raiz){
//     if(raiz != NULL){
//         destroiArvore2(raiz->esq);
//         destroiArvore2(raiz->dir);
//         free(raiz);
//     }
// }

// int main(){
//     int u, n, m;
//     p_no raiz;
//     raiz = NULL;

//     scanf("%d", &u);
//     scanf("%d", &n);
//     raiz = recebeArvore(raiz, n);
//     scanf("%d", &m);
//     recebeRequest(raiz, m, u); 
//     destroiArvore(raiz); 
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Cor {VERMELHO, PRETO};

//Struct para a arvore Rubro-Negra de dominios.
typedef struct No{ 
    char IP[17]; 
    char dominio[101];
    enum Cor cor;
    struct No *esq, *dir;
} No;

//Struct para a arvore Rubro-Negra de requisitantes.
typedef struct Requests{
    char ip[17];
    int acessos;
    enum Cor cor;
    struct Requests *esq, *dir;
} Requests; 

typedef No * p_no;
typedef Requests * p_req;

p_no recebeArvore(p_no raiz, int n);
p_no inserir(p_no raiz, char IP[17], char dominio[101]);
p_no rotacionaDir(p_no raiz);
p_no rotacionaEsq(p_no raiz);
void recebeRequest(p_no raiz, int m, int u);
int buscarDominio(p_no raiz, char ipOrigem[17], char dominio[101], int *retorno);
void destroiArvore(p_no raiz);
void destroiArvore2(p_req raiz);
p_req inserirReq(p_req raiz, char ipOrigem[17], int *controle);
p_req rotacionaDir2(p_req raiz);
p_req rotacionaEsq2(p_req raiz);
void sobeVemelho(p_no raiz);
int ehVemelho(p_no x);
int ehPreto(p_no x);
void sobeVemelho2(p_req raiz);
int ehVemelho2(p_req x);
int ehPreto2(p_req x);


//Abre uma entrada para cada dominio e direciona os para serem inseridos em uma arvore balanceada Rubro-Negra.
p_no recebeArvore(p_no raiz, int n){
    int i; 
    char IP[17], dominio[101];
    for(i=0;i < n;i++){
        scanf("%s %s", dominio, IP);
        raiz = inserir(raiz, IP, dominio);
    }
    return raiz;
}

//Insere recursivamente os novos dominios na arvore balanceada Rubro-Negra.
p_no inserir(p_no raiz, char IP[17], char dominio[101]){
    p_no novo;
    if(raiz == NULL){
        novo = malloc(sizeof(No));
        novo->esq = novo->dir = NULL;
        novo->cor = VERMELHO;
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
    if(ehVemelho(raiz->dir) && ehPreto(raiz->esq)){
        raiz = rotacionaEsq(raiz);
    }
    if(ehVemelho(raiz->esq) && ehVemelho(raiz->esq->esq)){
        raiz = rotacionaDir(raiz);
    }
    if(ehVemelho(raiz->esq) && ehVemelho(raiz->dir)){
        sobeVemelho(raiz);
    }
    return raiz;
}

//Realiza a rotacao para a direita dos nos na arvore.
p_no rotacionaDir(p_no raiz){
    p_no x = raiz->esq;
    raiz->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

//Realiza a rotacao para a esquerda dos nos da arvore.
p_no rotacionaEsq(p_no raiz){
    p_no x = raiz->dir;
    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

//Atualiza a cor da raiz e de seus filhos para manter a propriedade da arvore.
void sobeVemelho(p_no raiz){
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}

//Verifica se um no e vermelho e retorna a resposta.
int ehVemelho(p_no x){
    if(x == NULL){
        return 0;
    }
    return x->cor == VERMELHO;
}

//Verifica se um no e preto e retorna a resposta.
int ehPreto(p_no x){
    if(x == NULL){
        return 1;
    }
    return x->cor == PRETO;
}

//Abre uma entrada para cada requerimento de acesso aos dominios, e insere os requisitantes em uma outra arvore balanceada Rubro-Negra.
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

//Procura recursivamente por um requisitante na arvore, se ele existir, aumenta em 1 o seu numero de acessos e copia esse numero 
//para uma variavel controle, que sera usada na funcao anterior; porem se o requisitante nao existir, cria-se um novo no para ele
//e insere-o de modo a manter o balanceamento da arvore.
p_req inserirReq(p_req raiz, char ipOrigem[17], int *controle){
    p_req novo;
    if(raiz == NULL){
        novo = malloc(sizeof(Requests));
        novo->dir = novo->esq = NULL;
        strcpy(novo->ip, ipOrigem);
        novo->acessos = 1;
        novo->cor = VERMELHO;
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
    if(ehVemelho2(raiz->dir) && ehPreto2(raiz->esq)){
        raiz = rotacionaEsq2(raiz);
    }
    if(ehVemelho2(raiz->esq) && ehVemelho2(raiz->esq->esq)){
        raiz = rotacionaDir2(raiz);
    }
    if(ehVemelho2(raiz->esq) && ehVemelho2(raiz->dir)){
        sobeVemelho2(raiz);
    }
    return raiz;
}

//Realiza a rotacao para a direita dos nos na arvore.
p_req rotacionaDir2(p_req raiz){
    p_req x = raiz->esq;
    raiz->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

//Realiza a rotacao para a esquerda dos nos da arvore.
p_req rotacionaEsq2(p_req raiz){
    p_req x = raiz->dir;
    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return x;
}

//Atualiza a cor da raiz e de seus filhos para manter a propriedade da arvore.
void sobeVemelho2(p_req raiz){
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}

//Verifica se um no e vermelho e retorna a resposta.
int ehVemelho2(p_req x){
    if(x == NULL){
        return 0;
    }
    return x->cor == VERMELHO;
}

//Verifica se um no e preto e retorna a resposta.
int ehPreto2(p_req x){
    if(x == NULL){
        return 1;
    }
    return x->cor == PRETO;
}

//Realiza uma busca binaria na arvore de dominios e imprime se o dominio foi encontrado.
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

//Libera a memoria alocada para a arvore de dominios.
void destroiArvore(p_no raiz){
    if(raiz != NULL){
        destroiArvore(raiz->esq);
        destroiArvore(raiz->dir);
        free(raiz);
    }
}

//Libera a memoria alocada para a arvore de requisitantes.
void destroiArvore2(p_req raiz){
    if(raiz != NULL){
        destroiArvore2(raiz->esq);
        destroiArvore2(raiz->dir);
        free(raiz);
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