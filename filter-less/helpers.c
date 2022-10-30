#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For every row (height)
    for (int i = 0; i < height; i++)
    {
        // For every pixel in row (width)
        for (int j = 0; j < width; j++)
        {
            // Calculate average RGB value
            float avg_value = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            // Set each RGB to average value
            image[i][j].rgbtRed = round(avg_value);
            image[i][j].rgbtGreen = round(avg_value);
            image[i][j].rgbtBlue = round(avg_value);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // For every row (height)
    for (int i = 0; i < height; i++)
    {
        // For every pixel in row (width)
        for (int j = 0; j < width; j++)
        {
            int origRed = image[i][j].rgbtRed;
            int origGreen = image[i][j].rgbtGreen;
            int origBlue = image[i][j].rgbtBlue;
            // Calculate sepia value
            float sepiaRed = .393 * origRed + .769 * origGreen + .189 * origBlue;
            float sepiaGreen = .349 * origRed + .686 * origGreen + .168 * origBlue;
            float sepiaBlue = .272 * origRed + .534 * origGreen + .131 * origBlue;
            // If sepia value < 255, set to 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtBlue = round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // For every row (height)
    for (int i = 0; i < height; i++)
    {
        // For every pixel in row (width)
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy image
    RGBTRIPLE copy[height][width];
    // For every row (height)
    for (int i = 0; i < height; i++)
    {
        // For every pixel in row (width)
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Blur
    // For every row (height)
    for (int i = 0; i < height; i++)
    {
        // For every pixel in row (width)
        for (int j = 0; j < width; j++)
        {
            // Create repository for all colors
            int allRed = 0;
            int allGreen = 0;
            int allBlue = 0;
            int checkx;
            int checky;
            float pixelcount = 0.00; // This is float because we need accurate division later
            // Check surrounding pixels
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    checkx = i + x;
                    //printf("checkx = %i\n", checkx);
                    checky = j + y;
                    //printf("checky = %i\n", checky);
                // Validate pixel
                if (checkx < 0 || checkx > (height - 1) || checky < 0 || checky > (width - 1))
                {
                    continue;
                }
                // Get RGB values from copy
                allRed += copy[checkx][checky].rgbtRed;
                allGreen += copy[checkx][checky].rgbtGreen;
                allBlue += copy[checkx][checky].rgbtBlue;
                pixelcount++;
                }
            }
            //printf("Red = %i; Green = %i; Blue = %i; pixelcount = %f\n", allRed, allGreen, allBlue, pixelcount);
            // Calculate average pixel value and overwrite
            image[i][j].rgbtRed = round(allRed / pixelcount);
            image[i][j].rgbtGreen = round(allGreen / pixelcount);
            image[i][j].rgbtBlue = round(allBlue / pixelcount);
        }
    }
    return;
}
