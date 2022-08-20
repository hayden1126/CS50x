#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    // Open file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    // Declare/assign some variables
    int jpeg_count = 0;
    bool jpeg_started = false;
    FILE *img = NULL;
    char *filename = malloc(sizeof(char) * 8);
    uint8_t buffer[BLOCK_SIZE];
    // While not end of the file
    while (fread(buffer, sizeof(uint8_t), BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // If current 512 byte block is the start of a JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If previous JPEG has been created, close that file
            if (jpeg_started)
            {
                fclose(img);
            }
            jpeg_started = true;
            // Name the JPEG file with the jpeg_count then add one to jpeg_count
            sprintf(filename, "%03i.jpg", jpeg_count);
            jpeg_count++;
            // Create new JPEG and start writing to it
            img = fopen(filename, "w");
            fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, img);
        }
        // If current 512 byte block is NOT the start of a JPEG file
        else
        {
            // If haven't found first JPEG, then go to next block of 512 bytes
            if (!jpeg_started)
            {
                continue;
            }
            // If JPEG already started, then write the info to the previous JPEG
            fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, img);
        }
    }
    // Free memory stuff
    free(filename);
    fclose(img);
    fclose(file);
}