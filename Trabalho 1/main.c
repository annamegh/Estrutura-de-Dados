#include <stdio.h>
#include <stdlib.h>
#include "../Ex matriz/Matriz.h"
#include "../Pilha - Alocação/Pilha.h"


//TRABALHO 1 EDA (PILHAS)
//ALUNOS: ANNA PAULA MENEGHELLI DE OLIVEIRA
        //JOÃO PEDRO PRUDENCIO
int main()
{
    int N, INI, *VS, X, i;
    Matriz matriz;
    Pilha P;

    printf("Digite o número de vértices do grafo:\n");
    scanf("%d", &N);

    if(!carrega_arquivo("m.txt", &matriz, N, N)) {
        printf("Arquivo não encontrado.\n");
        return -1;
    }//Colocar o arquivo da matriz com o tamanho correto

    VS = malloc(sizeof(int) * (N + 1)) ;
    for( i = 0; i < N; i++) {
        VS[i] = 0;
    }
    mostra_matriz(matriz);

    printf("Digite o vértice de início:\n");
    scanf("%d", &INI);

    inicializa_pilha( &P, N);
    if(empilha( &P, INI - 1) == ERRO_PILHA_CHEIA )
        printf("Pilha cheia.\n");

    while(! pilha_vazia(P)) {
        desempilha(&P, &X);

        if( VS[X] == 0) {
            printf("%d\n", X + 1);
            VS[X] = 1;
        }

        for( i = 0; i < N; i++) {
            int p;
            get_valor(matriz, X, i, &p);

            if( p == 1 && VS[i] == 0){
               empilha( &P, i);
            }
        }
    }

    libera_matriz( &matriz);
    desaloca_pilha ( &P);

    return 0;
}
