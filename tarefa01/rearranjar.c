#include <stdio.h>
#include <math.h>
#define TAMANHO_VETOR 10000

int ve_indice(int fila[], int n, int j);
int * le_movimentacoes(int m, int n, int fila[]);

void cria_fila(int fila[], int n){
    int j;
    for(j=0; j < n; j++){
        fila[j] = j+1;
    }
}

int * le_movimentacoes(int m, int n, int fila[]){
    int i, j, p, a, b, var;
    for(i=0; i < m; i++){ 
        scanf("%d %d %d", &p, &a, &b);
        int ind_a = ve_indice(fila, n, a);
        int ind_b = ve_indice(fila, n, b);
        int tamanho_troca = ind_b - ind_a;
        int ultimo = ind_b;

        if(p==1){                                   //inverte a ordem dos q estao no meio
            for(j=ind_a; j <= (ind_a + (tamanho_troca/2)); j++){
                var = fila[j];
                fila[j] = fila[ultimo]; 
                fila[ultimo] = var;
                ultimo --;
                }
            }
          
        if(p==2){                                       //esperar pela outra pessoa, diminuir o indice de cada e o A vai pra dps do B
            for(j=ind_a; j < (ind_a + tamanho_troca); j++){   //tirar o a, corre a lista e devolve ele      
                fila[j] = fila[j+1];

            }
            fila[ind_b] = a;  
        }  
    }
    return fila;
}
int ve_indice(int fila[], int n, int j){
    int i;
    for(i=0; i < n; i++){
        if(fila[i]==j){
            return i;
        }
    }
    return 0;
}

void imprime(int fila[], int n){
    int k;
    for(k=0; k < n;k++){
    printf("%d ",fila[k]);
    }
}

int main(){
    int n, m, fila[TAMANHO_VETOR], * vetor;
    scanf("%d", &n);                 //recebe a quantidade de posiçoes na fila
    scanf("%d", &m);                 //recebe a quantidade de mudanças q serão feitas
    cria_fila(fila, n);
    vetor = le_movimentacoes(m, n, fila);
    imprime(vetor, n);
}