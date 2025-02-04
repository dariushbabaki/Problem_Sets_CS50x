#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Check for correct command-line argument count
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card file
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE]; // Buffer to store 512-byte blocks
    FILE *img = NULL;           // File pointer for JPEGs
    char filename[8];           // Buffer for filename (###.jpg)
    int file_count = 0;         // Counter for JPEG files

    // Read through the memory card file block by block
    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // Check if the block contains the beginning of a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If a JPEG file is already open, close it
            if (img != NULL)
            {
                fclose(img);
            }

            // Create a new JPEG filename
            sprintf(filename, "%03d.jpg", file_count);
            file_count++;

            // Open a new JPEG file for writing
            img = fopen(filename, "w");
        }

        // If a JPEG file is open, write the current block into it
        if (img != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    // Close any remaining open files
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);

    return 0;
}
