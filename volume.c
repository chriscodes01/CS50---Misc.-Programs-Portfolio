// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    // Open input.wav and read.
    FILE *input = fopen(argv[1], "r");
    // Abort if NULL.
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    // Open output.wav and write.
    FILE *output = fopen(argv[2], "w");
    // Abort if NULL.
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    // Convert factor (currently a string) to a float.
    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // Should I?: Malloc space for header. Need to be in output!
    uint8_t header[HEADER_SIZE]; // Use this to store data from input.wav (i.e. your buffer)
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer; // Use this to store audio samples read from input.wav.
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        // Multiply buffer data by factor.
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
