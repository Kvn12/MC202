#include <stdio.h>
#include <stdlib.h>
#include "minecraft.h"

int **calcularAltitudes(int m, int n, int seed){ 
    int a, h, x, z, **altitudes;

    altitudes = malloc(m*sizeof(int*));
    for(a=0;a < m;a++){
        altitudes[a] = malloc(n*sizeof(int));
    }
    for(x=0;x < m;x++){
        for(z=0;z < n;z++){
            h = (seed*(202+x+z) + 12345 + x + z)%256;
            altitudes[x][z] = h;
        }
    }
    return altitudes;
}

Bloco ***criarMundo(int m, int n, int **altitudes, int seed){ 
    int h, M, x, z, y;
    Bloco ***mundo;

    mundo = malloc(m*sizeof(Bloco **));
    for(x=0;x < m;x++){
        mundo[x] = malloc(n*sizeof(Bloco *));
        for(z=0;z < n;z++){
            mundo[x][z] = malloc(256*sizeof(Bloco));
            h = altitudes[x][z];
            for(y=0;y < 256;y++){ 
                if(y > h){
                    mundo[x][z][y].tipo = 21;
                }
                else{      
                    M = ((seed*(202+x+y+z))+x+y+z)%33;
                    mundo[x][z][y].tipo = M;
                }
            }
        } 
    }
    return mundo;
}

double explorarMundo(Bloco ***mundo, int m, int n, int **altitudes, double tempoPorBloco, int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBlocos){
    int h, M, x, y, z, qtdPedra, qtdTerra;
    double tempoTotal;
    qtdPedra = qtdTerra = 0;

    for(x=0;x < m;x++){
        for(z=0;z < n;z++){
            h = altitudes[x][z];
            for(y=0;y < 256;y++){ 
                if(y <= h){
                    M = mundo[x][z][y].tipo;
                    if(M==0){ //dima
                        *qtdDiamante += 1;
                    }
                    if(M==1 || M==2){ //ouro
                        *qtdOuro += 1;
                    }
                    if(M >=3 && M <= 5){ //Ferro
                        *qtdFerro += 1;
                    }
                    if(M >=6 && M <= 11){ //pedra
                        qtdPedra += 1;
                    }
                    if(M >= 12 && M <= 20){ //terra
                        qtdTerra += 1;
                    }
                }
            }
        }
    }     
    *qtdBlocos = qtdPedra + qtdTerra + *qtdDiamante + *qtdFerro + *qtdOuro;
    tempoTotal = tempoPorBloco * (*qtdBlocos);
    return tempoTotal;
}

void imprimir(int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBlocos, double tempoTotal){
    printf("Total de Blocos: %d\n", *qtdBlocos);
    printf("Tempo total: %.2fs\n", tempoTotal);
    printf("Diamantes: %d\n", *qtdDiamante);
    printf("Ouros: %d\n", *qtdOuro);
    printf("Ferros: %d\n", *qtdFerro);
}

void destruirMundo(Bloco ***mundo, int **altitudes, int m, int n){//recebe todos os ponteiros e da free
    int x,z;
    for(x=0;x < m;x++){
        for(z=0;z < n;z++){
            free(mundo[x][z]);
        }
        free(mundo[x]);
        free(altitudes[x]);
    }
    free(mundo);
    free(altitudes);
}

int main(){
    int m, n, seed, **altitudes;
    double tempoPorBloco, tempoTotal;
    Bloco ***retorno;
    int qtdDima = 0;
    int qtdOuro = 0;
    int qtdFerro = 0;
    int qtdBlocos = 0;

    scanf("%d %d", &m, &n);
    scanf("%d", &seed);
    scanf("%lf", &tempoPorBloco);
    altitudes = calcularAltitudes(m, n, seed); 
    retorno = criarMundo(m, n, altitudes, seed); 
    tempoTotal = explorarMundo(retorno, m, n, altitudes, tempoPorBloco, &qtdDima, &qtdOuro, &qtdFerro, &qtdBlocos);
    imprimir(&qtdDima, &qtdOuro, &qtdFerro, &qtdBlocos, tempoTotal);
    destruirMundo(retorno, altitudes, m, n);
}