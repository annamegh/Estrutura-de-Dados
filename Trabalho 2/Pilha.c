#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h" //TEM QUE INCLUIR A BIBLIOTECA CRIADA

void inicializa_pilha ( Pilha *p, int c){
    p->topo = -1;
    p->capacidade = c; //MUDA AQUI
    p->dados = malloc(sizeof (int) * c); //MUDA AQUI
} //atribui -1 ao topo

int pilha_vazia ( Pilha p ) {
    return p.topo == -1;
} //Se o topo vale -1, a pilha está vazia

int pilha_cheia ( Pilha p ) {
    return p.topo == p.capacidade; //MUDA AQUI
} //verifica se o íncide do topo é o máx de elementos

int empilha ( Pilha *p, int info ) {
    if( pilha_cheia ( *p ) )
        return ERRO_PILHA_CHEIA; //verifica se a pilha está cheia, se sim, retorna -2

    p->topo++; //incrementa o topo
    p->dados[p->topo] = info; //passa o valor informado para o novo topo
    return 1; // Sucesso
}

int desempilha ( Pilha *p, int *info ) {
    if ( pilha_vazia ( *p ) )
        return ERRO_PILHA_VAZIA; //Verifica se a pilha está vazia, se sim retorna -1

    *info = p->dados[p->topo]; //passa o valor do topo para a variável info
    p->topo--; //desencrementa o topo
    return 1; // Sucesso
}

int le_topo ( Pilha p, int *info ) {
    if ( pilha_vazia( p ) )
        return ERRO_PILHA_VAZIA; //Verifica se a pilha está vazia, se sim retorna -1

    *info = p.dados[p.topo]; //passa o valor do topo para info
    return 1; // Sucesso
}

void mostra_pilha ( Pilha p ) {
    if( pilha_vazia ( p ) )
        printf("Pilha vazia!\n"); //Verifica se a pilha está vazia

    else{
        printf("Dados da Pilha:\n");
        int i;
        for(i=0; i <= p.topo; i++)
            printf("%d\n", p.dados[i]); //printa os dados da pilha
    }
    printf("-------------\n");
}

void desaloca_pilha ( Pilha *p) {
    free( p->dados);
}

void concatena( Pilha *p1, Pilha *p2 ) {
    while( !pilha_vazia( *p1 ) ){
        int temp;
        desempilha( p2, &temp );
        empilha( p1, temp);

        if(pilha_cheia( *p1))
            break;
    }
}


