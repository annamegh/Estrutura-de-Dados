#define MAX_PILHA 50
#define ERRO_PILHA_VAZIA -1
#define ERRO_PILHA_CHEIA -2

//STRUCTS SÃO DEFINIDAS NO .h
typedef struct{
    int dados[MAX_PILHA]; // dados da pilha
    int topo; // índice do topo
} Pilha;

void inicializa_pilha ( Pilha *p );
int pilha_vazia ( Pilha p );
int pilha_cheia ( Pilha p );
int empilha ( Pilha *p, int info ) ;
int desempilha ( Pilha *p, int *info );
int le_topo ( Pilha p, int *info );
void mostra_pilha ( Pilha p );
