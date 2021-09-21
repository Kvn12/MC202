#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{ 
    int documento;
    int lanterna;   
    char profissao[100];
    char estadoVacinacao[13];
    struct No *prox; 
} No;

typedef No* p_no;

p_no adiciona_comeco(p_no fila, int documento, char profissao[100], char estadoVacincao[13]);
p_no adiciona_lanterna(p_no fila, int documento, char profissao[100], char estadoVacincao[13]);
p_no adiciona_fim(p_no fila, int documento, char profissao[100], char estadoVacincao[13]);
p_no tiraNaoVacinados(p_no proximos);

p_no adiciona(p_no fila, int documento, char profissao[100], char estadoVacincao[13]){
    //recebe as informaçoes da pessoa e decide em qual local da fila ela será adicionada
    char coach[6] = {"coach"};
    char exbbb[7] = {"ex-bbb"};
    char filhoPolitico[15] = {"filho-politico"};
    char herdeiro[9] = {"herdeiro"};
    char youtuberFinancas[20] = {"youtuber-financas"};
    char funcionario[12] = {"funcionario"};

    if(strcmp(profissao, funcionario)==0){                               //vai pro final
        return adiciona_fim(fila, documento, profissao, estadoVacincao);
    }
    if(strcmp(profissao, coach)==0 || strcmp(profissao, exbbb)==0 || strcmp(profissao, filhoPolitico)==0 || strcmp(profissao, herdeiro)==0 ||
    strcmp(profissao, youtuberFinancas)==0){                             //vai pro começo
        return adiciona_comeco(fila, documento, profissao, estadoVacincao);
    }
    else{                                                                //Vai pra lanterna  
        return adiciona_lanterna(fila, documento, profissao, estadoVacincao);
    }
}

p_no adiciona_comeco(p_no fila, int documento, char profissao[100], char estadoVacincao[13]){ 
    //adiciona no começo da fila e esta pessoa recebe a lanterna
    p_no novo;
    p_no atual;
    novo = malloc(sizeof(No));
    novo->documento = documento;
    strcpy(novo->profissao, profissao);
    strcpy(novo->estadoVacinacao, estadoVacincao);
    novo->lanterna = 1;
    for(atual=fila;atual != NULL;atual = atual->prox){  
        if(atual->lanterna == 1){
            atual->lanterna = 0;
            break;
        }
    }
    novo->prox = fila; 
    return novo;
}

p_no adiciona_lanterna(p_no fila, int documento, char profissao[100], char estadoVacincao[13]){ 
    //adiciona a pessoa logo atras da que está com a lanterna, e essa recebe a lanterna
    char fiscal[7] = {"fiscal"};
    char Vacinado[9] = {"vacinado"};
    p_no atual;
    p_no novo;
    novo = malloc(sizeof(No));
    novo->documento = documento;
    strcpy(novo->profissao, profissao);
    strcpy(novo->estadoVacinacao, estadoVacincao);
    novo->lanterna = 1;
    for(atual=fila;atual != NULL;atual = atual->prox){  
        if(atual->lanterna == 1){ 
            atual->lanterna = 0;     
            if(strcmp(atual->profissao, fiscal)==0){               //lanterna e fiscal
                if(strcmp(novo->estadoVacinacao, Vacinado) == 0){  //novo ta vacinado, logo entra na fila
                    novo->prox = atual->prox;
                    atual->prox = novo;
                    return fila;
                }
                else{                                              //o novo n ta vacinado, entao n entra
                    atual->lanterna = 1;
                    return fila;
                }
            }  
            if(strcmp(novo->profissao, fiscal)==0){                //adiciona o fiscal e os atras dele vazzam
                novo->prox = tiraNaoVacinados(atual->prox);    
                atual->prox = novo;
                return fila;
            }
            else{
                novo->prox = atual->prox;
                atual->prox = novo;
                return fila;
            }                              
        }
    }
    novo->prox = fila;
    return novo;    
}

p_no adiciona_fim(p_no fila, int documento, char profissao[100], char estadoVacincao[13]){
    //adiciona a pessoa no fim da fila, e esta recebe a lanterna
    p_no novo;
    p_no atual;
    novo = malloc(sizeof(No));
    novo->documento = documento;
    strcpy(novo->profissao, profissao);
    strcpy(novo->estadoVacinacao, estadoVacincao);
    novo->lanterna = 1;
    novo->prox = NULL;
    if(fila == NULL){
        novo->prox = fila;
        return novo;
    }
    for(atual=fila;atual != NULL;atual = atual->prox){  
        if(atual->lanterna == 1){
            atual->lanterna = 0;
        }
        if(atual->prox == NULL){
            atual->prox = novo;
            return fila;
        }
    }
    return 0;
}

p_no tiraNaoVacinados(p_no proximos){ 
    //retorna o proximo depois do fiscal que está vacinado
    char Vacinado[9] = {"vacinado"};
    p_no aux;
    for(aux=proximos;aux != NULL;aux = aux->prox){
        if(strcmp(aux->estadoVacinacao, Vacinado) == 0){
            return aux;
        }
    }
    return NULL;
}

p_no criarFila(){
    return NULL;
}

void impressao(p_no fila){ 
    //imprime a fila
    p_no atual;
    for(atual=fila; atual != NULL; atual = atual->prox){
        printf("%d %s %s\n", atual->documento, atual->profissao, atual->estadoVacinacao);
    }
}

void destruir(p_no fila){
    //libera a memoria alocada para a fila
    if(fila != NULL){
        destruir(fila->prox);
        free(fila);
    }
}

int main(){
    p_no fila;    
    int documento = 0;
    char profissao[100], estadoVacinacao[13];
    fila = criarFila();
    while(scanf("%d %s %s", &documento, profissao, estadoVacinacao) != EOF){   
        fila = adiciona(fila, documento, profissao, estadoVacinacao);
    }
    impressao(fila);
    destruir(fila);
    return 0;
}