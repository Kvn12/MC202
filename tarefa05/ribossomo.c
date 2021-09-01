#include <stdio.h>
#include <stdlib.h>

typedef struct padrao{
    char *DNA, *RNA;
} Padrao;

typedef struct alien{
    char *DNA, *RNA, *ID;
} Alien;

Alien transcreve(Padrao padrao, Alien alien, int n){ 
    int i, j, cont;                                                                                     
    for(i=0;i < 14;i++){
        cont = 0;
        for(j=0;j < n;j++){
            if(padrao.DNA[i] == alien.DNA[j]){
                alien.RNA[j] = padrao.RNA[i];;   
                alien.ID[j] = cont; 
                cont += 1;
            }
        }
    }
    return alien;
}

void imprimir(Alien alien, int n){
    int i;
    printf("ID:\t\t");
    for(i=0;i < n;i++){ //rever esse range
        printf("%d\t", alien.ID[i]);
    }
    printf("\n");
    printf("DNA:\t");
    for(i=0;i < n;i++){ 
        printf("%c\t", alien.DNA[i]);
    }
    printf("\n");
    printf("\t\t");
    for(i=0;i < n;i++){     //barrinhas
        printf("|\t");
    }
    printf("\n");
    printf("RNA:\t");
    for(i=0;i < n;i++){ 
        printf("%c\t", alien.RNA[i]);
    }
} 
int main(){
    Padrao padrao;
    Alien alien;
    Alien retorno;
    int n;
    padrao.DNA = malloc(14*sizeof(char)); 
    padrao.RNA = malloc(14*sizeof(char));
    scanf("%s", padrao.DNA);
    scanf("%s", padrao.RNA);
    scanf("%d", &n);
    alien.DNA = malloc((n+1)*sizeof(char)); //talvez colocar n+1
    alien.RNA = malloc((n+1)*sizeof(char));
    alien.ID = malloc((n+1)*sizeof(char));
    if(alien.DNA==NULL){
        printf("Não há memória suficiente\n");
        exit(1);
    }
    scanf("%s", alien.DNA);
    retorno = transcreve(padrao, alien, n+1);
    imprimir(retorno, n);
    free(padrao.DNA);
    free(padrao.RNA);
    free(alien.DNA);
    free(alien.RNA);
    free(alien.ID);
    free(retorno.DNA);
    free(retorno.RNA);
    free(retorno.ID);
}