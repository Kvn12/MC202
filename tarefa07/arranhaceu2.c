#include <stdio.h>
#include <stdlib.h>

int conferir(int **tabuleiro, int **dicas, int n, int lin, int col, int predio);
int conferir_dicas_L(int **tabuleiro, int **dicas, int n, int lin);
int conferir_dicas_R(int **tabuleiro, int **dicas, int n, int lin);
int conferir_dicas_U(int **tabuleiro, int **dicas, int n, int col);
int conferir_dicas_D(int **tabuleiro, int **dicas, int n, int col);

void recebe_dicas(int **dicas, int n){
    int i, j;
    for(i=0;i < (n+2);i++){
        for(j=0;j < (n+2);j++){
            scanf("%d", &dicas[i][j]);
        }
    }
}
void imprimir(int **tabuleiro, int n){
    int i, j;
    for(i=0;i < n;i++){
        for(j=0;j < n;j++){
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int solucionaR(int **tabuleiro, int **dicas, int n, int lin, int col){ 
    int i, prox_lin, prox_col;
    prox_lin = 0;
    prox_lin = 0;

    if(lin==n){ //final
        imprimir(tabuleiro, n);
        return 1; 
    }
    //proximas coordenadas
    if(col == n-1){
        prox_lin = lin + 1;
        prox_col = 0;
    }
    else{
        prox_col = col + 1;
        prox_lin = lin;
    }
    //
    for(i=1;i <= n;i++){
        if(conferir(tabuleiro, dicas, n, lin, col, i)){      //ver se pd inserir
            tabuleiro[lin][col] = i;
            if(solucionaR(tabuleiro, dicas,n, prox_lin, prox_col)){ //chama recursivamente
                return 1;
            }
        }
    }
    tabuleiro[lin][col] = 0;
    return 0;
}

int conferir(int **tabuleiro, int **dicas, int n, int lin, int col, int predio){
    int i, j;

    for(i=0;i < n;i++){ //ve se ta na linha
        if(tabuleiro[lin][i]==predio){
            return 0;
        }
    }
    for(j=0;j < n;j++){ //ve se ta na coluna
        if(tabuleiro[j][col]==predio){
            return 0;
        }
    }
    if(!conferir_dicas_L(tabuleiro, dicas, n, lin)){
        return 0;
    }
    if(!conferir_dicas_R(tabuleiro, dicas, n, lin)){
        return 0;
    }
    if(!conferir_dicas_U(tabuleiro, dicas, n, col)){
        return 0;
    }
    if(!conferir_dicas_D(tabuleiro, dicas, n, col)){
        return 0;
    }
    
    return 1;
}

int conferir_dicas_L(int **tabuleiro, int **dicas, int n, int lin){
    int i, maior;
    int qtd_predios = 1;

    maior = tabuleiro[lin][0];
    for(i=1;i < n;i++){
        if(tabuleiro[lin][i] > maior){
            maior = tabuleiro[lin][i];
            qtd_predios += 1;
        }
    }
    if(dicas[lin][0] != qtd_predios){ // indice errado na dicas
    printf("%d\n", dicas[lin][0]);  
        return 0;
    }
    else{
        return 1;
    }
}

int conferir_dicas_R(int **tabuleiro, int **dicas, int n, int lin){
    int i, maior;
    int qtd_predios = 1;

    maior = tabuleiro[lin][0];
    for(i=n-1;i == 0;i--){
        if(tabuleiro[lin][i] > maior){
            maior = tabuleiro[lin][i];
            qtd_predios += 1;
        }
    }
    if(dicas[lin][n+1] != qtd_predios){
        return 0;
    }
    else{
        return 1;
    }
}

int conferir_dicas_U(int **tabuleiro, int **dicas, int n, int col){
    int i, maior;
    int qtd_predios = 1;

    maior = tabuleiro[0][col];
    for(i=1;i < n;i++){
        if(tabuleiro[i][col] > maior){
            maior = tabuleiro[i][col];
            qtd_predios += 1;
        }
    }
    if(dicas[0][col] != qtd_predios){
        return 0;
    }
    else{
        return 1;
    }
}

int conferir_dicas_D(int **tabuleiro, int **dicas, int n, int col){
    int i, maior;
    int qtd_predios = 1;

    maior = tabuleiro[0][col];
    for(i=n-1;i == 0;i--){
        if(tabuleiro[i][col] > maior){
            maior = tabuleiro[i][col];
            qtd_predios += 1;
        }
    }
    if(dicas[n+1][col] != qtd_predios){
        return 0;
    }
    else{
        return 1;
    }
}

void libera_mem(int **tabuleiro, int **dicas, int n){
    int i, j;
    for(i=0;i < n;i++){
        free(tabuleiro[i]);
    }
    free(tabuleiro);
    for(j=0;j < (n+2);j++){
        free(dicas[j]);
    }
    free(dicas);
}

int main(){
    int n, **tabuleiro, **dicas, i;
    scanf("%d", &n);
    tabuleiro = malloc(n*sizeof(int *));
    dicas = malloc((n+3)*sizeof(int *));
    for(i = 0;i < n; i++){
        tabuleiro[i] = calloc(n,sizeof(int));
    }
    for(i = 0;i < (n+3); i++){
        dicas[i] = malloc((n+3)*sizeof(int));
    }
    recebe_dicas(dicas, n);
    solucionaR(tabuleiro, dicas, n, 0, 0);
    libera_mem(tabuleiro, dicas, n);
    return 0;

}