// Constantes de erro
#define ERRO_LDE_VAZIA	-1
#define ERRO_POS_INVALIDA	-2

// EleDuplo de LDE
typedef struct ele {
	void *info;
	struct ele *suc, *ant;
} EleDuplo;

// Cabeçalho de LDE
typedef struct {
	EleDuplo *cabeca;
	int tamInfo, qtd;
} LDE;

void inicializa_LDE( LDE *p, int t ); //nao muda
int LDE_vazia ( LDE l ); //nao muda
int insere_inicio( LDE *p, void *info ); //arruamda
int remove_inicio( LDE *p, void *info ); //arrumada
int insere_fim( LDE *p, void *info ); //arrumada
int remove_fim( LDE *p, void *info ); //nao muda
int insere_pos( LDE *p, void *info , int pos ); //arrumada
int remove_pos( LDE *p, void *info , int pos ); //arrumada
int le_valor( LDE l, void *info , int pos ); //nao muda
int modifica_valor( LDE l, void *info , int pos ); //nao muda
void mostra_LDE( LDE l, void (*mostra)(void *) ); //nao muda
void limpa_LDE( LDE *l ); //nao muda
int insere_ordem( LDE *p, void *info, int (*compara)(void*, void*) ); //nao muda

int conta_EleDuplos( LDE l ); // Função inútil na prática, pois temos o campo 'qtd'.

