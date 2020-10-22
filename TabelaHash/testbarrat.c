#include<stdio.h>
#include<stdlib.h>

int tam;
int main(int argc, char *argv[]){
    if(argv[1]==NULL) exit(1);
    sscanf( argv[1], "%d",  &tam);
    printf("oi\t");
    printf("tchau \t");
    printf("kelas %d\n", tam);
}