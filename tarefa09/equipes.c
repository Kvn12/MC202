#include <stdio.h>
#include <stdlib.h>

typedef struct No{ 
    int altura;
    struct No *direita; 
    struct No *esquerda;
} No;

typedef No* p_no;

p_no inserir(p_no circulo, p_no novo, int m);
p_no selecionaEsquerda(p_no equipe1,  p_no *circulo, int sortEsq);
p_no selecionaDireita(p_no equipe2,  p_no *circulo, int sortDir);
p_no adicionaEquipe(p_no equipe, p_no novo);

void imprimir(p_no equipe){
    p_no atual;
    for(atual=equipe;atual->direita != equipe;atual=atual->direita){ 
        printf("%d\t", atual->altura);
    }
    printf("%d\t", atual->altura);
}

p_no inserir(p_no circulo, p_no novo, int m){
    int cont = 0;
    p_no atual;
    atual = malloc(sizeof(No));
    for(atual=circulo;atual != NULL;atual = atual->direita){
        cont += 1;
        if(atual->direita == NULL){
            novo->esquerda = atual;
            atual->direita = novo;
            if(cont == m-1){    // ver se eh m msm
                novo->direita = circulo;
                circulo->esquerda = novo;
            }
            return circulo;
        }
    }
    novo->direita = circulo;
    return novo;
}

void selecionaEquipes(p_no equipe1, p_no equipe2, p_no circulo, int m){
    int i, sorteios[1000];
    for(i=0;i < m;i++){
        scanf("%d", &sorteios[i]);
    }
    for(i=0;i < m;i++){
        if((i+1)%2 != 0){           //corre para a esquerda
        // printf("esquerda, %d\n", sorteios[i]);
        equipe1 = selecionaEsquerda(equipe1, &circulo, sorteios[i]);
        }
        else{                       //corre para a direita
        // printf("direita, %d\n", sorteios[i]);
        equipe2 = selecionaDireita(equipe2, &circulo, sorteios[i]);   
        } 
    }
    imprimir(equipe1);  
    printf("\n");
    imprimir(equipe2); 
}

p_no selecionaEsquerda(p_no equipe1,  p_no *circulo, int sortEsq){
    int i;
    p_no atual;
    p_no novo;
    novo = malloc(sizeof(No));
    atual = *circulo;
    for(i=1;i < sortEsq;i++){   
        atual = atual->esquerda;
    }
    if(atual == *circulo){ //selecionou o primeiro
        *circulo = (*circulo)->direita;
        atual->direita->esquerda = atual->esquerda;
        atual->esquerda->direita = atual->direita;               
        novo->altura = atual->altura;
        // printf("if %d\n", novo->altura);
        // circulo = atual->direita;
        free(atual);
    }
    else{
        atual->direita->esquerda = atual->esquerda;
        atual->esquerda->direita = atual->direita;               
        novo->altura = atual->altura;
        // printf("else %d\n", novo->altura);
        free(atual);
    }
    //adiciona na equipe
    return adicionaEquipe(equipe1, novo);
    // if(equipe1==NULL){
    //     novo->direita = equipe1;
    //     return novo;
    // }
    // else{
    //     for(aux=equipe1;aux != NULL;aux=aux->direita){
    //         if(aux->direita==NULL){
    //             novo->direita = NULL;
    //             aux->direita = novo;
    //             return equipe1;
    //         }
    //     }
    // }
    // return 0;
}

p_no selecionaDireita(p_no equipe2,  p_no *circulo, int sortDir){
    int i;
    p_no atual;
    p_no novo;
    novo = malloc(sizeof(No));
    // if(circulo->esquerda == circulo){
    //     return equipe2;
    // }
    atual = *circulo;
    for(i=1;i < sortDir;i++){   
        atual = atual->direita;
    }
    if(atual==*circulo){ //selecionou o primeiro
        atual->direita->esquerda = atual->esquerda;
        atual->esquerda->direita = atual->direita;   
        novo->altura = atual->altura;
        *circulo = (*circulo)->direita;
        // printf("if %d\n", novo->altura);
        free(atual);
    }    
    else{
        // printf("1\n");
        atual->direita->esquerda = atual->esquerda;
        // printf("2\n");
        atual->esquerda->direita = atual->direita;  
        // printf("3\n"); 
        novo->altura = atual->altura;
        // printf("else %d\n", novo->altura);
        free(atual);
    }
    return adicionaEquipe(equipe2, novo);
}
    
p_no adicionaEquipe(p_no equipe, p_no novo){    //adiciona na equipe 
    p_no aux;

    if(equipe==NULL){ //se for adicionar o 1
        novo->direita = equipe;
        return novo;
    }
    else{
        if(equipe->direita==NULL){ //se for adicionar o 2
            if(novo->altura >= equipe->altura){ //se o novo for maior q o 1
                equipe->direita = novo;
                equipe->esquerda = novo;
                novo->direita = equipe;
                novo->esquerda = equipe;
                return equipe; 
            }
            else{   //se o 2 for menor q o 1
                novo->direita = equipe;
                novo->esquerda = equipe;
                equipe->esquerda = novo;
                equipe->direita = novo;
                return novo;
            }

        }
        else{  //se for adicionar a partir do 2
            for(aux=equipe;aux->direita != equipe;aux=aux->direita){  
                if(aux->altura >= novo->altura){
                    if(aux == equipe){  //se for entrar em primeiro
                        novo->esquerda = aux->esquerda;
                        novo->direita = aux;
                        aux->esquerda->direita = novo;
                        aux->esquerda = novo;
                        return novo; 
                    }
                    else{
                        novo->esquerda = aux->esquerda;
                        novo->direita = aux;
                        aux->esquerda->direita = novo;
                        aux->esquerda = novo;
                        return equipe;  
                    }
                }
            }
            //aux é o ultimo nesse caso
            if(aux->altura >= novo->altura){ 
                novo->esquerda = aux->esquerda;
                novo->direita = aux;
                aux->esquerda->direita = novo;
                aux->esquerda = novo;
                return equipe;
            }
            else{
                novo->direita = aux->direita;
                novo->esquerda = aux;
                aux->direita->esquerda = novo;
                aux->direita = novo;
                return equipe;
            }
        }
    }
    return 0;
}

p_no cria(){
    return NULL;
}

void destruirEquipes(p_no equipe){
    //libera a memoria alocada para as equipes
    p_no atual;
    for(atual=equipe;atual->direita != equipe;atual=atual->direita){ 
        free(atual);
    }
    free(atual);
}

int main(){
    int m, i;
    p_no circulo, equipe1, equipe2;
    circulo = malloc(sizeof(No));
    equipe1 = malloc(sizeof(No));
    equipe2 = malloc(sizeof(No));
    circulo = cria();
    equipe1 = cria();
    equipe2 = cria();
    scanf("%d", &m);
    for(i=0;i < m;i++){
        p_no novo;
        novo = malloc(sizeof(No));
        novo->direita = NULL;
        scanf("%d", &novo->altura);
        circulo = inserir(circulo, novo, m);
    }
    selecionaEquipes(equipe1, equipe2, circulo, m);
    destruirEquipes(equipe1);
    destruirEquipes(equipe2); 
}