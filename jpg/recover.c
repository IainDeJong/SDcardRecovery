/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //must we?

typedef struct
{
    uint8_t BYTE0;
    uint8_t BYTE1;
    uint8_t BYTE2;
    uint8_t BYTE3;
    uint8_t rest[508];       
} __attribute__((__packed__))
MEMBLOCK;

int main(int argc, char* argv[])
{

    // ceck for no command line args
    if (argc != 1)
    {
        printf("error: too many arguments");
        exit(-1);
    }
    
    // open card.raw 
    FILE* file = fopen("card.raw", "r");
    
    // ceck for NULL
    if (file == NULL)
    {
        printf("error: could not open file");
        exit(-1); 
    }
    
    // declaring some stuff
    int jpgcount = 0;
    char title[8];
    MEMBLOCK buffer;
    
    // char* buffer = malloc(512 * sizeof(uint8_t));
    while (fread(&buffer, sizeof(MEMBLOCK), 1, file) == 1)
    {
        // char buffer[512][uint8_t];
        if (buffer.BYTE0 == 0xff && buffer.BYTE1 == 0xd8 && buffer.BYTE2 == 
        0xff && (buffer.BYTE3 == 0xe0 || buffer.BYTE3 == 0xe1))
        {
            sprintf(title,"%03d.jpg",jpgcount);
            jpgcount++;
            FILE* img = fopen(title, "a");
            fwrite(&buffer, sizeof(MEMBLOCK), 1, img);
            fclose(img);
            
        }
        
        else if (jpgcount != 0)
        {
            FILE* img = fopen(title, "a");
            fwrite(&buffer, sizeof(MEMBLOCK), 1, img);
            fclose(img);
        }
            
    }        
    
    return 0;
}


