#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int tabela_hash_tam;

typedef struct pessoa_t{
    char nome[51];
    long long int cpf;
    int idade;
}pessoa_t;

typedef struct lista_pessoas_t{
    pessoa_t* pessoa;
    struct lista_pessoas_t* proximo; 
}lista_pessoas_t;

 typedef lista_pessoas_t** tabela_hash_t;

bool lista_pessoas_adicionar(pessoa_t *pessoa, lista_pessoas_t **lista){
    lista_pessoas_t* item_novo = (lista_pessoas_t*) malloc(sizeof(lista_pessoas_t));
    if(item_novo == NULL) return false;

    item_novo->pessoa = pessoa;
    item_novo->proximo = *lista;
    *lista = item_novo;
    return true;
}

void lista_pessoas_listar(lista_pessoas_t *lista){
    do{
        pessoa_t pessoa = *(lista->pessoa);
        printf("- %s\t%lld\t%d\n",pessoa.nome,pessoa.cpf,pessoa.idade);
        lista = lista->proximo;
    }while(lista != NULL);
}

tabela_hash_t tabela_hash_pessoas_criar(){
   
    tabela_hash_t tabela_hash = (tabela_hash_t) malloc(sizeof(lista_pessoas_t)*tabela_hash_tam);
    for(int i=0;i<tabela_hash_tam;i++) tabela_hash[i] = NULL;

    return tabela_hash;
}

int tabela_hash_pessoas_funcao(pessoa_t *pessoa){
    return pessoa->cpf % tabela_hash_tam;
}

bool tabela_hash_pessoas_adicionar(pessoa_t *pessoa, tabela_hash_t tabela_hash){

    int posicao = tabela_hash_pessoas_funcao(pessoa);
    
    bool verif = lista_pessoas_adicionar(pessoa, &tabela_hash[posicao]);    
    if(!verif) return false;

    return true;
}

void tabela_hash_pessoas_listar(tabela_hash_t tabela_hash){
    for(int i=0;i<tabela_hash_tam;i++){
        printf("POSIÇÃO %d DA TABELA HASH:\n",i);
        lista_pessoas_listar(tabela_hash[i]);
    }
}


int main(int argc, char* argv[]){
    FILE *f = fopen(argv[2],"r");

    if(f == NULL){
        printf("Triste, não deu pra abrir o arquivo\n");
		return 0;
    }

    sscanf(argv[1],"%d",&tabela_hash_tam);
    tabela_hash_t tabela_hash = tabela_hash_pessoas_criar();

    pessoa_t pessoa; 
    while(fscanf(f," %50[^\t]\t%lld\t%d\n", pessoa.nome,&pessoa.cpf,&pessoa.idade) != -1){
        
        pessoa_t* nova_pessoa = (pessoa_t*) malloc(sizeof(pessoa_t));
        *nova_pessoa = pessoa;
        
        bool resp = tabela_hash_pessoas_adicionar(nova_pessoa, tabela_hash);
        if(!resp){
            printf("Erro ao adicionar pessoa na Tabela Hash");
            return 0;
        }
    }    

    tabela_hash_pessoas_listar(tabela_hash);

}