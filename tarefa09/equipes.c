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

void destruirEquipes(p_no equipe){
    //libera a memoria alocada para as equipes
    p_no atual;
    p_no aux;
    atual = equipe;
    while(atual->direita != equipe){
        aux = atual->direita;
        free(atual);
        atual = aux;
    }
    free(atual);
}

void imprimir(p_no equipe){
    //Imprimi as equipes
    p_no atual;
    for(atual=equipe;atual->direita != equipe;atual=atual->direita){ 
        printf("%d\t", atual->altura);
    }
    printf("%d\t", atual->altura);
}

p_no inserir(p_no circulo, p_no novo, int m){
    //insere novos integrantes a roda inicial de amigos
    int cont = 0;
    p_no atual;
    // atual = malloc(sizeof(No));
    for(atual=circulo;atual != NULL;atual = atual->direita){
        cont += 1;
        if(atual->direita == NULL){
            novo->esquerda = atual;
            atual->direita = novo;
            if(cont == m-1){    
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
    //Recebe os sorteios que serao feitos e separa o circulo de amigos em duas equipes
    int i, sorteio;
    for(i=0;i < m;i++){
        scanf("%d", &sorteio);
        if((i+1)%2 != 0){           //corre para a esquerda
        equipe1 = selecionaEsquerda(equipe1, &circulo, sorteio);
        }
        else{                       //corre para a direita
        equipe2 = selecionaDireita(equipe2, &circulo, sorteio);   
        } 
    }
    imprimir(equipe1);  
    printf("\n");
    imprimir(equipe2); 
    destruirEquipes(equipe1);
    destruirEquipes(equipe2);
}

p_no selecionaEsquerda(p_no equipe1,  p_no *circulo, int sortEsq){
    //Recebe a posicao do integrante q sera sorteado e tira-o do circulo inicial e coloca-o na equipe 1.
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
        free(atual);
    }
    else{
        atual->direita->esquerda = atual->esquerda;
        atual->esquerda->direita = atual->direita;               
        novo->altura = atual->altura;
        free(atual);
    }
    return adicionaEquipe(equipe1, novo);
}

p_no selecionaDireita(p_no equipe2,  p_no *circulo, int sortDir){
    //Recebe a posicao do integrante q sera sorteado e tira-o do circulo inicial e coloca-o na equipe 2.
    int i;
    p_no atual;
    p_no novo;
    novo = malloc(sizeof(No));

    atual = *circulo;
    for(i=1;i < sortDir;i++){   
        atual = atual->direita;
    }
    if(atual==*circulo){ //selecionou o primeiro
        atual->direita->esquerda = atual->esquerda;
        atual->esquerda->direita = atual->direita;   
        novo->altura = atual->altura;
        *circulo = (*circulo)->direita;
        free(atual);
    }    
    else{
        atual->direita->esquerda = atual->esquerda;
        atual->esquerda->direita = atual->direita;  
        novo->altura = atual->altura;
        free(atual);
    }
    return adicionaEquipe(equipe2, novo);
}
    
p_no adicionaEquipe(p_no equipe, p_no novo){    //adiciona na equipe 
    //Recebe a equipe e o novo integrante a ser adicionado, e adiciona-o em uma posição de acordo com sua altura
    //de modo que os integrantes fiquem em ordem crescente de altura.
    p_no aux;

    if(equipe==NULL){ //se for adicionar o 1
        equipe = novo;
        equipe->direita = novo;
        equipe->esquerda = novo;
        return novo;
    }
    else{
        if(equipe->direita==equipe){ //se for adicionar o 2
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

int main(){
    int m, i;
    p_no circulo, equipe1, equipe2;
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
}