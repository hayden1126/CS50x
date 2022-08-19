#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

const int BLOCK_SIZE = 512;

bool is_jpeg(uint8_t file[BLOCK_SIZE], int i);

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

    int next_jpeg;
    uint8_t card[BLOCK_SIZE];
    while (fread(card, sizeof(uint8_t), BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // For each byte
        for (int i = 0; i < BLOCK_SIZE - 4; i++)
        {
            // If this byte is the start of a JPEG
            if (!is_jpeg(card, i))
            {
                continue;
            }
            // Check location of the next JPEG
            for (int j = i + 4; j < BLOCK_SIZE - 4; j++)
            {
                if (is_jpeg(card, j))
                {
                    next_jpeg = j;
                    break;
                }
            }

        }

    }
    fclose(file);
}

bool is_jpeg(uint8_t file[BLOCK_SIZE], int i)
{
    if (file[i] != 0xff || file[i + 1] != 0xd8 || file[i + 2] != 0xff)
    {
        return false;
    }
    else if (file[i + 3] >= 0xe0 && file[i + 3] <= 0xef)
    {
        return true;
    }
    return false;
}