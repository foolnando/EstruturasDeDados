#include<stdio.h>
#include<stdlib.h>
#include <arpa/inet.h>
#include<string.h>


struct png_chunk_hdr {
int width;
int height;
char bitDepth;
char colourType;
char compressionMeth;
char filterMethod;
char interfaceMethod;
} __attribute__ ((packed));


struct chunk{
int length;
char tipo[4];
} __attribute__ ((packed));



int main(int argc, char **argv){
    FILE *png_file = fopen(argv[1], "rb");
    struct png_chunk_hdr *png_hdr = (struct png_chunk_hdr*)malloc(sizeof(struct png_chunk_hdr));
    struct chunk *png_chunk = (struct chunk*)malloc(sizeof(struct chunk));
    fseek(png_file, 8, SEEK_CUR);
    
    int numFile = 1;

    while(!feof(png_file)){
        printf("Lendo chunk %d:\n", numFile);
        
        fread(png_chunk, sizeof(struct chunk), 1, png_file);
        printf("\t--> Tamanho: %d\n", ntohl(png_chunk->length));
        printf("\t--> Tipo: %.4s\n", png_chunk->tipo);
        

        if(strcmp(png_chunk->tipo,"IHDR")==0){
            fread(png_hdr, sizeof(struct png_chunk_hdr), 1, png_file);
            printf("\t\t--> Largura: %d\n", ntohl(png_hdr->width));
            printf("\t\t--> Altura: %d\n", ntohl(png_hdr->height));
            fseek(png_file, 4, SEEK_CUR);

        } else if(strcmp(png_chunk->tipo,"IEND")==0){
            
            break;}
        else fseek(png_file, ntohl(png_chunk->length)+4, SEEK_CUR);
    numFile++;
    }

    free(png_hdr);
    free(png_chunk);

    fclose(png_file);
}

