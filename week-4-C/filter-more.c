#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //looping through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculating average value, changing 3 to float 3.0 to avoid problems with round()
            int grey = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            //changing values
            image[i][j].rgbtBlue = grey;
            image[i][j].rgbtGreen = grey;
            image[i][j].rgbtRed = grey;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //looping through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //checking if it is not the middle of grid (for odd width)
            if (j == width - j - 1)
            {
                break;
            }
            //making variables for storing values of pixels in right half
            int tempBlue = image[i][width - j - 1].rgbtBlue;
            int tempGreen = image[i][width - j - 1].rgbtGreen;
            int tempRed = image[i][width - j - 1].rgbtRed;
            //changing values of pixels from right half to values of pixels in in left half
            image[i][width - j - 1].rgbtBlue = image[i][j].rgbtBlue;
            image[i][width - j - 1].rgbtGreen = image[i][j].rgbtGreen;
            image[i][width - j - 1].rgbtRed = image[i][j].rgbtRed;
            //changing values of pixels in left half using values stored in tempBlue, tempGreen and tempRed
            image[i][j].rgbtBlue = tempBlue;
            image[i][j].rgbtGreen = tempGreen;
            image[i][j].rgbtRed = tempRed;
            //cheking if it is not the middle of grid (for even width)
            if (j + 1 == width - j - 1)
            {
                break;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //creating new array and copy original values to it
    RGBTRIPLE imageCopy[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            imageCopy[h][w] = image[h][w];
        }
    }

    //looping through rows in image array
    for (int i = 0; i < height; i++)
    {
        //looping through pixels in image array
        for (int j = 0; j < width; j++)
        {
            //declaring variables for accumulating values of colors and counter
            int avBlue = 0;
            int avGreen = 0;
            int avRed = 0;
            //to avoid round problems making count float
            float count = 0;

            //looping through 3 rows for [i][j]'s pixel - row i - 1, row i and row i + 1 if exists
            for (int k = i == 0 ? 0 : i - 1; k < i + 2; k++)
            {
                //checking if it is out of range row
                if (k == height)
                {
                    break;
                }
                //looping through 3 pixels in [k]'s row j - 1, j, j + 1, if exists
                for (int l = j == 0 ? 0 : j - 1; l < j + 2; l++)
                {
                    //checking if pixel is out of range
                    if (l == width)
                    {
                        break;
                    }
                    //pixel [k][l], exists so adding its values (from imageCopy array!) and updating counter
                    avBlue += imageCopy[k][l].rgbtBlue;
                    avGreen += imageCopy[k][l].rgbtGreen;
                    avRed += imageCopy[k][l].rgbtRed;
                    count++;
                }
            }

            //calculating avarage
            avBlue = round(avBlue / count);
            avGreen = round(avGreen / count);
            avRed = round(avRed / count);

            //updating values of pixel
            image[i][j].rgbtBlue = avBlue;
            image[i][j].rgbtGreen = avGreen;
            image[i][j].rgbtRed = avRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //kernels
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    //creating new array and copy original values to it
    RGBTRIPLE imageCopy[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            imageCopy[h][w] = image[h][w];
        }
    }

    //looping through rows in image array
    for (int i = 0; i < height; i++)
    {
        //looping through pixels in i's row of image array
        for (int j = 0; j < width; j++)
        {
            //here I'm getting one pixel - image[i][j]
            //declaring variables for accumulating Gy and Gy values for each RGB channel
            double weightedBlueGx = 0;
            double weightedGreenGx = 0;
            double weightedRedGx = 0;
            double weightedBlueGy = 0;
            double weightedGreenGy = 0;
            double weightedRedGy = 0;
            //declaring variables for combining Gx and Gy values for each RGB channel
            double weightedBlue = 0;
            double weightedGreen = 0;
            double weightedRed = 0;


            //looping through rows of current 3x3 quare around image[i][j] and through kernels
            for (int r = i - 1, kernRow = 0; r < i + 2; r++, kernRow++)
            {
                //looping through 3 pixels in r's row (j - 1, j, j + 1) and through kernels rows
                for (int p = j - 1, kernPix = 0; p < j + 2; p++, kernPix++)
                {
                    //check if imageCopy[r][p] exists if not - color values = 0
                    //here I'm getting one pixel imageCopy[r][p] and kernels elements gx[kernRow][kernPix], gy[kernRow][kernPix]
                    int pixelBlue = (r < 0 || r == height || p < 0 || p == width) ? 0 : imageCopy[r][p].rgbtBlue;
                    int pixelGreen = (r < 0 || r == height || p < 0 || p == width) ? 0 : imageCopy[r][p].rgbtGreen;
                    int pixelRed = (r < 0 || r == height || p < 0 || p == width) ? 0 : imageCopy[r][p].rgbtRed;


                    //accumulating Gx and Gy for each channel
                    weightedBlueGx += (gx[kernRow][kernPix] * pixelBlue);
                    weightedGreenGx += (gx[kernRow][kernPix] * pixelGreen);
                    weightedRedGx += (gx[kernRow][kernPix] * pixelRed);
                    weightedBlueGy += (gy[kernRow][kernPix] * pixelBlue);
                    weightedGreenGy += (gy[kernRow][kernPix] * pixelGreen);
                    weightedRedGy += (gy[kernRow][kernPix] * pixelRed);
                }
            }
            //combining Gx and Gy values for each RGB channel, rounding them
            weightedBlue = round(sqrt((weightedBlueGx * weightedBlueGx) + (weightedBlueGy * weightedBlueGy)));
            weightedGreen = round(sqrt((weightedGreenGx * weightedGreenGx) + (weightedGreenGy * weightedGreenGy)));
            weightedRed = round(sqrt((weightedRedGx * weightedRedGx) + (weightedRedGy * weightedRedGy)));

            //changing color values for each channel
            image[i][j].rgbtBlue = (weightedBlue <= 255) ? weightedBlue : 255;
            image[i][j].rgbtGreen = (weightedGreen <= 255) ? weightedGreen : 255;
            image[i][j].rgbtRed = (weightedRed <= 255) ? weightedRed : 255;
        }
    }
    return;
}