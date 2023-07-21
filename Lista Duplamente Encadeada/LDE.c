#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LDE.h"

//Privado------------------------

EleDuplo *aloca_EleDuplo( void *info, int tam ) {
	EleDuplo *p = malloc( sizeof(EleDuplo) );
	if( p == NULL )
		return NULL; // Erro, falta de memória!
	p->info = malloc( tam );
	if( p->info == NULL ){
		free(p);
		return NULL; // Erro, falta de memória!
	}
	memcpy(p->info, info, tam);
	return p; // Sucesso!
}

//-------------------------------


void inicializa_lista( Lista *p, int t ){
	p->tamInfo = t;
	p->cabeca = NULL;
	p->qtd = 0;
}

int lista_vazia ( Lista l ){
	return l.cabeca == NULL;
}

int insere_inicio( Lista *p, void *info ){
	EleDuplo *novo = aloca_EleDuplo( info, p->tamInfo );
	if( novo == NULL )
		return 0; // Erro, falta de memória!

	novo->suc = p->cabeca;
	p->cabeca = novo;
	p->qtd++;
	novo->ant = NULL;
	if(novo->suc != NULL) {
        novo->suc->ant = novo; //ou = p->cabeca
	}
	return 1; // Sucesso!
}

int remove_inicio( Lista *p, void *info ){
	if( lista_vazia( *p ) )
		return ERRO_LISTA_VAZIA;

	EleDuplo *aux = p->cabeca;
	memcpy( info, aux->info, p->tamInfo );
	p->cabeca = aux->suc;
	free( aux->info );
	free( aux );
	p->qtd--;
	if(p->cabeca != NULL) {
        p->cabeca->ant = NULL;
	}
	return 1; // Sucesso!
}

int insere_fim( Lista *p, void *info ){
	if( lista_vazia( *p ) )
		return insere_inicio( p, info );

	EleDuplo *aux = p->cabeca;
	while( aux->suc != NULL )
		aux = aux->suc;

	EleDuplo *novo = aloca_EleDuplo( info, p->tamInfo );
	if( novo == NULL )
    	return 0; // Erro, falta de memória!

	aux->suc = novo;
	novo->suc = NULL;
	novo->ant = aux; //checar se funciona!
	p->qtd++;

	return 1; // Sucesso!
}

int remove_fim( Lista *p, void *info ){
   if( lista_vazia( *p ) )
      return ERRO_LISTA_VAZIA;
   if( p->qtd == 1 )
      return remove_inicio( p, info );
   EleDuplo *aux = p->cabeca;
   while( aux->suc->suc != NULL )
      aux = aux->suc;
   EleDuplo *ultimo = aux->suc;
   memcpy( info, ultimo->info, p->tamInfo );
   free( ultimo->info );
   free( ultimo );
   aux->suc = NULL;
   p->qtd--;
   return 1; // Sucesso!
}

int insere_pos( Lista *p, void *info , int pos ){
	if( pos < 0 || pos > p->qtd )
		return ERRO_POS_INVALIDA;

	if( pos == 0 )
		return insere_inicio( p, info );

	EleDuplo *aux = p->cabeca;
	int cont;
	for( cont = 0 ; cont < pos-1 ; cont++ )
		aux = aux->suc; // Vai até EleDuplo em pos-1

	EleDuplo *novo = aloca_EleDuplo( info, p->tamInfo );
	if( novo == NULL )
		return 0; // Erro, falta de memória!

	novo->suc = aux->suc;
	aux->suc = novo;
	if(novo->suc != NULL) {
        novo->suc->ant = novo; //ou = p->cabeca
	}
	novo->ant = aux;
	p->qtd++;
	return 1; // Sucesso!
}

int remove_pos( Lista *p, void *info , int pos ){
	if( lista_vazia( *p ) )
		return ERRO_LISTA_VAZIA;

	if( pos < 0 || pos >= p->qtd )
		return ERRO_POS_INVALIDA;

	if( pos == 0 )
		return remove_inicio( p, info );

	EleDuplo *aux = p->cabeca;
	int cont;
	for( cont = 0 ; cont < pos-1 ; cont++ )
		aux = aux->suc; // Vai até pos-1

	EleDuplo *x = aux->suc;
	aux->suc = x->suc;
	if( aux->suc != NULL)
        aux->suc->ant = aux;
	memcpy( info, x->info, p->tamInfo );
	free( x->info );
	free( x );
	p->qtd--;
	return 1; // Sucesso!
}

int le_valor( Lista l, void *info , int pos ){
	if( lista_vazia( l ) )
		return ERRO_LISTA_VAZIA;

	if( pos < 0 || pos >= l.qtd )
		return ERRO_POS_INVALIDA;

	EleDuplo *aux = l.cabeca;
	int cont;
	for( cont = 0 ; cont < pos ; cont++ )
		aux = aux->suc; // Vai até EleDuplo em pos

	memcpy( info, aux->info, l.tamInfo );
	return 1; // Sucesso!
}

int modifica_valor( Lista l, void *info , int pos ){
	if( lista_vazia( l ) )
		return ERRO_LISTA_VAZIA;

	if( pos < 0 || pos >= l.qtd )
		return ERRO_POS_INVALIDA;

	EleDuplo *aux = l.cabeca;
	int cont;
	for( cont = 0 ; cont < pos ; cont++ )
		aux = aux->suc; // Vai até EleDuplo em pos

	memcpy( aux->info, info, l.tamInfo );
	return 1; // Sucesso!
}

void mostra_lista( Lista l, void (*mostra)(void *) ){
	if( lista_vazia( l ) )
		printf("Lista vazia!\n");
	else{
		printf("Dados da lista (%d EleDuplos):\n", l.qtd );
		EleDuplo *p = l.cabeca;
		int cont = 0; // cont é o índice do EleDuplo dentro da lista.
		while( p != NULL ){
			printf("[%d] ", cont);
			mostra( p->info ); // Invocação por callback
			p = p->suc;
			cont++;
		}
	}
	printf("--------------------------------\n");
}

int conta_EleDuplos( Lista l ){
	int cont = 0;
	EleDuplo *p = l.cabeca;
	while( p != NULL ){
		cont++;
		p = p->suc;
	}
	return cont;
}

void limpa_lista( Lista *l ){
	EleDuplo *p = l->cabeca;
	while( p != NULL ){
		EleDuplo *prox = p->suc;
		free( p->info );
		free( p );
		p = prox;
	}
	l->cabeca = NULL;
	l->qtd = 0;
}

int insere_ordem( Lista *p, void *info, int (*compara)(void*, void*) ){
	EleDuplo *aux = p->cabeca;
	int cont = 0;
	while( aux != NULL && compara( info, aux->info ) > 0 ){
		aux = aux->suc;
		cont++;
	}
	return insere_pos( p, info, cont );
}
