#include "helpers.h"
#include <math.h>
#include <stdio.h>


/*
    BYTE  rgbtBlue;
    BYTE  rgbtGreen;
    BYTE  rgbtRed;
    */

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //looping through pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculating sepia value
            int sBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            int sGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);

            //changing values, checking if it is not more than 255
            image[i][j].rgbtBlue = (sBlue <= 255) ? sBlue : 255;
            image[i][j].rgbtGreen = (sGreen <= 255) ? sGreen : 255;
            image[i][j].rgbtRed = (sRed <= 255) ? sRed : 255;
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
