#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct evento_t { 
    double tempo;
    int alvo;
    int tipo;
    
}evento_t;


typedef struct lista_eventos_t { 
    struct evento_t *evento;
    struct lista_eventos_t * prox;
}lista_eventos_t;

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

int main(int argc, char *argv[]){

    FILE *f = fopen(argv[1], "r"); // "r" for read
    if (f==NULL) exit(1);
    int alvo, tipo;
    double tempo;

    lista_eventos_t **listInicio = (lista_eventos_t**)malloc(sizeof(lista_eventos_t**));
    *listInicio = NULL;
    lista_eventos_t **listFim = (lista_eventos_t**)malloc(sizeof(lista_eventos_t**));
    *listFim = NULL;
    lista_eventos_t **listOrdenada = (lista_eventos_t**)malloc(sizeof(lista_eventos_t**));
    *listOrdenada = NULL;

    evento_t * evento = (evento_t*)malloc(sizeof(evento_t));


    while(!feof(f)){
        evento_t * evento = (evento_t*)malloc(sizeof(evento_t));
 
        fscanf(f, "%lf\t%d\t%d", &tempo, &alvo, &tipo);
        evento->tempo = tempo;
        evento->alvo = alvo;
        evento->tipo = tipo;
        lista_eventos_adicionar_inicio(evento,listInicio);
        lista_eventos_adicionar_inicio(evento,listFim);
        lista_eventos_adicionar_inicio(evento,listOrdenada);
    }
    printf("================ Insercao no inicio ================\n");
    lista_eventos_listar(listInicio);

    
    printf("================ Insercao no fim ================\n");
    lista_eventos_listar(listFim);


    printf("================ Insercao ordenada ================\n");
    lista_eventos_listar(listOrdenada);
}