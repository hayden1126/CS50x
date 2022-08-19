#include <math.h>
#include <stdlib.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For each pixel
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Find average of all RGB color values and set RGB values to their average
            int average = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    // For each pixel to half the width
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            // Swap left pixel with its counterpart on the right side of the image
            temp = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create identical copy of image
    RGBTRIPLE image_copy[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image_copy[h][w] = image[h][w];
        }
    }
    // rgbtcolor values used to calculate sum then average of each 3x3 pixels box
    float rgbtBlue;
    float rgbtGreen;
    float rgbtRed;
    // valid_pixels is the number of pixels that had their colors added the rgbtcolor values
    // Does not count any out-of-bounds pixels for all pixels on the edge of the image
    int valid_pixels;
    // For each target pixel
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Initialize values to 0
            rgbtBlue = 0.0;
            rgbtGreen = 0.0;
            rgbtRed = 0.0;
            valid_pixels = 0;
            // For each pixel in a 3x3 box around the target pixel (including the target pixel)
            for (int i = h - 1; i <= h + 1; i++)
            {
                for (int j = w - 1; j <= w + 1; j++)
                {
                    // If the pixel is not out-of-bounds, add the rgb values to the sum of each rgbtcolor value
                    if (i < height && i >= 0 && j < width && j >= 0)
                    {
                        valid_pixels++;
                        // image_copy is used here so that the original unchanged/unblurred rgb values would be used
                        rgbtBlue += image_copy[i][j].rgbtBlue;
                        rgbtGreen += image_copy[i][j].rgbtGreen;
                        rgbtRed += image_copy[i][j].rgbtRed;
                    }
                }
            }
            // Divide the rgbtcolor summed values by the number of pixels included and round it
            image[h][w].rgbtBlue = round(rgbtBlue / valid_pixels);
            image[h][w].rgbtGreen = round(rgbtGreen / valid_pixels);
            image[h][w].rgbtRed = round(rgbtRed / valid_pixels);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create arrays for Gx and Gy calculations of the Sobel Operator
    float gx_weight[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    float gy_weight[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    // Create copy of image
    RGBTRIPLE image_copy[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image_copy[h][w] = image[h][w];
        }
    }
    // Create sum structure
    typedef struct
    {
        float blue;
        float green;
        float red;
    }
    weightedSum;
    weightedSum sum[2];
    // For each target pixel
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Initialize values to 0
            int pixel_no = 0;
            sum[0].blue = 0;
            sum[0].green = 0;
            sum[0].red = 0;
            sum[1].blue = 0;
            sum[1].green = 0;
            sum[1].red = 0;
            // For each 3x3 pixel around target pixel (including target pixel)
            for (int i = h - 1; i <= h + 1; i++)
            {
                for (int j = w - 1; j <= w + 1; j++)
                {
                    // If pixel is not out-of-bounds
                    if (i < height && i >= 0 && j < width && j >= 0)
                    {
                        // Multiply rgb values of pixel to the Sobel operator weight and add to the sum
                        // image_copy is used here so that the original unchanged rgb values would be used
                        sum[0].blue += (image_copy[i][j].rgbtBlue * gx_weight[pixel_no]);
                        sum[0].green += (image_copy[i][j].rgbtGreen * gx_weight[pixel_no]);
                        sum[0].red += (image_copy[i][j].rgbtRed * gx_weight[pixel_no]);
                        sum[1].blue += (image_copy[i][j].rgbtBlue * gy_weight[pixel_no]);
                        sum[1].green += (image_copy[i][j].rgbtGreen * gy_weight[pixel_no]);
                        sum[1].red += (image_copy[i][j].rgbtRed * gy_weight[pixel_no]);
                    }
                    // pixel_no variable for counting the pixel for using which weight for the Sobel operator
                    pixel_no++;
                }
            }
            // calculate semifinal rgb values with square root (gx^2 + gy^2)
            int blue = round(sqrt(sum[0].blue * sum[0].blue + sum[1].blue * sum[1].blue));
            int green = round(sqrt(sum[0].green * sum[0].green + sum[1].green * sum[1].green));
            int red = round(sqrt(sum[0].red * sum[0].red + sum[1].red * sum[1].red));
            // Set rgb values to 255 if exceeds 255
            if (blue > 255)
            {
                blue = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (red > 255)
            {
                red = 255;
            }
            // Finally put the final rgb values into the image
            image[h][w].rgbtBlue = blue;
            image[h][w].rgbtGreen = green;
            image[h][w].rgbtRed = red;
        }
    }
    return;
}
