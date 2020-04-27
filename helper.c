#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum = (image[i][j].rgbtBlue + (int)image[i][j].rgbtGreen + (int)image[i][j].rgbtRed);
            float avg = round((float)sum/3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int *temp = malloc(3 * sizeof(int));
            temp[0] = image[i][j].rgbtBlue;
            temp[1] = image[i][j].rgbtGreen;
            temp[2] = image[i][j].rgbtRed;

            int sepiaRed = round(.393 * temp[2] + .769 * temp[1] + .189 * temp[0]);
            int sepiaGreen = round(.349 * temp[2] + .686 * temp[1] + .168 * temp[0]);
            int sepiaBlue = round(.272 * temp[2] + .534 * temp[1] + .131 * temp[0]);

            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < round(width/2); j++)
        {
            //temporary storage
            int *temp = (int *)malloc(3 * sizeof(int));
            temp[0] = image[i][j].rgbtBlue;
            temp[1] = image[i][j].rgbtGreen;
            temp[2] = image[i][j].rgbtRed;
            if (width % 2 == 0)
            {
                image[i][j].rgbtBlue = image[i][width-(j+1)].rgbtBlue;
                image[i][j].rgbtGreen = image[i][width-(j+1)].rgbtGreen;
                image[i][j].rgbtRed = image[i][width-(j+1)].rgbtRed;

                image[i][width-(j+1)].rgbtBlue = temp[0];
                image[i][width-(j+1)].rgbtGreen = temp[1];
                image[i][width-(j+1)].rgbtRed = temp[2];

            }
            else
            {
                image[i][j].rgbtBlue = image[i][width-(j)].rgbtBlue;
                image[i][j].rgbtGreen = image[i][width-(j)].rgbtGreen;
                image[i][j].rgbtRed = image[i][width-(j)].rgbtRed;

                image[i][width-(j)].rgbtBlue = temp[0];
                image[i][width-(j)].rgbtGreen = temp[1];
                image[i][width-(j)].rgbtRed = temp[2];


            }
            free(temp);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int sumBlue, sumRed, sumGreen, counter;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            counter = 0;

            // sums values of the pixel and 8 neighboring ones, skips iteration if it goes outside the pic
            for (int k = -1; k < 2; k++)
            {
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }

                    sumBlue += image[j + k][i + h].rgbtBlue;
                    sumGreen += image[j + k][i + h].rgbtGreen;
                    sumRed += image[j + k][i + h].rgbtRed;
                    counter++;
                }
            }
            // averages the sum to make picture look blurrier
            temp[j][i].rgbtBlue = round(sumBlue / (float)counter);
            temp[j][i].rgbtGreen = round(sumGreen / (float)counter);
            temp[j][i].rgbtRed = round(sumRed / (float)counter);
        }
    }

    //copies values from temporary table
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
            image[j][i].rgbtRed = temp[j][i].rgbtRed;
        }
    }
    return;
}
