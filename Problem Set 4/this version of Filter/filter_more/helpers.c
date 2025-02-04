#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of RGB values
            int avg =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Assign the same grayscale value to all RGB components
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each row
    for (int i = 0; i < height; i++)
    {
        // Swap pixels from left to right
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary copy of the image to avoid modifying original values during calculations
    RGBTRIPLE temp[height][width];

    // Copy the original image to the temp array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Iterate over each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            int count = 0;

            // Iterate over the surrounding pixels (3x3 grid)
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Check if the neighboring pixel is within the image bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        totalRed += temp[ni][nj].rgbtRed;
                        totalGreen += temp[ni][nj].rgbtGreen;
                        totalBlue += temp[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Compute the average values
            image[i][j].rgbtRed = round(totalRed / (float) count);
            image[i][j].rgbtGreen = round(totalGreen / (float) count);
            image[i][j].rgbtBlue = round(totalBlue / (float) count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temporary copy of the image to avoid modifying original values during calculations
    RGBTRIPLE temp[height][width];

    // Copy the original image to the temp array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Sobel operator kernels for Gx and Gy
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Iterate over each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumRedX = 0, sumGreenX = 0, sumBlueX = 0;
            float sumRedY = 0, sumGreenY = 0, sumBlueY = 0;

            // Iterate over the surrounding pixels (3x3 grid)
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // If the neighboring pixel is outside the image, treat it as black (0, 0, 0)
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        int weightX = Gx[di + 1][dj + 1];
                        int weightY = Gy[di + 1][dj + 1];

                        sumRedX += temp[ni][nj].rgbtRed * weightX;
                        sumGreenX += temp[ni][nj].rgbtGreen * weightX;
                        sumBlueX += temp[ni][nj].rgbtBlue * weightX;

                        sumRedY += temp[ni][nj].rgbtRed * weightY;
                        sumGreenY += temp[ni][nj].rgbtGreen * weightY;
                        sumBlueY += temp[ni][nj].rgbtBlue * weightY;
                    }
                }
            }

            // Compute final edge intensity using Sobel formula: sqrt(Gx^2 + Gy^2)
            int finalRed = round(sqrt(sumRedX * sumRedX + sumRedY * sumRedY));
            int finalGreen = round(sqrt(sumGreenX * sumGreenX + sumGreenY * sumGreenY));
            int finalBlue = round(sqrt(sumBlueX * sumBlueX + sumBlueY * sumBlueY));

            // Ensure values are within the valid range [0, 255]
            image[i][j].rgbtRed = finalRed > 255 ? 255 : finalRed;
            image[i][j].rgbtGreen = finalGreen > 255 ? 255 : finalGreen;
            image[i][j].rgbtBlue = finalBlue > 255 ? 255 : finalBlue;
        }
    }
    return;
}
