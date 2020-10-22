#include "linkedList.h"




int main(int argc, char *argv[]){
    FILE *f = fopen(argv[1], "r"); // "r" for read
    if (f==NULL) exit(1);
    int alvo, tipo;
    double tempo;

    lista_eventos_t **list = (lista_eventos_t**)malloc(sizeof(lista_eventos_t**));
    *list = NULL;

    evento_t * evento = (evento_t*)malloc(sizeof(evento_t));


    while(!feof(f)){
        evento_t * evento = (evento_t*)malloc(sizeof(evento_t));
 
        fscanf(f, "%lf\t%d\t%d", &tempo, &alvo, &tipo);
        evento->tempo = tempo;
        evento->alvo = alvo;
        evento->tipo = tipo;
        lista_eventos_adicionar_fim(evento,list);
    }

    printf("================ Insercao no fim ================\n");
    lista_eventos_listar(list);
}
