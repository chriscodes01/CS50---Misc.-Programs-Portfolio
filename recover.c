#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for invalid usage: Multiple command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    // Open memory card
    FILE *in_image = fopen(argv[1], "r");
    // Check for invalid usage: Unable to open image for reading
    if (in_image == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Declare variables
    int image_count = 0;
    FILE *out_image = NULL;
    char *file_name = malloc(8 * sizeof(BYTE));
    BYTE buffer[512];
    int BLOCK_SIZE = 512;

    // Repeat until end of card
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, in_image) == BLOCK_SIZE)
    {
        // If start of new JPEG...
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If not first JPEG, close file
            if (image_count != 0)
            {
                fclose(out_image);
            }
            // Open new file and write
            sprintf(file_name, "%03i.jpg", image_count);
            out_image = fopen(file_name, "w");
            image_count++;
        }
        // Else if already found JPEG
        if (out_image != NULL)
        {
            // Keep writing
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, out_image);
        }
    }
    // Free memory and close everything
    free(file_name);
    fclose(in_image);
    fclose(out_image);
}