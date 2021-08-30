#include <stdio.h>
#include <string.h>
#include "planejar.h"
#define TAMANHO_VETOR 100

int main(){ 
    char registrar[10] = {"registrar"};
    char alterar_vet[10] = {"alterar"};
    char cancelar_vet[10] = {"cancelar"};
    char planejar_vet[10] = {"planejar"};
    char instrucao[10];
    char planejar_origem[4];
    char data_voo[11];
    char data_primeiro[11];
    char data_ultimo[11];
    Voo voos[TAMANHO_VETOR]; 
    int qtd_voos = 0;
    int alterar_codigo, alterar_valor, cancelar_codigo;
    int retorno[2]; 
    Data inicio_ferias;
    Data final_ferias;
    // int valor_data1, valor_data2, valor_data3;

    while(1){ 
        scanf("%s", instrucao);
        if(strcmp(instrucao, registrar)==0){ //registrar
            scanf("%d", &voos[qtd_voos].numero_voo); //passando a posiçao, qndo for passar o tamanho, passar qtd+1
            scanf("%s %s", voos[qtd_voos].codigo_de_origem, voos[qtd_voos].codigo_de_destino);
            scanf("%s", data_voo);
            voos[qtd_voos].data_saida = ler_data(data_voo);                                  
            scanf("%f", &voos[qtd_voos].valor);
            qtd_voos += 1;
        }
        if(strcmp(instrucao, alterar_vet)==0){  //alterar
            scanf("%d %d", &alterar_codigo, &alterar_valor);
            alterar(voos, qtd_voos+1, alterar_codigo, alterar_valor);
        }
        if(strcmp(instrucao, cancelar_vet)==0){ //cancelar
            scanf("%d", &cancelar_codigo);
            cancelar(voos, qtd_voos+1, cancelar_codigo);
            qtd_voos -= 1;   
        }
        if(strcmp(instrucao, planejar_vet)==0){ //planejar
            scanf("%s", planejar_origem);
            scanf("%s %s", data_primeiro, data_ultimo);//data
            inicio_ferias = ler_data(data_primeiro);  
            final_ferias = ler_data(data_ultimo); 
            planejar(voos, qtd_voos, inicio_ferias, final_ferias, planejar_origem, retorno);  
            printf("%d\n", retorno[0]);
            printf("%d", retorno[1]);
            break;
        }
    }
    return 0;
}