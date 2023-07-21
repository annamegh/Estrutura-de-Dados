#define ERRO_PILHA_VAZIA -1
#define ERRO_PILHA_CHEIA -2

//STRUCTS SÃO DEFINIDAS NO .h
typedef struct{
    int *dados; // dados da pilha
    int topo; // índice do topo
    int capacidade;
} Pilha;

void inicializa_pilha ( Pilha *p, int c );
int pilha_vazia ( Pilha p );
int pilha_cheia ( Pilha p );
int empilha ( Pilha *p, int info ) ;
int desempilha ( Pilha *p, int *info );
int le_topo ( Pilha p, int *info );
void mostra_pilha ( Pilha p );
void desaloca_pilha ( Pilha *p); //necessário para ponteiros

void concatena( Pilha *p1, Pilha *p2 );

