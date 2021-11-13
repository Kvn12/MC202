#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>  

typedef struct {
    char palavra[50];
    int qtd;
} No;

typedef No * p_no;

p_no criaHash(p_no *nuvem, int tamanho);
p_no separar(p_no *nuvem, p_no *ordenar, int tamanhoNuvem);
p_no adicionaStop(p_no *nuvem, char palavra[50], int tamanho);
p_no adicionaNuvem(p_no *nuvem, char palavra[50], int tamanho, int *adicionados);
void imprimir(p_no *vetor);
void quickSort(p_no *vetor, int e, int d);
char convertePalavra(char palavra[50]);
int hash(char palavra[50], int tamanho);
int particiona(p_no *vetor, int e, int d);
int ehStopWord(p_no *StopWords, char palavra[50], int qtdStop);

/*Calcula p hash de determinada palavras pelo metodo da divisao.*/
int hash(char palavra[50], int tamanho){
    int i, n;
    n = 0;
    for(i=0; palavra[i] != '\0';i++){ 
        n = (256 * n + palavra[i]) % tamanho;
    }
    return n;
}

/*Percorre cada posicao do vetor e atribui NULL para cada posicao.*/
p_no criaHash(p_no *nuvem, int tamanho){ 
    int i;
    for(i=0;i < tamanho;i++){
        nuvem[i] = NULL;
    }
    return *nuvem;
}

/*Adiciona as palavras no vetor com base em seu hash, e se ja existir alguma palavras com aquele hash, adiciona no proximo espaco vazio do vetor.
Alem disso, adiciona 1 na variavel adicionados cada vez que uma nova palavra e adicionada.*/
p_no adicionaNuvem(p_no *nuvem, char palavra[50], int tamanho, int *adicionados){ 
    int n, i, j;
    p_no novo;
    n = hash(palavra, tamanho);
    
    if(nuvem[n] == NULL){
        novo = malloc(sizeof(No));
        novo->qtd = 1;
        strcpy(novo->palavra, palavra);
        nuvem[n] = novo;
        *adicionados += 1;
    }
    else if(strcmp(nuvem[n]->palavra, palavra) == 0){
        nuvem[n]->qtd += 1;
    }  
    else{
        for(i=n;i < tamanho;i++){ 
            if(nuvem[i] == NULL){
                novo = malloc(sizeof(No));
                novo->qtd = 1;
                strcpy(novo->palavra, palavra);
                nuvem[i] = novo;
                *adicionados += 1;
                return *nuvem;                
            }
            else if(strcmp(nuvem[i]->palavra, palavra) == 0){ 
                nuvem[i]->qtd += 1;
                return *nuvem;
            }
        }
        for(j=0;j < n;j++){
            if(nuvem[j] == NULL){
                novo = malloc(sizeof(No));
                novo->qtd = 1;
                strcpy(novo->palavra, palavra);
                nuvem[j] = novo;
                *adicionados += 1;
                return *nuvem;                
            }
            else if(strcmp(nuvem[j]->palavra, palavra) == 0){ 
                nuvem[j]->qtd += 1;
                return *nuvem;
            } 
        }
    }
    return *nuvem;
}

/*Adiciona as stopWords no vetor com base no seu hash, e se ja existir alguma palavra com aquele hash, adiciona no proximo espaco vazio do vetor.*/
p_no adicionaStop(p_no *stopWords, char palavra[50], int tamanho){ 
    int n, i, j;
    p_no novo;
    n = hash(palavra, tamanho);

    if(stopWords[n] == NULL){
        novo = malloc(sizeof(No));
        novo->qtd = 1;
        strcpy(novo->palavra, palavra);
        stopWords[n] = novo;
    }
    else if(strcmp(stopWords[n]->palavra, palavra) == 0){
        stopWords[n]->qtd += 1;
    }  
    else{
        for(i=n;i < tamanho;i++){ 
            if(stopWords[i] == NULL){
                novo = malloc(sizeof(No));
                novo->qtd = 1;
                strcpy(novo->palavra, palavra);
                stopWords[i] = novo;
                return *stopWords;                
            }
            else if(strcmp(stopWords[i]->palavra, palavra) == 0){ 
                stopWords[i]->qtd += 1;
                return *stopWords;
            }
        }
        for(j=0;j < n;j++){
            if(stopWords[j] == NULL){
                novo = malloc(sizeof(No));
                novo->qtd = 1;
                strcpy(novo->palavra, palavra);
                stopWords[j] = novo;
                return *stopWords;                
            }
            else if(strcmp(stopWords[j]->palavra, palavra) == 0){ 
                stopWords[j]->qtd += 1;
                return *stopWords;
            } 
        }
    }
    return *stopWords;
}

