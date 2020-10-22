#include "linkedList.h"


bool lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista){
    lista_eventos_t *new_event = (lista_eventos_t*)malloc(sizeof(lista_eventos_t));
    if(new_event==NULL) return false;
    else{
        new_event->evento = evento;
        new_event->prox = *lista;
        *lista = new_event;
        return true;
    }
}

bool lista_eventos_adicionar_fim(evento_t *evento, lista_eventos_t **lista){
    lista_eventos_t *new_event = (lista_eventos_t*)malloc(sizeof(lista_eventos_t));
    lista_eventos_t *aux = (lista_eventos_t*)malloc(sizeof(lista_eventos_t));
    if(new_event==NULL) return false;
    else{
        new_event->evento = evento;
        new_event->prox = NULL;
        if(*lista==NULL){
            *lista = new_event;
            
        } else{
            aux = *lista;
            while(aux->prox!=NULL){
                aux = aux->prox;
            }
            aux->prox = new_event;
        }
        return true;
    }
}

bool lista_eventos_adicionar_ordenado(evento_t *evento, lista_eventos_t **lista){
    lista_eventos_t *new_event = (lista_eventos_t*)malloc(sizeof(lista_eventos_t));
    lista_eventos_t *aux = (lista_eventos_t*)malloc(sizeof(lista_eventos_t));
    if(new_event==NULL) return false;
    else{
        new_event->evento = evento;
        
        if(*lista==NULL){
            new_event->prox = NULL;
            *lista = new_event;
            
            
        } else{
            if((*lista)->evento->tempo > evento->tempo){
                new_event->prox = (*lista)->prox;
                *lista = new_event;
            }else{
            aux = *lista;
            while (aux->prox != NULL && aux->prox->evento->tempo < evento->tempo)
            {
                aux = aux->prox;
            }
            new_event->prox = aux->prox;
            aux->prox = new_event;
        }}
        return true;
    }
}

void lista_eventos_listar(lista_eventos_t **lista){
    // int i = 0;
    lista_eventos_t *aux = (lista_eventos_t*)malloc(sizeof(lista_eventos_t));
    for (aux = *lista; aux != NULL; aux = aux->prox){
        printf("tempo = %3.6f\n", aux->evento->tempo);
        printf("alvo = %d\n", aux->evento->alvo);
        printf("tipo = %d\n", aux->evento->tipo);
        // i++;
        printf("\n");}
    // printf("A lista tem %d eventos\n", i);
}
