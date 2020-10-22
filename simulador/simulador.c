#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct lista_vizinhos_t { 
    int vizinho;
    struct lista_vizinhos_t * prox;
}lista_vizinhos_t;

typedef struct no_t { 
   int id;
   double x,y;
   bool pac;
   lista_vizinhos_t** lista_vizinhos;
   
}no_t;

typedef struct evento_t { 
    double tempo;
    int alvo;
    int tipo;
    
}evento_t;

typedef struct lista_eventos_t { 
    struct evento_t *evento;
    struct lista_eventos_t * prox;
}lista_eventos_t;

typedef no_t* grafo_t;


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


bool lista_vizinhos_adicionar(int vizinho, lista_vizinhos_t **lista){
    
    lista_vizinhos_t *new_vizinho = (lista_vizinhos_t*)malloc(sizeof(lista_vizinhos_t));
    if(new_vizinho==NULL) return false;
    else{
        new_vizinho->vizinho = vizinho;
        new_vizinho->prox = *lista;
        *lista = new_vizinho;
        return true;
    }
}


grafo_t grafo_criar(int tam) {
    grafo_t grafo = (grafo_t) malloc(tam*sizeof(no_t));
    for (int i=0; i<tam; i++) {
        grafo[i].lista_vizinhos = (lista_vizinhos_t**) malloc(sizeof(lista_vizinhos_t**));
        *(grafo[i].lista_vizinhos) = NULL;
    }
    return grafo;
}


void grafo_atualizar_vizinhos(int tam, double raio_comunicacao, grafo_t grafo){
    double disc;
    for (int i = 0;i<tam;i++){
        for (int j = 0;j<tam;j++){
            disc = sqrt(pow(grafo[i].x - grafo[j].x, 2) + pow(grafo[i].y - grafo[j].y, 2));
            // printf("%lf\n", disc);
            if(i!=j && disc <= raio_comunicacao){

                lista_vizinhos_adicionar(grafo[j].id,grafo[i].lista_vizinhos);
            }
        }
    }
}
void lista_vizinhos_imprimir(lista_vizinhos_t *lista){
    
    // int i = 0;
    lista_vizinhos_t *aux;
    for (aux = lista; aux != NULL; aux = aux->prox){
        printf("%d ",  aux->vizinho);
        // i++;
        }
    // printf("A lista tem %d pessoas\n", i);
}

void simulacao_iniciar(lista_eventos_t **lista, grafo_t grafo){
    int gi = 0;
    lista_eventos_t *aux = (lista_eventos_t*)malloc(sizeof(lista_eventos_t));
    aux = *lista;
    while(aux){
        gi = aux->evento->alvo;
        
        printf("[%3.6f] Nó %d recebeu pacote.\n", aux->evento->tempo, gi);
        lista_vizinhos_t *vi;
        for (vi = *grafo[gi].lista_vizinhos; vi != NULL; vi = vi->prox){
            if(!grafo[gi].pac){
                printf("\t -->  Repassando pacote para o nó %d  ...\n",  vi->vizinho);

                evento_t * evento = (evento_t*)malloc(sizeof(evento_t));

                evento->tempo = aux->evento->tempo+(0.1 + (vi->vizinho * 0.01));
                evento->alvo = vi->vizinho;
                evento->tipo = 1;
                lista_eventos_adicionar_ordenado(evento,&aux);}


        // i++;
        }

        grafo[gi].pac =true;
        aux = aux->prox;
    }
}

int main(int argc, char **argv){
    FILE *f = fopen(argv[1], "r");

    int tam = 0;
    double raio = 0;
    int id, i=0; 
    double x, y;

    if(!feof(f)) fscanf(f, " %d\t%lf\n", &tam, &raio);

    grafo_t grafo;
    grafo = grafo_criar(tam);

    // printf("%lf", raio);
    while(!feof(f)){
        
 
        fscanf(f, " %d\t%lf\t%lf\n", &id,&x,&y);
        // printf("- %s\t%lld\t%d\n", nome,cpf, idade);

        grafo[i].id = id;
        grafo[i].x = x;
        grafo[i].y = y;
        grafo[i].pac = false;
        
        
        i++;
    }

    grafo_atualizar_vizinhos(tam, raio, grafo);

    lista_eventos_t **list = (lista_eventos_t**)malloc(sizeof(lista_eventos_t**));
    *list = NULL;

    evento_t * evento = (evento_t*)malloc(sizeof(evento_t));


    evento->tempo = 1.0;
    evento->alvo = 0;
    evento->tipo = 1;
    lista_eventos_adicionar_ordenado(evento,list);
    simulacao_iniciar(list, grafo);


    printf("\nharo");
    
}