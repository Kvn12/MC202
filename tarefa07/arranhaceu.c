#include <stdio.h>
#include <stdlib.h>

int conferir(int **tabuleiro, int n, int lin, int col, int predio);
int conferir_dicas_L(int **tabuleiro, int n, int lin, int col);
int conferir_dicas_R(int **tabuleiro, int n, int lin);
int conferir_dicas_U(int **tabuleiro, int n, int col, int lin);
int conferir_dicas_D(int **tabuleiro, int n, int col);

void recebe_dicas(int **tabuleiro, int n){
    //Recebe os valores do scanf em um ponteiro de ponteiros, uma matriz, que representa o tabuleiro do jogo.
    int i, j;
    for(i=0;i < (n+2);i++){
        for(j=0;j < (n+2);j++){
            scanf("%d", &tabuleiro[i][j]);
        }
    }
}
void imprimir(int **tabuleiro, int n){
    //Imprime a matriz, tabuleiro do jogo.
    int i, j;
    for(i=1;i < n+1;i++){
        for(j=1;j < n+1;j++){
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int solucionaR(int **tabuleiro, int n, int lin, int col){ 
    //Função recursiva que completa o tabuleiro de acordo com as regras, 
    //e se for preciso desfaz alguns passos até encontrar uma solução, backtracking.
    int i, prox_lin, prox_col;
    prox_lin = 0;
    prox_col = 0;

    if(lin == (n+1)){ //final
        imprimir(tabuleiro, n);
        return 1; 
    }
    //proximas coordenadas
    if(col == n){
        prox_lin = lin + 1;
        prox_col = 1;
    }
    else{
        prox_col = col + 1;
        prox_lin = lin;
    }
    //
    for(i=1;i <= n;i++){
        if(conferir(tabuleiro, n, lin, col, i)){      //ve se pd inserir
            if(solucionaR(tabuleiro, n, prox_lin, prox_col)){ //chama recursivamente
                return 1;
            }
        }
    }
    tabuleiro[lin][col] = 0; //falhou posteriormente, retorna o valor incial 0, e tenta o próximo número.
    return 0;
}

int conferir(int **tabuleiro, int n, int lin, int col, int predio){
    //Recebe o tabuleiro e o valor a ser inserido, confere nas linhas e nas colunas se o valor não esta presente,
    //se não o estiver, adiciona-o e confere esse valor com as dicas.
    int i, j;
    
    for(i=1;i < n+1;i++){ //ve se ta na linha
        if(tabuleiro[lin][i]==predio){
            return 0;
        }
    }
    for(j=1;j < n+1;j++){ //ve se ta na coluna
        if(tabuleiro[j][col]==predio){
            return 0;
        }
    }
    tabuleiro[lin][col] = predio;
    if(!conferir_dicas_L(tabuleiro, n, lin, col)){ //Confere com as dicas da esquerda na linha.
        return 0;
    }
    if(!conferir_dicas_U(tabuleiro, n, col, lin)){ //Confere com as dicas de cima na coluna.
        return 0;
    }
    if(col == n && !conferir_dicas_R(tabuleiro, n, lin)){ //Confere com as dicas da direita na linha.
        return 0;
    }
    if(lin == n && !conferir_dicas_D(tabuleiro, n, col)){ //Confere com as dicas de baixo na coluna. 
        return 0;
    }
    return 1;
}

int conferir_dicas_L(int **tabuleiro, int n, int lin, int col){
    //Procura quantos prédios são visíveis pela esquerda na linha. 
    //Se a quantidade de prédios visíveis for maior, retorna 0.
    int i, maior;
    int qtd_predios = 1;

    maior = tabuleiro[lin][1];
    for(i=2;i < n+1;i++){
        if(tabuleiro[lin][i] > maior){
            maior = tabuleiro[lin][i];
            qtd_predios += 1;
        }
        if(tabuleiro[lin][0] < qtd_predios){ 
            return 0;
        }
    }
    if(n == col){
        if(tabuleiro[lin][0] == qtd_predios){
            return 1;
        }
        else{
            return 0;
        }
    }
    return 1;

}

int conferir_dicas_R(int **tabuleiro, int n, int lin){
    //Procura quantos prédios são visíveis pela direita na linha. 
    //Se a quantidade de prédios visíveis for maior, retorna 0.
    int i, maior;
    int qtd_predios = 1;

    maior = tabuleiro[lin][n];
    for(i=n-1;i > 0;i--){ 
        if(tabuleiro[lin][i] > maior){
            maior = tabuleiro[lin][i];
            qtd_predios += 1;
        }
        if(tabuleiro[lin][n+1] < qtd_predios){ 
            return 0;
        }
    }
    if(tabuleiro[lin][n+1] == qtd_predios){ 
        return 1;
    }
    else{
        return 0; 
    }
    
}

int conferir_dicas_U(int **tabuleiro, int n, int col, int lin){
    //Procura quantos prédios são visíveis de cima para baixo na coluna. 
    //Se a quantidade de prédios visíveis for maior, retorna 0.
    int i, maior;
    int qtd_predios = 1;

    maior = tabuleiro[1][col];
    for(i=2;i < n+1;i++){
        if(tabuleiro[i][col] > maior){
            maior = tabuleiro[i][col];
            qtd_predios += 1;
        }
        if(tabuleiro[0][col] < qtd_predios){ 
            return 0;
        }
    }
    if(n == lin){
        if(tabuleiro[0][col] == qtd_predios){
            return 1;
        }
        else{
            return 0;
        }
    }
    return 1;
}

int conferir_dicas_D(int **tabuleiro, int n, int col){
    //Procura quantos prédios são visíveis de baixo para cima na coluna. 
    //Se a quantidade de prédios visíveis for maior, retorna 0.
    int i, maior;
    int qtd_predios = 1;

    maior = tabuleiro[n][col];
    for(i=n-1;i > 0;i--){
        if(tabuleiro[i][col] > maior){
            maior = tabuleiro[i][col];
            qtd_predios += 1;
        }
        if(tabuleiro[n+1][col] < qtd_predios){ 
            return 0;
        }
    }
    if(tabuleiro[n+1][col] == qtd_predios){
        return 1;
    }
    else{
        return 0; 
    }
}

void libera_mem(int **tabuleiro, int n){
    //Recebe a matriz de ponteiros e libera a memória alocada.
    int j;
    for(j=0;j < (n+3);j++){
        free(tabuleiro[j]);
    }
    free(tabuleiro);
}

int main(){
    int n, **tabuleiro, i;
    scanf("%d", &n);
    tabuleiro = malloc((n+3)*sizeof(int *));
    for(i = 0;i < (n+3); i++){
        tabuleiro[i] = malloc((n+3)*sizeof(int));
    }
    recebe_dicas(tabuleiro, n);
    solucionaR(tabuleiro, n, 1, 1); 
    libera_mem(tabuleiro, n);
    return 0;
}