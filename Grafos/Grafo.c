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
   lista_vizinhos_t** lista_vizinhos;
   
}no_t;

typedef no_t* grafo_t;

    // → Adiciona um inteiro (id de um vizinho) ao início de uma lista encadeada (similar ao TP1/TP2)
    // → lista_vizinhos_t será uma lista de inteiros, portanto não há necessidade de criar um tipo
    // “vizinho_t”.
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


    //→ Imprime os números (ids) da lista se vizinhos (similar ao TP1, mas no formato especificado)
void lista_vizinhos_imprimir(lista_vizinhos_t *lista){
    
    // int i = 0;
    lista_vizinhos_t *aux;
    for (aux = lista; aux != NULL; aux = aux->prox){
        printf("%d ",  aux->vizinho);
        // i++;
        }
    // printf("A lista tem %d pessoas\n", i);
}

    // → Aloca memória para um vetor de nós.
    // → grafo_t pode ser definido como: typedef no_t* grafo_t;
lista_vizinhos_t ** lista_vizinhos_criar(){
    lista_vizinhos_t **lista = (lista_vizinhos_t**)malloc(sizeof(lista_vizinhos_t**));
    *lista = NULL;
    return lista;
}

grafo_t grafo_criar(int tam) {
    grafo_t grafo = (grafo_t) malloc(tam*sizeof(no_t));
    for (int i=0; i<tam; i++) {
        grafo[i].lista_vizinhos = (lista_vizinhos_t**) malloc(sizeof(lista_vizinhos_t**));
        *(grafo[i].lista_vizinhos) = NULL;
    }
    return grafo;
}

void grafo_imprimir(int tam, grafo_t grafo){
    for(int i = 0;i<tam;i++){
    printf("NÓ %d: ", i);
    lista_vizinhos_imprimir(*(grafo[i].lista_vizinhos));
    printf("\n");}
    
    }
    

    // → Para cada nó (nó “i”) do vetor de nós do grafo, compará-lo com todos os outros nós da rede (nó “j”,
    //     sendo j != i) e, caso a distância entre i e j seja menor que o raio de comunicação, adicione i à
    //     lista de vizinhos de j.
    // → Cálculo de distâncias Euclidianas:
    //     sqrt(pow(grafo[i].x - grafo[j].x, 2) + pow(grafo[i].y - grafo[j].y, 2))
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
        
        
        i++;
    }

    grafo_atualizar_vizinhos(tam, raio, grafo);
    grafo_imprimir(tam, grafo);
    printf("haro");

}

