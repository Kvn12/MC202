#include <string.h>
#include <stdio.h>
#include "planejar.h"
#define TAMANHO_VETOR 100

// Data ler_data(char data_voo[], Voo voos[], int qtd_voos)
Data ler_data(char data_voo[]){
    Data data1;    
    int dia = 0;
    int mes = 0;
    int ano = 0;
    dia += 10*(data_voo[0] - '0');//dia
    dia += 1*(data_voo[1] - '0');//dia

    mes += 10*(data_voo[3] - '0');//mes
    mes += 1*(data_voo[4] - '0');//mes

    ano += 1000*(data_voo[6] - '0');//ano
    ano += 100*(data_voo[7] - '0');//ano
    ano += 10*(data_voo[8] - '0');//ano
    ano += 1*(data_voo[9] - '0');//ano

    data1.dia = dia;
    data1.mes = mes;
    data1.ano = ano;
    // printf("Dia %d\n", dia);             
    // printf("Mes %d\n", mes);             
    // printf("Ano %d\n", ano);   
    // printf("\n");                       
    data1.soma_data = soma_datas(data1);
    return data1;
   
}
int soma_datas(Data data1){
    int soma = 0;
    soma += data1.dia;
    if(data1.mes==2){
        soma += 31;
    }   if(data1.mes==3){
        soma += 59;
    }   if(data1.mes==4){
        soma += 90;
    }   if(data1.mes==5){
        soma += 120;
    }   if(data1.mes==6){
        soma += 151;
    }   if(data1.mes==7){
        soma += 181;
    }   if(data1.mes==8){
        soma += 212;
    }   if(data1.mes==9){
        soma += 243;
    }   if(data1.mes==10){
        soma += 273;
    }   if(data1.mes==11){
        soma += 304;
    }   if(data1.mes==12){
        soma += 334;
    }
    if(data1.ano==2022){
        soma += 365;
    }
    // printf("teste somadatas %d\n", soma);             
    return soma;
}

int compara_data(Data data1, Data data2){ //data1 antes q data2 retorna 1
    // printf("teste datas1 %d\n", data1.soma_data);
    // printf("teste datas2 %d\n", data2.soma_data);    
    // printf("\n");
    if(data1.soma_data <= data2.soma_data){        
        return 1;
    }
    else{
        return 0;
    }
}

int diferenca_data(Data data1, Data data2){ //data2 - data 1 >= 4 dias  retorna o tempo
    return data2.soma_data - data1.soma_data;  
}

void cancelar(Voo voos[], int qtd_voos, int numero_voo){
    int i, j, indice;
    for(i=0;i < qtd_voos;i++){
        if(voos[i].numero_voo == numero_voo){
            indice = i;
            break;
        }
    }//atribuir atributo cancelado
    for(j=indice;j < qtd_voos-1;j++){ //talvez esse raciocinio dê problema
        voos[j] = voos[j+1];
    }
}

void alterar(Voo voos[], int qtd_voos, int numero_voo, float novo_valor){ //documentar
    int i;
    for(i=0;i < qtd_voos;i++){
        if(voos[i].numero_voo == numero_voo){
            voos[i].valor = novo_valor;
            break;
        }
    }
}

void planejar(Voo voos[], int qtd_voos, Data data_inicio, Data data_fim, char codigo_origem[], int retorno[]){  // documentar
    Voo voos_partida[TAMANHO_VETOR];
    Voo voos_retorno[TAMANHO_VETOR];
    int i, qtd_partida, qtd_retorno;
    qtd_partida = qtd_retorno = 0;
    for(i=0;i < qtd_voos;i++){
        if(strcmp(voos[i].codigo_de_origem, codigo_origem)==0){ //msm origem
            if(compara_data(data_inicio, voos[i].data_saida) == 1){ //data dps inicio ferias
                voos_partida[qtd_partida] = voos[i];                
                qtd_partida += 1;  
            }
        }
        if(strcmp(voos[i].codigo_de_destino, codigo_origem)==0){
            if(compara_data(voos[i].data_saida, data_fim)==1){
                voos_retorno[qtd_retorno] = voos[i];
                qtd_retorno += 1;                       
            }
        }
    }
    verifica_viabilidade(voos_partida, voos_retorno, qtd_partida, qtd_retorno, data_inicio, data_fim, retorno);
}
//    printf("teste 1 %d\n", qtd_partida);
//     printf("teste 2 %d\n", qtd_retorno);

void verifica_viabilidade(Voo voos_partida[], Voo voos_retorno[], int qtd_partida, int qtd_retorno, Data data_inicio, Data data_fim, int retorno[]){
    int i, j, qtd_possibilidades;
    int possibilidades[100][4];
    int aux[100][3];
    qtd_possibilidades = 0;
    int k, l;
    float valor_partida, valor_retorno, soma_valor;
    
    for(i=0;i < qtd_partida;i++){ //combinar os destinos e procurar o melhor preço
        for(j=0;j < qtd_retorno;j++){ //ver questao de tempo de viagem > diferenca_data
            valor_partida = 0;
            valor_retorno = 0;
            soma_valor = 0;
            if(strcmp(voos_partida[i].codigo_de_destino, voos_retorno[j].codigo_de_origem)==0){  //ver valor primeiro
                if(diferenca_data(voos_partida[i].data_saida, voos_retorno[j].data_saida)>=4){
                    possibilidades[qtd_possibilidades][0] = voos_partida[i].numero_voo;
                    possibilidades[qtd_possibilidades][1] = voos_retorno[j].numero_voo;
                    valor_partida = voos_partida[i].valor; 
                    valor_retorno = voos_retorno[j].valor;
                    soma_valor = valor_partida + valor_retorno;
                    possibilidades[qtd_possibilidades][2] = soma_valor;
                    // printf("Valores 2: %f\n", soma_valor);
                    // printf("Valores 3: %f\n", possibilidades[qtd_possibilidades][2]);
                    qtd_possibilidades += 1;
                    
                }
            }                          
        }
    }
    // printf("Possibilidades: %d\n", qtd_possibilidades);
    
    for(k=qtd_possibilidades-1;k > 0;k--){
        for(l=0;l < k-1;k++){
            if(possibilidades[k][2] < possibilidades[k+1][2]){
                aux[j][0] = possibilidades[k][0]; 
                possibilidades[k][0] = possibilidades[k+1][0];     
                possibilidades[k+1][0] = aux[j][0];

                aux[j][1] = possibilidades[k][1]; 
                possibilidades[k][1] = possibilidades[k+1][1];     
                possibilidades[k+1][1] = aux[j][1];

                aux[j][2] = possibilidades[k][2]; 
                possibilidades[k][2] = possibilidades[k+1][2];     
                possibilidades[k+1][2] = aux[j][2];
            }
        }
    }
    retorno[0] = possibilidades[0][0]; 
    retorno[1] = possibilidades[0][1];

// diff "testes\registrar1.out" "testes\registrar1.res"
}