#include <stdio.h>
#define TAMANHO_VETOR 1000

void recebe_rendimentos(int n, double funcionarios[][16]){
    double a, b, c, d, e, f, g, h, ih, jh, k, l, abate;
    int i;
    for(i=0; i < n; i++){
        scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f, &g, &h, &ih, &jh, &k, &l);
        funcionarios[i][0]=a;
        funcionarios[i][1]=b;
        funcionarios[i][2]=c;
        funcionarios[i][3]=d;
        funcionarios[i][4]=e;
        funcionarios[i][5]=f; 
        funcionarios[i][6]=g; 
        funcionarios[i][7]=h; 
        funcionarios[i][8]=ih; 
        funcionarios[i][9]=jh; 
        funcionarios[i][10]=k; 
        funcionarios[i][11]=l; 
    }
    for(i=0; i < n; i++){
        scanf("%lf", &abate);
        funcionarios[i][15] = abate; 
        }
}
void calcula_imposto(int n, double funcionarios[][16]){
    int i, j;
    double aux = 0.00;
    double total = 0.00;
    double retido = 0.00;
    double f1 = 0.00;
    double f2 = 0.00;
    double f3 = 0.00;
    double f4 = 0.00;
    double f5 = 0.00;
    for(i=0; i < n; i++){               //soma o rendimento total de cada funcionario
        total = 0;
        for(j=0; j < 12; j++){
            total += funcionarios[i][j];
        }
        funcionarios[i][13] = total;  //redimento total
    }
    for(i=0; i < n; i++){  //calcula a aliquota de cada mes           
        for(j=0; j < 12; j++){
        f1 = 0;
        f2 = 0;
        f3 = 0;
        f4 = 0;
        f5 = 0; 
            aux = funcionarios[i][j];
            if(aux > 3743.19){ 
                f5 = (aux-3743.19)*0.275;  
                aux = 3743.19;
            }
            if(aux > 2995.70){              
                f4 = (aux-2995.70)*0.225;     
                aux = 2995.70;   
            }
            if(aux > 2246.75){ 
                f3 = (aux-2246.75)*0.15; 
                aux = 2246.75;   
            }
            if(aux > 1499.15){
                f2 = (aux-1499.15)*0.075;    
                aux = 1499.15;
            }
            if(aux <= 1499.15){
                f1 = 0;    
            }
            funcionarios[i][j] = f1+f2+f3+f4+f5;  
        }
    }
    for(i=0; i < n; i++){  //calcula o total retido
        retido = 0;
        for(j=0; j < 12; j++){
            retido += funcionarios[i][j];
        }
        funcionarios[i][12] = retido; 
    }
    for(i=0; i < n; i++){  //calcula o imposto anual devido
        f1 = 0;
        f2 = 0;
        f3 = 0;
        f4 = 0;
        f5 = 0; 
        aux = funcionarios[i][13]-funcionarios[i][15]; 
        if(aux > 44400.0){
            f5 = (aux-44400.0)*0.275; 
            aux = 44400.0;
        }
        if(aux > 36000.0){                       
            f4 = (aux-36000.0)*0.225; 
            aux = 36000.0;
        }
        if(aux > 26400.0){
            f3 = (aux-26400.0)*0.15; 
            aux = 26400.0;
        }
        if(aux > 18000.0){
            f2 = (aux-18000.0)*0.075;
            aux = 18000.0;  
        }
        if(aux <= 18000.0){
            f1 = 0;
        }
        funcionarios[i][13] = f1+f2+f3+f4+f5; //anual devido
    }        
    for(i=0; i < n; i++){  //calcula o ajuste
        funcionarios[i][14] = funcionarios[i][13] - funcionarios[i][12];
    }
}
void saida(int n, double funcionarios[][16], char meses[][7]){
    int l, k;
    int i, j;
    for(k=0; k < 15; k++){
        for(l=0; meses[k][l] != '\0'; l++){   
        printf("%c", meses[k][l]);
        }
        printf("\t");
    } 
    printf("\n");
    for(i=0; i < n; i++){
        for(j=0; j < 15; j++){
            printf("%.2f\t", funcionarios[i][j]);
        }
        printf("\n");
    }
}
int main(){
    int n; 
    double funcionarios[TAMANHO_VETOR][16];
    char meses[15][7] = {{"Jan"}, {"Fev"}, {"Mar"}, {"Abr"}, {"Mai"}, {"Jun"}, {"Jul"}, {"Ago"}, {"Set"}, {"Out"}, {"Nov"}, {"Dez"}, {"Retido"}, {"Devido"}, {"Ajuste"}};
    scanf("%d", &n);
    recebe_rendimentos(n, funcionarios);
    calcula_imposto(n, funcionarios);
    saida(n, funcionarios, meses);
    return 0;
}