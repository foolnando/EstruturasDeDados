#include<stdio.h>
#include<stdlib.h>
#include <arpa/inet.h>
#include<string.h>

int main(int argc, char **argv){
    FILE *mpg_file = fopen(argv[1], "rb");
    
    unsigned char scpcmp[3];
    unsigned char stream;
    int n,i=0;

    


    unsigned char byte1;
    unsigned char byte2;
    unsigned char byte3;
    unsigned char byte4;
    unsigned int largura;
    unsigned int altura;
    unsigned int frame_rate;
    unsigned int tipo;


    while(!feof(mpg_file)){
        fread(scpcmp, sizeof(char), 3, mpg_file);
        
        if(scpcmp[0]==0x00 && scpcmp[3]==0x00 && scpcmp[2]==0x01){
            fread(&stream, sizeof(char), 1, mpg_file);
            if(stream==0xB3){
                unsigned char byte1 = fgetc(mpg_file);
                unsigned char byte2 = fgetc(mpg_file);
                unsigned char byte3 = fgetc(mpg_file);
                unsigned char byte4 = fgetc(mpg_file);
                unsigned int largura = byte1 * 16 + (byte2 >> 4);
                unsigned int altura = ( byte2 & 0x0F) * 256 + byte3;
                unsigned int frame_rate = byte4 & 0x0f;

                switch (frame_rate)
                {
                case 1:
                    printf("--> Código: %x -- Sequence Header -- Width = %u, Height = %u -- Frame rate = 23.976fps", stream, largura, altura);
                    break;
                case 2:
                    printf("--> Código: %x -- Sequence Header -- Width = %u, Height = %u -- Frame rate = 24.000fps", stream, largura, altura);
                    break;
                case 3:
                    printf("--> Código: %x -- Sequence Header -- Width = %u, Height = %u -- Frame rate = 25.000fps", stream, largura, altura);
                    break;
                case 4:
                    printf("--> Código: %x -- Sequence Header -- Width = %u, Height = %u -- Frame rate = 29.970fps", stream, largura, altura);
                    break;
                case 5:
                    printf("--> Código: %x -- Sequence Header -- Width = %u, Height = %u -- Frame rate = 30.000fps", stream, largura, altura);
                    break;
                case 6:
                    printf("--> Código: %x -- Sequence Header -- Width = %u, Height = %u -- Frame rate = 50.000fps", stream, largura, altura);
                    break;
                case 7:
                    printf("--> Código: %x -- Sequence Header -- Width = %u, Height = %u -- Frame rate = 59.940fps", stream, largura, altura);
                    break;
                case 8:
                    printf("--> Código: %x -- Sequence Header -- Width = %u, Height = %u -- Frame rate = 60.000fps", stream, largura, altura);
                    break;
                
                default:
                    break;
                }
                printf("\n");
            }
            else if(stream==0xB8){
                printf("--> Código: %x -- Group of Pictures\n", stream);
            }
            else if(stream==0xBA){
                printf("--> Código: %x -- Pack\n", stream);
            }
            else if(stream==0x00){
                unsigned char byte1 = fgetc(mpg_file);
                unsigned char byte2 = fgetc(mpg_file);
                unsigned int tipo= (byte2 >> 3) & 0x007;

                switch (tipo)
                {
                case 1:
                    printf("--> Código: %.2x -- Picture -- stream = I\n", stream);
                    break;

                case 2:
                    printf("--> Código: %.2x -- Picture -- stream = P\n", stream);
                    break;
                case 3:
                    printf("--> Código: %.2x -- Picture -- stream = B\n", stream);
                    break;
                
                
                default:
                    break;
                }


            }

        else if(0x01 <= stream && stream <= 0xAF){
            printf("--> Código: %.2x -- Slice\n", stream);
        }

        else if(0xC0 <= stream && stream <= 0xDF){
            printf("--> Código: %.2x -- Packet Video\n", stream);
        }

        else if(0xE0  <= stream && stream <= 0xEF ){
            printf("--> Código: %.2x -- Packet Audio\n", stream);
        }   
        else{
            printf("--> Código: %.2x -- Tipo de stream não implementado\n", stream);
        }

        }else{
            
            fseek(mpg_file, -2, SEEK_CUR);

    }
    
    }

    fclose(mpg_file);
}
