#include <stdio.h>
#include <string.h>
#define TAMANHO_VETOR 100 

int recebe_nomes(int n, char indicador[10], char homo[10], char paren[10], char nomes[TAMANHO_VETOR][31], char impressao[TAMANHO_VETOR][31], char referencia[TAMANHO_VETOR][31]);
int procura(int k, char impressao[TAMANHO_VETOR][31], char nome[31]);

int recebe_nomes(int n, char indicador[10], char homo[10], char paren[10], char nomes[TAMANHO_VETOR][31], char impressao[TAMANHO_VETOR][31], char referencia[TAMANHO_VETOR][31]){
    int i, ih, j, a, b, k, cont, q, w, cont2;
    char aux;
    k = 0;
    char comparar[TAMANHO_VETOR][31];

    for(i=0;i < n;i++){
        scanf("%s", nomes[i]);
    }
    if(strcmp(indicador, homo) == 0){ // Achar Homonimos
        for(ih=0;ih < n;ih++){
            for(j=0;nomes[ih][j] != '_';j++){
                comparar[ih][j] = nomes[ih][j];
            }
            comparar[ih][j] = '\0';
        }
        for(a=0;a < n-1;a++){
            for(b=a+1;b < n;b++){  
                if(strcmp(comparar[a], comparar[b]) == 0){ //se forem homonimos
                    if(procura(k, impressao, nomes[a])!=1){  
                        strcpy(impressao[k], nomes[a]);
                        k +=1;
                    }
                    if(procura(k, impressao, nomes[b])!=1){
                        strcpy(impressao[k], nomes[b]);
                        k +=1;
                    }
                } 
            }
        }     
    }

    if(strcmp(indicador, paren) == 0){ // Achar Parentes 
        for(ih=0;ih < n;ih++){
            cont = 0;
            for(j=strlen(nomes[ih])-1;nomes[ih][j] != '_';j--){
                comparar[ih][cont] = nomes[ih][j]; 
                cont += 1;
            }         
            comparar[ih][cont] = '\0';
        }
        for(q=0;q < n;q++){  // inverte os caracteres do sobrenome
            cont2 = strlen(comparar[q])-1;
            for(w=0; w < strlen(comparar[q])/2; w++){
                aux = comparar[q][w];
                comparar[q][w] = comparar[q][cont2]; 
                comparar[q][cont2] = aux;
                cont2 --;
            }
        }
        for(a=0;a < n-1;a++){
            for(b=a+1;b < n;b++){  
                if(strcmp(comparar[a], comparar[b]) == 0){ //se forem parentes
                    if(procura(k, impressao, nomes[a])!=1){  
                        strcpy(impressao[k], nomes[a]);
                        strcpy(referencia[k], comparar[a]);
                        k +=1;
                    }
                    if(procura(k, impressao, nomes[b])!=1){
                        strcpy(impressao[k], nomes[b]);
                        strcpy(referencia[k], comparar[b]);
                        k +=1;
                    }
                } 
            }
        }     

    }
    return k;
}

int procura(int k, char impressao[TAMANHO_VETOR][31], char nome[31]){
    int i;
    for(i=0;i < k;i++){
        if(strcmp(nome, impressao[i])==0){
            return 1;
        }
    }
    return 0;
}

void ordena_homonimos(char impressao[TAMANHO_VETOR][31], int k){
    int i, j;
    char aux[TAMANHO_VETOR][31];
    for(i=k;i > 0;i--){
        for(j=0;j < i-1;j++){
            if(strcmp(impressao[j], impressao[j+1]) > 0){
                strcpy(aux[j], impressao[j]);
                strcpy(impressao[j], impressao[j+1]);
                strcpy(impressao[j+1], aux[j]);
            }
        }
    }
}

void ordena_parentes(char impressao[TAMANHO_VETOR][31], int k, char referencia[TAMANHO_VETOR][31]){
    int i, j, a, b, cont, ih, jh;
    char aux[TAMANHO_VETOR][31];
    char aux2[TAMANHO_VETOR][31];
    char aux3[TAMANHO_VETOR][31];
    char aux4[TAMANHO_VETOR][31];
    char referencia_nome[TAMANHO_VETOR][31];
    char referencia_sobrenome[TAMANHO_VETOR][31];
    
    for(i=k;i > 0;i--){ //ordena o sobrenome
        for(j=0;j < i-1;j++){
            if(strcmp(referencia[j], referencia[j+1]) > 0){
                //muda a impressao
                strcpy(aux[j], impressao[j]);
                strcpy(impressao[j], impressao[j+1]);
                strcpy(impressao[j+1], aux[j]);
                //muda a referencia
                strcpy(aux2[j], referencia[j]);
                strcpy(referencia[j], referencia[j+1]);
                strcpy(referencia[j+1], aux2[j]);
            }
        }
    }
    for(a=0;a < k;a++){ //pega so o nome
        for(b=0;impressao[a][b] != '_';b++){
            referencia_nome[a][b] = impressao[a][b];
        }
        referencia_nome[a][b] = '\0';
    }
    for(ih=0;ih < k;ih++){ //pega so o sobrenome
            referencia_sobrenome[ih][strlen(impressao[ih])] = '\0';
            cont = 0;
            for(jh=strlen(impressao[ih])-1;impressao[ih][jh] != '_';jh--){
                referencia_sobrenome[ih][cont] = impressao[ih][jh]; 
                cont += 1;
            }         
        }


    for(i=k;i > 0;i--){ //ordena o nome
        for(j=0;j < i-1;j++){
            if(strcmp(referencia_nome[j], referencia_nome[j+1]) > 0){  
                if(strcmp(referencia_sobrenome[j], referencia_sobrenome[j+1])==0){ //se tiver o msm sobrenome
                //muda a impressao
                strcpy(aux3[j], impressao[j]);
                strcpy(impressao[j], impressao[j+1]);
                strcpy(impressao[j+1], aux3[j]);
                //muda a referencia_nome
                strcpy(aux4[j], referencia_nome[j]);
                strcpy(referencia_nome[j], referencia_nome[j+1]);
                strcpy(referencia_nome[j+1], aux4[j]);
                }
            }
        }
    }        
}

void imprimir(int k, char impressao[TAMANHO_VETOR][31]){
    int i;
    for(i=0; i < k; i++){
        printf("%s\n", impressao[i]);
    }
}

int main(){
    int n;
    char indicador[10];
    char homo[10] = {"homonimos"};
    char paren[10] = {"parentes"};
    char nomes[TAMANHO_VETOR][31];
    char impressao[TAMANHO_VETOR][31];
    char referencia[TAMANHO_VETOR][31];
    scanf("%d", &n);
    scanf("%s", indicador);
    int k = recebe_nomes(n, indicador, homo, paren, nomes, impressao, referencia);
    if(strcmp(indicador, homo) == 0){
        ordena_homonimos(impressao, k);
    }
    if(strcmp(indicador, paren) == 0){
        ordena_parentes(impressao, k, referencia);
    }
    imprimir(k, impressao);
    return 0;
}