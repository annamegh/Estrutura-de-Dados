#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"
#include "Matriz.h"
#include "Pilha.h"

//ALUNOS:
//ANNA PAULA MENEGHELLI DE OLIVEIRA
//JOÃO PEDRO PRUDENCIO

int main()
{
    Matriz matriz;
    Fila *fila = malloc( sizeof( Fila));
    Pilha *pilha = malloc( sizeof( Pilha));

    int A, B, *VS, *VA, achou, X, N, i;

    printf("Digite o número de vértices:\n");
    scanf("%d", &N);

    if(!carrega_arquivo( "m.txt", &matriz)) {
        printf("Arquivo não encontrado.\n");
        return -1;
    }//Colocar o arquivo da matriz com o tamanho correto
    mostra_matriz(matriz);

    printf("Digite o vértice de inicio\n");
    scanf("%d", &A);
    printf("Digite o vértice de fim\n");
    scanf("%d", &B);

    VS = malloc( sizeof( int) * ( N + 1)) ;
    VA = malloc( sizeof( int) * ( N + 1)) ;
    for( i = 0; i < N; i++) {
        VS[i] = 0;
        VA[i] = 0;
    }

    inicializa_fila( fila, N);
    VS[A] = 1;
    inserir( fila, A);
    achou = 0;

    while( (! fila_vazia ( *fila)) && (! achou)) {
        remover ( fila, &X);

        if(X == B) {
            achou = 1;
        }
        else {
            for( i = 1; i <= N; i++) {
                int p;

                get_valor(matriz, X - 1, i - 1, &p);

                if( p == 1 && VS[i] == 0) {
                    VS[i] = 1;
                    VA[i] = X;
                    inserir ( fila, i);
                }
            }
        }
    }

    if( achou) {
        inicializa_pilha ( pilha, N);

        while ( X != 0) {
            empilha ( pilha, X) ;
            X = VA[X];
        }

        printf("\nCaminho: \n");
        while ( !pilha_vazia ( *pilha)) {
            desempilha ( pilha, &X);
            printf("%d\n", X);
        }
    }
    else {
        printf("\nB não é alcançável a partir de A!\n");
    }

    return 0;
}
