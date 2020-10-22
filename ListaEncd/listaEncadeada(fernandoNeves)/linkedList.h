#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct evento_t { 
    double tempo;
    int alvo;
    int tipo;
    
}evento_t;


typedef struct lista_eventos_t { 
    struct evento_t *evento;
    struct lista_eventos_t * prox;
}lista_eventos_t;

bool lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista);

bool lista_eventos_adicionar_fim(evento_t *evento, lista_eventos_t **lista);

bool lista_eventos_adicionar_ordenado(evento_t *evento, lista_eventos_t **lista);

void lista_eventos_listar(lista_eventos_t **lista);

#endif