/*Procura uma palavra no vetor de hash stopwords, e se ela estiver la retorna 1.*/
int ehStopWord(p_no *StopWords, char palavra[50], int qtdStop){  
    int n, i, j;

    if(palavra[1] == '\0'){
        return 1;
    }

    n = hash(palavra, qtdStop);
    if(StopWords[n] == NULL){
        return 0;
    }
    else if(strcmp(StopWords[n]->palavra, palavra) == 0){
        return 1;
    }  
    else{
        for(i=n;i < qtdStop;i++){ 
            if(StopWords[i] == NULL){
                return 0;                
            }
            else if(strcmp(StopWords[i]->palavra, palavra) == 0){ 
                return 1;
            }
        }
        for(j=0;j < n;j++){
            if(StopWords[j] == NULL){
                return 0;                
            }
            else if(strcmp(StopWords[j]->palavra, palavra) == 0){ 
                return 1;
            } 
        }
    }
    return 0;
}

/*Recebe um vetor de caracteres, tira os caracteres que nao sao letras e converte as letras maiusculas em minusculas.*/
char convertePalavra(char palavra[50]){
    int i, j;
    for(i=0;palavra[i] != '\0';i++){
        if(!isalpha(palavra[i])){
            for(j=i;palavra[j] != '\0';j++){
                palavra[j] = palavra[j+1];
            }
            i -= 1;
        }
        else if(isupper(palavra[i])){
            palavra[i] = tolower(palavra[i]);
        }
    }
    return palavra[50];
}

/*Percorre o vetor nuvem, que possui muitos espacos vazios, e os termos que nao sao vazios sao adicionados no vetor ordenar.*/
p_no separar(p_no *nuvem, p_no *ordenar, int tamanhoNuvem){
    int i, k;
    k = 0;
    for(i=0;i < tamanhoNuvem;i++){
        if(nuvem[i] != NULL){
            ordenar[k] = nuvem[i];
            k +=1;
        }
    }
    return *ordenar;
}

/*Ordena o vetor em ordem decressiva pelo metodo quicksort.*/
void quickSort(p_no *vetor, int e, int d){
    int i;
    if(d <= e){
        return;
    }
    i = particiona(vetor, e, d);
    quickSort(vetor, e, i-1);
    quickSort(vetor, i+1, d);
}

/*Particiona o vetor e ordena os termos em ordem decressiva em funcao a um pivo do vetor para ordena-los com base no valor 'qtd', e se este for igual, 
ordena lexicograficamente.*/
int particiona(p_no *vetor, int e, int d){
    int i, pos = d+1;
    int pivo = vetor[e]->qtd;
    p_no aux;
    for(i=d;i > e;i--){
        if(vetor[i]->qtd < pivo || (vetor[i]->qtd == pivo && strcmp(vetor[i]->palavra, vetor[e]->palavra) > 0)){
            pos -= 1;
            aux = vetor[pos];
            vetor[pos] = vetor[i];  
            vetor[i] = aux;
        }
    }
    aux = vetor[pos-1];
    vetor[pos-1] = vetor[e];
    vetor[e] = aux;
    return pos-1;
}

/*Recebe um vetor e imprime os 50 primeiros termos, que sao os maiores.*/
void imprimir(p_no *vetor){
    int i;
    for(i=0;i < 50;i++){
        printf("%s %d\n", vetor[i]->palavra, vetor[i]->qtd);
    }
}

/*Recebe um vetor alocado dinamicamente e libera a memoria alocada.*/
void liberaMem(p_no *vetor, int tamanho){
    int i;
    for(i=0;i < tamanho;i++){
        if(vetor[i] != NULL){
        free(vetor[i]);
        }
    }
    free(vetor);
}

int main(){
    int i, qtdPalavras, qtdStopWords, adicionados = 0;;
    char stopWord[50], palavra[50];
    p_no *stop, *nuvem, *ordenar;
  
    scanf("%d", &qtdPalavras);
    scanf("%d", &qtdStopWords);

    stop = malloc(qtdStopWords*sizeof(p_no));  
    nuvem = malloc(qtdPalavras*sizeof(p_no));
    *nuvem = criaHash(nuvem, qtdPalavras);
    *stop = criaHash(stop, qtdStopWords);

    /*Recebe StopWords*/
    for(i=0;i < qtdStopWords;i++){ 
        scanf("%s", stopWord);
        *stop = adicionaStop(stop, stopWord, qtdStopWords);
    }
    /*Recebe as palavras*/
    while(scanf("%s", palavra) != EOF){ 
        palavra[50] = convertePalavra(palavra); 
        if(!ehStopWord(stop, palavra, qtdStopWords)){
            *nuvem = adicionaNuvem(nuvem, palavra, qtdPalavras, &adicionados); 
        }
    }

    ordenar = malloc(adicionados*sizeof(p_no));
    *ordenar = separar(nuvem, ordenar, qtdPalavras);
    quickSort(ordenar, 0, adicionados-1); 
    imprimir(ordenar);  

    liberaMem(nuvem, qtdPalavras);
    liberaMem(stop, qtdStopWords);
    free(ordenar);
}