#include <stdio.h>
#include <stdlib.h>
#include "Matriz_lista.h"

void inicializa_matriz( Matriz *p, int l, int c) {
    inicializa_lista( &p->dados, sizeof( Lista ));
    int i, j;
    Lista sub;

    for(i = 0; i < l; i++) {
        inicializa_lista( &sub, sizeof(int));
        for( j = 0; j < c; j++) {
            int valor = 0;
            insere_fim( &sub, &valor);
        }
        insere_fim( &p->dados, &sub);
    }
}

void mostra_matriz( Matriz m) {
    int i, j, valor;
    Lista sub;

    for( i = 0; le_valor( m.dados, &sub, i ) != ERRO_POS_INVALIDA ; i++ ) { //condição de parada: até dar erro
        for( j = 0; le_valor( sub, &valor, j ) != ERRO_POS_INVALIDA; j++) {
            printf("%4d ", valor);
        }
        printf("\n");
    }
}

int set_valor( Matriz *p, int i, int j, int v ){
	Lista sub;
	if( le_valor( p->dados, &sub, i ) == ERRO_POS_INVALIDA )
		return ERRO_COORD_INVALIDA;

	if( modifica_valor( sub, &v, j ) == ERRO_POS_INVALIDA )
		return ERRO_COORD_INVALIDA;

	return 1; // Sucesso!
}

int get_valor( Matriz m, int i, int j, int *v) {
    Lista sub;

    if (le_valor( m.dados, &sub, i ) != ERRO_POS_INVALIDA )
        if( le_valor( sub, v, j ) != ERRO_POS_INVALIDA )
            return 1;

    return ERRO_COORD_INVALIDA;
}

int soma_matrizes( Matriz m1, Matriz m2, Matriz *p) {
    int i, j, aux1, aux2, valor, lin1 = 0, col1 = 0, lin2 = 0, col2 = 0;
    Lista sub;

    for( i = 0; le_valor( m1.dados, &sub, i ) != ERRO_POS_INVALIDA; i++ )
        lin1++;
    for( j = 0; le_valor( sub, &valor, j ) != ERRO_POS_INVALIDA; j++)
        col1++;
    for( i = 0; le_valor( m2.dados, &sub, i ) != ERRO_POS_INVALIDA; i++ )
        lin2++;
    for( j = 0; le_valor( sub, &valor, j ) != ERRO_POS_INVALIDA; j++)
        col2++;

    if(lin1 != lin2 || col1 != col2)
        return MATRIZES_INCOMPATIVEIS;

    inicializa_matriz( p, lin1, col1);
    for( i = 0; i < lin1; i++ ) {
        for( j = 0; j < col1; j++ ) {
            get_valor(m1, i, j, &aux1);
            get_valor(m2, i, j, &aux2);
            valor = aux1 + aux2;

            set_valor(p, i, j, valor);
        }
    }
    return 1;
}

int sao_iguais( Matriz m1, Matriz m2) {
    int i, j, valor1, valor2, lin1 = 0, col1 = 0, lin2 = 0, col2 = 0;
    Lista sub1, sub2;

    for( i = 0; le_valor( m1.dados, &sub1, i ) != ERRO_POS_INVALIDA; i++ )
        lin1++;
    for( j = 0; le_valor( sub1, &valor1, j ) != ERRO_POS_INVALIDA; j++)
        col1++;
    for( i = 0; le_valor( m2.dados, &sub2, i ) != ERRO_POS_INVALIDA; i++ )
        lin2++;
    for( j = 0; le_valor( sub2, &valor2, j ) != ERRO_POS_INVALIDA; j++)
        col2++;
    if(lin1 != lin2 || col1 != col2)
        return 0;

    for( i = 0; i < lin1 ; i++ ) { //condição de parada: até dar erro
        le_valor( m1.dados, &sub1, i );
        le_valor( m2.dados, &sub2, i );

        for( j = 0; j < col1; j++) {
            le_valor( sub1, &valor1, j );
            le_valor( sub2, &valor2, j );

            if(valor1 != valor2)
                return 0;
        }
    }

    return 1;
}

int carrega_arquivo( char *nome, Matriz *p) {
    int valor, l, c;
    FILE *f = fopen( nome, "rt");
    if( f == NULL)
        return 0;

    fscanf( f, "%d", &l);
    fscanf( f, "%d", &c);
    int i, j;
    inicializa_matriz(p, l, c);

    for(i = 0; i < l; i++) {
        for(j = 0; j < c; j++){
            fscanf( f, "%d", &valor);
            set_valor(p, i, j, valor);
        }
    }
    fclose(f);
    return 1;
}

int salva_arquivo( char *nome, Matriz m) {
    int lin = 0, col = 0, valor, i, j;
    Lista sub;
    FILE *f = fopen( nome, "wt");
    if( f == NULL)
        return 0;

    for( i = 0; le_valor( m.dados, &sub, i ) != ERRO_POS_INVALIDA; i++ )
        lin++;
    for( j = 0; le_valor( sub, &valor, j ) != ERRO_POS_INVALIDA; j++)
        col++;

    fprintf(f, "%d %d\n", lin, col);

    for (i = 0; i < lin; i++) {
        le_valor( m.dados, &sub, i );
        for(j = 0; j < col; j++){
            le_valor( sub, &valor, j );
            fprintf(f, "%d ", valor);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 1;
}
