#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
    //cheking input
    if (argc != 2)
    {
        printf("Usage: recover image\n");
        return 1;
    }

    //opening input file
    FILE *openedCard = fopen(argv[1], "r");

    //cheking if file is opening
    if (openedCard == NULL)
    {
        printf("File could not be opened.\n");
        return 2;
    }

    //declaring jpg counter
    int jpegNumber = 0;
    //declaring variable for storing info if first jpg has been found
    int firstJpegFound = 0;

    //declaring array for storing jpg name
    char filename[8];
    //declaring jpg pointer
    FILE *imgW;

    //declaring buffer array for storing 512-BYTE chunks
    typedef uint8_t BYTE;
    BYTE arr[512];

    //while fread can read 512-BYTE chunk
    while (fread(arr, 512, 1, openedCard))
    {
        //if 512-BYTE chunk starts jpg
        if (arr[0] == 0xff && arr[1] == 0xd8 && arr[2] == 0xff && (arr[3] & 0xf0) == 0xe0)
        {
            //if it is not the first jpg
            if (firstJpegFound > 0)
            {
                //closing pointer for writing to previous jpg
                fclose(imgW);
            }

            //print in to string with formating code using jpeg counter
            sprintf(filename, "%03i.jpg", jpegNumber);

            //creating jpeg with filename by creating pointer for writing
            imgW = fopen(filename, "w");

            //writing to jpeg current content of arr
            fwrite(arr, 512, 1, imgW);

            //updating firstJpegFound and jpg counter
            firstJpegFound = 1;
            jpegNumber++;
        }
        //if 512-BYTE chunk does not start jpg
        else
        {
            //if there was jpg found
            if (firstJpegFound > 0)
            {
                //writing to current jpg
                fwrite(arr, 512, 1, imgW);
            }
        }
    }
    //closing card for reading after looping through all 512-BYTE chunk
    fclose(openedCard);
}
