#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct pessoa_t { 
    char nome[51];
    long long int cpf;
    int idade;
}pessoa_t;

typedef struct lista_pessoas_t { 
    struct pessoa_t *pessoa;
    struct lista_pessoas_t * prox;
}lista_pessoas_t;

typedef lista_pessoas_t** tabela_hash_t;
int tabela_hash_tam=0;
int id_hash=0;

// adiciona pessoas na lista encadadeada
bool lista_pessoas_adicionar(pessoa_t *pessoa, lista_pessoas_t **lista){
    lista_pessoas_t *new_person = (lista_pessoas_t*)malloc(sizeof(lista_pessoas_t));
    if(new_person==NULL) return false;
    else{
        new_person->pessoa = pessoa;
        new_person->prox = *lista;
        *lista = new_person;
        return true;
    }
}

//Imprime as pessoas em uma lista encadeada
void lista_pessoas_listar(lista_pessoas_t **lista){
    // int i = 0;
    lista_pessoas_t *aux = (lista_pessoas_t*)malloc(sizeof(lista_pessoas_t));
    for (aux = *lista; aux != NULL; aux = aux->prox){
        printf("- %s\t%lld\t%d\n", aux->pessoa->nome, aux->pessoa->cpf, aux->pessoa->idade);
        // i++;
        }
    // printf("A lista tem %d pessoas\n", i);
}

// Aloca memória para um vetor de ponteiros para listas encadeadas e faz cada ponteiro de lista
// (elemento do vetor) apontar para nulo.
tabela_hash_t tabela_hash_pessoas_criar(){
    lista_pessoas_t **lista = (lista_pessoas_t**)malloc(sizeof(lista_pessoas_t**));
    *lista = NULL;
    return lista;
}

// Calcula a Função Hash de uma pessoa (pessoa->cpf % tabela_hash_tam).
int tabela_hash_pessoas_funcao(pessoa_t *pessoa){
    int key = (pessoa->cpf % tabela_hash_tam);
    return key;
}

//Adiciona a pessoa na lista encadeada localizada na posição do vetor especificado pela função acima
bool tabela_hash_pessoas_adicionar(pessoa_t *pessoa, tabela_hash_t tabela_hash){
    lista_pessoas_adicionar(pessoa, tabela_hash);
    return true;
}

//Para cada posição do vetor, executa a função lista_pessoas_listar.
void tabela_hash_pessoas_listar(tabela_hash_t tabela_hash[]){
    for(int i = 0;i<tabela_hash_tam;i++){
    printf("POSIÇÃO %d DA TABELA HASH: \n", i);
    lista_pessoas_listar(tabela_hash[i]);}
    }

void inicializar(tabela_hash_t hash[], int tam){
    int i;
    for(i=0;i<tam;i++){
        hash[i] = tabela_hash_pessoas_criar();
    }
}

int main(int argc, char *argv[]){
    if(argv[1]==NULL) exit(1);
    sscanf(argv[1], "%d",  &tabela_hash_tam);
    tabela_hash_t hash[tabela_hash_tam];
    inicializar(hash,tabela_hash_tam);

    FILE *f = fopen(argv[2], "r"); // "r" for read
    if (f==NULL) exit(1);
    long long int cpf;
    int idade;
    int id =0;
    char nome[51];

    while(!feof(f)){
        pessoa_t * pessoa = (pessoa_t*)malloc(sizeof(pessoa_t));
 
        fscanf(f, " %50[^\t]\t%lld\t%d\n", nome, &cpf, &idade);
        // printf("- %s\t%lld\t%d\n", nome,cpf, idade);

        strcpy(pessoa->nome, nome);
        pessoa->cpf = cpf;
        pessoa->idade = idade;
        id = tabela_hash_pessoas_funcao(pessoa);
        tabela_hash_pessoas_adicionar(pessoa, hash[id]);
    }

    tabela_hash_pessoas_listar(hash);

    // lista_pessoas_t **lista = (lista_pessoas_t**)malloc(sizeof(lista_pessoas_t**));
    // *lista = NULL;
    // pessoa_t *pessoa = (pessoa_t*)malloc(sizeof(pessoa_t));

    // char c[] = "abcd";
    // strcpy(pessoa->nome, c);
    // pessoa->cpf = 99071002268;
    // pessoa->idade = 20;

    // lista_pessoas_adicionar(pessoa, lista);
    // lista_pessoas_listar(lista);
    //printf("-%s\t%lli\t%d", (*lista)->pessoa->nome, (*lista)->pessoa->cpf, (*lista)->pessoa->idade);
    
}