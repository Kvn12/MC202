#include <stdio.h>
#include <stdlib.h>

#define PAI(i) ((i-1)/2)
#define F_ESQ(i) (2*i+1)
#define F_DIR(i) (2*i+2)

typedef struct {
    int id, prio, inc; 
} Pacote;

typedef struct {
    Pacote *v;
    int n, tamanho;
} fp;

typedef fp * p_fp;

p_fp mudaPrio(p_fp fila);
p_fp criaFila(int tamanho);
Pacote extraiMax(p_fp fila);
void troca(Pacote *x, Pacote *y);
void destroiFila(p_fp fila);
void tick(p_fp fila, int qtd, int nTick);
void sobeHeap(p_fp fila, int n);
void desceHeap(p_fp fila, int k);
void adicionaFila(p_fp fila, Pacote pacote);

/*Recebe o tamanho do Heap e cria-o.*/
p_fp criaFila(int tamanho){
    p_fp fila; 
    fila = malloc(sizeof(fp));
    fila->v = malloc(tamanho* sizeof(Pacote));
    fila->n = 0;
    fila->tamanho = tamanho;
    return fila;
}

/*Adiciona um pacote novo no Heap de modo a manter a propriedade do Max Heap.*/
void adicionaFila(p_fp fila, Pacote pacote){
    fila->v[fila->n] = pacote;
    fila->n++;
    sobeHeap(fila, fila->n - 1);
}

/*Recebe pacotes do Heap por referencia e troca as suas posicoes.*/
void troca(Pacote *x, Pacote *y){
    Pacote aux = *x;
    *x = *y;
    *y = aux;
}

/*Realiza a acao do Tick, de modo a retirar os qtd pacotes com prioridaded mais alta.*/
void tick(p_fp fila, int qtd, int nTick){
    int i;
    Pacote max;
    printf("TICK %d\n", nTick);
    for(i=0;i < qtd;i++){
        max = extraiMax(fila); 
        printf("%d %d %d\n", max.id, max.prio, max.inc);
    }
}

/*Extrai o primeiro pacote do Heap, que e o maior, e depois troca os outros pacotes e rearranja-os para manter a propriedade do Max Heap.*/
Pacote extraiMax(p_fp fila){
    Pacote max = fila->v[0];
    troca(&fila->v[0], &fila->v[fila->n -1]);
    fila->n--;
    desceHeap(fila, 0);
    return max;
}

/*Recebe o Heap e um inteiro n relativo a posicao do elemento a subir de posicao, e sobe-o de posicao de acordo com a propriedade de Max Heap.*/
void sobeHeap(p_fp fila, int n){
    if(n > 0 && fila->v[PAI(n)].prio < fila->v[n].prio){
        troca(&fila->v[n], &fila->v[PAI(n)]);
        sobeHeap(fila, PAI(n));
    }
}

/*Recebe o Heap e um inteiro n relativo a posicao do elemento a descer de posicao, e desce-o de posicao de acordo com a propriedade de Max Heap*/
void desceHeap(p_fp fila, int k){
    int maior;
    if(F_ESQ(k) < fila->n){
        maior = F_ESQ(k);
        if(F_DIR(k) < fila->n && fila->v[F_ESQ(k)].prio < fila->v[F_DIR(k)].prio){
            maior = F_DIR(k);
        }
        if(fila->v[k].prio <  fila->v[maior].prio){
            troca(&fila->v[k], &fila->v[maior]);
            desceHeap(fila, maior);
        }
    }
}

/*Percorre todos os pacotes restantes do heap e aumenta a prioridade de cada um.*/
p_fp mudaPrio(p_fp fila){
    int i;
    for(i=0;i < fila->n;i++){
        fila->v[i].prio += fila->v[i].inc;
        sobeHeap(fila, i);
    }
    return fila;
}

/*Libera a memoria alocada para o Heap*/
void destroiFila(p_fp fila){
    free(fila->v);
    free(fila);
}

int main(){
    int k , m, qtd, id, prio, inc, nTick;
    p_fp fila;
    Pacote pacote;

    scanf("%d %d", &k, &m);
    fila = criaFila(m);
    qtd = nTick = 0;

    while(scanf("%d %d %d", &id, &prio, &inc) != EOF){
        if(id == 0 && prio == 0 && inc == 0){ /*Tick*/ 
            nTick += 1;     
            if(qtd >= k){ /*Incrementa a prioridade dos remanescentes*/
                tick(fila, k, nTick);
                fila = mudaPrio(fila); 
                qtd = qtd - k; 
            }
            else{
                tick(fila, qtd, nTick);
                qtd = 0;
            }
        }
        else{ /*adiciona na Fila*/
            if(qtd < m){
                qtd += 1;
                pacote.id = id;
                pacote.inc = inc;
                pacote.prio = prio;
                adicionaFila(fila, pacote);
            }
        }
    }
    destroiFila(fila);
}
