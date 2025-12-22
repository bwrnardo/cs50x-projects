#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average =
                (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;

            image[i][j].rgbtRed = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtBlue = round(average);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            int temp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = temp;

            temp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = temp;

            temp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            float red = 0.0;
            float green = 0.0;
            float blue = 0.0;
            int count = 0;

            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    if (i + row >= 0 && i + row < height)
                    {
                        if (j + col >= 0 && j + col < width)
                        {
                            red += copy[i + row][j + col].rgbtRed;
                            blue += copy[i + row][j + col].rgbtBlue;
                            green += copy[i + row][j + col].rgbtGreen;
                            count++;
                        }
                    }
                }
            }
            int avg_red = round(red / count);
            int avg_blue = round(blue / count);
            int avg_green = round(green / count);

            image[i][j].rgbtRed = avg_red;
            image[i][j].rgbtBlue = avg_blue;
            image[i][j].rgbtGreen = avg_green;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gxRed = 0, gxGreen = 0, gxBlue = 0;
            float gyRed = 0, gyGreen = 0, gyBlue = 0;
            float weightX = 0, weightY = 0;
            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    if (i + row >= 0 && i + row < height)
                    {
                        if (j + col >= 0 && j + col < width)
                        {
                            weightX = Gx[row + 1][col + 1];
                            weightY = Gy[row + 1][col + 1];

                            gxRed += copy[i + row][j + col].rgbtRed * weightX;
                            gyRed += copy[i + row][j + col].rgbtRed * weightY;

                            gxGreen += copy[i + row][j + col].rgbtGreen * weightX;
                            gyGreen += copy[i + row][j + col].rgbtGreen * weightY;

                            gxBlue += copy[i + row][j + col].rgbtBlue * weightX;
                            gyBlue += copy[i + row][j + col].rgbtBlue * weightY;
                        }
                    }
                }
            }
            float valueRed = sqrt(pow(gxRed, 2) + pow(gyRed, 2));
            float valueGreen = sqrt(pow(gxGreen, 2) + pow(gyGreen, 2));
            float valueBlue = sqrt(pow(gxBlue, 2) + pow(gyBlue, 2));

            if (valueRed > 255)
            {
                valueRed = 255;
            }
            if (valueGreen > 255)
            {
                valueGreen = 255;
            }
            if (valueBlue > 255)
            {
                valueBlue = 255;
            }

            image[i][j].rgbtRed = round(valueRed);
            image[i][j].rgbtGreen = round(valueGreen);
            image[i][j].rgbtBlue = round(valueBlue);
        }
    }
    return;
}
