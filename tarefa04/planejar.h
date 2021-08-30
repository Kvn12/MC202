typedef struct data {
    int dia;
    int mes;
    int ano;
    int soma_data;
} Data;

typedef struct voo {
    int numero_voo;
    float valor;
    char codigo_de_origem[4];
    char codigo_de_destino[4];
    int cancelado;
    Data data_saida;

} Voo; 

Data ler_data(char data_voo[]);

int soma_datas(Data data1);

int compara_data(Data data1, Data data2);

int diferenca_data(Data data1, Data data2);

void cancelar(Voo voos[], int qtd_voos, int numero_voo);

void alterar(Voo voos[], int qtd_voos, int numero_voo, float novo_valor);

void planejar(Voo voos[], int qtd_voos, Data data_inicio, Data data_fim, char codigo_origem[], int retorno[]);

void verifica_viabilidade(Voo voos_partida[], Voo voos_retorno[], int qtd_partida, int qtd_retorno, Data data_inicio, Data data_fim, int retorno[]);
