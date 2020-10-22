#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(int argc, char *argv[]){
    FILE *f = fopen(argv[1], "r"); // "r" for read
    if (f==NULL) exit(1);
    long long int cpf;
    int idade;
    int id =0;
    char nome[51];

    while(!feof(f)){

 
        fscanf(f, " %50[^\t]\t%lld\t%d\n", nome, &cpf, &idade);
        printf("- %s\t%lld\t%d\n", nome,cpf, idade);

       
    }

}