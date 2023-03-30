#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pix[height][width];
    float green = 0, blue = 0, red = 0;

    //copy the image to a new array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pix[i][j].rgbtGreen = image[i][j].rgbtGreen;
            pix[i][j].rgbtBlue = image[i][j].rgbtBlue;
            pix[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    float ave = 0;

    //take the average color of each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ave = (round)((pix[i][j].rgbtBlue + pix[i][j].rgbtGreen + pix[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = ave;
            image[i][j].rgbtGreen = ave;
            image[i][j].rgbtRed = ave;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //swap the pixels
    RGBTRIPLE temp = image[0][0];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pix[height][width];
    float green = 0, blue = 0, red = 0;

    //copy the image to a new array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pix[i][j].rgbtGreen = image[i][j].rgbtGreen;
            pix[i][j].rgbtBlue = image[i][j].rgbtBlue;
            pix[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //top edge
            if (i == 0)
            {
                //upper left corner
                if (j == 0)
                {
                    green = (round)((pix[i][j].rgbtGreen + pix[i][j + 1].rgbtGreen + pix[i + 1][j].rgbtGreen +
                                    pix[i + 1][j + 1].rgbtGreen) / 4.0);
                    blue = (round)((pix[i][j].rgbtBlue + pix[i][j + 1].rgbtBlue + pix[i + 1][j].rgbtBlue +
                                    pix[i + 1][j + 1].rgbtBlue) / 4.0);
                    red = (round)((pix[i][j].rgbtRed + pix[i][j + 1].rgbtRed + pix[i + 1][j].rgbtRed +
                                    pix[i + 1][j + 1].rgbtRed) / 4.0);

                    image[i][j].rgbtGreen = green;
                    image[i][j].rgbtBlue = blue;
                    image[i][j].rgbtRed = red;
                }
                //upper right corner
                else if (j == width - 1)
                {
                    green = (round)((pix[i][j].rgbtGreen + pix[i][j - 1].rgbtGreen + pix[i + 1][j].rgbtGreen +
                                    pix[i + 1][j - 1].rgbtGreen) / 4.0);
                    blue = (round)((pix[i][j].rgbtBlue + pix[i][j - 1].rgbtBlue + pix[i + 1][j].rgbtBlue +
                                    pix[i + 1][j - 1].rgbtBlue) / 4.0);
                    red = (round)((pix[i][j].rgbtRed + pix[i][j - 1].rgbtRed + pix[i + 1][j].rgbtRed +
                                    pix[i + 1][j - 1].rgbtRed) / 4.0);

                    image[i][j].rgbtGreen = green;
                    image[i][j].rgbtBlue = blue;
                    image[i][j].rgbtRed = red;
                }
                //top edge
                else
                {
                    green = (round)((pix[i][j].rgbtGreen + pix[i][j + 1].rgbtGreen + pix[i][j - 1].rgbtGreen +
                                    pix[i + 1][j].rgbtGreen + pix[i + 1][j + 1].rgbtGreen + pix[i + 1][j - 1].rgbtGreen) / 6.0);
                    blue = (round)((pix[i][j].rgbtBlue + pix[i][j + 1].rgbtBlue + pix[i][j - 1].rgbtBlue +
                                    pix[i + 1][j].rgbtBlue + pix[i + 1][j + 1].rgbtBlue + pix[i + 1][j - 1].rgbtBlue) / 6.0);
                    red = (round)((pix[i][j].rgbtRed + pix[i][j + 1].rgbtRed + pix[i][j - 1].rgbtRed + pix[i + 1][j].rgbtRed +
                                    pix[i + 1][j + 1].rgbtRed + pix[i + 1][j - 1].rgbtRed) / 6.0);

                    image[i][j].rgbtGreen = green;
                    image[i][j].rgbtBlue = blue;
                    image[i][j].rgbtRed = red;
                }
            }
            //bottom edge
            else if (i == height - 1)
            {
                //lower left corner
                if (j == 0)
                {
                    green = (round)((pix[i][j].rgbtGreen + pix[i][j + 1].rgbtGreen + pix[i - 1][j].rgbtGreen +
                                     pix[i - 1][j + 1].rgbtGreen) / 4.0);
                    blue = (round)((pix[i][j].rgbtBlue + pix[i][j + 1].rgbtBlue + pix[i - 1][j].rgbtBlue +
                                    pix[i - 1][j + 1].rgbtBlue) / 4.0);
                    red = (round)((pix[i][j].rgbtRed + pix[i][j + 1].rgbtRed + pix[i - 1][j].rgbtRed +
                                   pix[i - 1][j + 1].rgbtRed) / 4.0);

                    image[i][j].rgbtGreen = green;
                    image[i][j].rgbtBlue = blue;
                    image[i][j].rgbtRed = red;
                }
                //lower right corner
                else if (j == width - 1)
                {
                    green = (round)((pix[i][j].rgbtGreen + pix[i][j - 1].rgbtGreen + pix[i - 1][j].rgbtGreen +
                                     pix[i - 1][j - 1].rgbtGreen) / 4.0);
                    blue = (round)((pix[i][j].rgbtBlue + pix[i][j - 1].rgbtBlue + pix[i - 1][j].rgbtBlue +
                                    pix[i - 1][j - 1].rgbtBlue) / 4.0);
                    red = (round)((pix[i][j].rgbtRed + pix[i][j - 1].rgbtRed + pix[i - 1][j].rgbtRed +
                                   pix[i - 1][j - 1].rgbtRed) / 4.0);

                    image[i][j].rgbtGreen = green;
                    image[i][j].rgbtBlue = blue;
                    image[i][j].rgbtRed = red;
                }
                //lower edge
                else
                {
                    green = (round)((pix[i][j].rgbtGreen + pix[i][j + 1].rgbtGreen + pix[i][j - 1].rgbtGreen +
                                     pix[i - 1][j].rgbtGreen + pix[i - 1][j + 1].rgbtGreen + pix[i - 1][j - 1].rgbtGreen) / 6.0);
                    blue = (round)((pix[i][j].rgbtBlue + pix[i][j + 1].rgbtBlue + pix[i][j - 1].rgbtBlue +
                                    pix[i - 1][j].rgbtBlue + pix[i - 1][j + 1].rgbtBlue + pix[i - 1][j - 1].rgbtBlue) / 6.0);
                    red = (round)((pix[i][j].rgbtRed + pix[i][j + 1].rgbtRed + pix[i][j - 1].rgbtRed + pix[i - 1][j].rgbtRed +
                                   pix[i - 1][j + 1].rgbtRed + pix[i - 1][j - 1].rgbtRed) / 6.0);

                    image[i][j].rgbtGreen = green;
                    image[i][j].rgbtBlue = blue;
                    image[i][j].rgbtRed = red;
                }
            }
            //the middle
            else
            {
                //left edge
                if (j == 0)
                {
                    green = (round)((pix[i][j].rgbtGreen + pix[i][j + 1].rgbtGreen + pix[i - 1][j].rgbtGreen +
                                     pix[i - 1][j + 1].rgbtGreen + pix[i + 1][j].rgbtGreen + pix[i + 1][j + 1].rgbtGreen) / 6.0);
                    blue = (round)((pix[i][j].rgbtBlue + pix[i][j + 1].rgbtBlue + pix[i - 1][j].rgbtBlue +
                                    pix[i - 1][j + 1].rgbtBlue + pix[i + 1][j].rgbtBlue + pix[i + 1][j + 1].rgbtBlue) / 6.0);
                    red = (round)((pix[i][j].rgbtRed + pix[i][j + 1].rgbtRed + pix[i - 1][j].rgbtRed +
                                   pix[i - 1][j + 1].rgbtRed + pix[i + 1][j].rgbtRed + pix[i + 1][j + 1].rgbtRed) / 6.0);

                    image[i][j].rgbtGreen = green;
                    image[i][j].rgbtBlue = blue;
                    image[i][j].rgbtRed = red;
                }
                //right edge
                else if (j == width - 1)
                {
                    green = (round)((pix[i][j].rgbtGreen + pix[i][j - 1].rgbtGreen + pix[i + 1][j].rgbtGreen +
                                     pix[i + 1][j - 1].rgbtGreen + pix[i - 1][j].rgbtGreen + pix[i - 1][j - 1].rgbtGreen) / 6.0);
                    blue = (round)((pix[i][j].rgbtBlue + pix[i][j - 1].rgbtBlue + pix[i + 1][j].rgbtBlue +
                                    pix[i + 1][j - 1].rgbtBlue + pix[i - 1][j].rgbtBlue + pix[i - 1][j - 1].rgbtBlue) / 6.0);
                    red = (round)((pix[i][j].rgbtRed + pix[i][j - 1].rgbtRed + pix[i + 1][j].rgbtRed +
                                   pix[i + 1][j - 1].rgbtRed + pix[i - 1][j].rgbtRed + pix[i - 1][j - 1].rgbtRed) / 6.0);

                    image[i][j].rgbtGreen = green;
                    image[i][j].rgbtBlue = blue;
                    image[i][j].rgbtRed = red;
                }
                //middle
                else
                {
                    green = (round)((pix[i][j].rgbtGreen + pix[i][j + 1].rgbtGreen + pix[i][j - 1].rgbtGreen +
                                     pix[i + 1][j].rgbtGreen + pix[i + 1][j + 1].rgbtGreen + pix[i + 1][j - 1].rgbtGreen +
                                     pix[i - 1][j].rgbtGreen + pix[i - 1][j + 1].rgbtGreen + pix[i - 1][j - 1].rgbtGreen) / 9.0);
                    blue = (round)((pix[i][j].rgbtBlue + pix[i][j + 1].rgbtBlue + pix[i][j - 1].rgbtBlue +
                                    pix[i + 1][j].rgbtBlue + pix[i + 1][j + 1].rgbtBlue + pix[i + 1][j - 1].rgbtBlue +
                                    pix[i - 1][j].rgbtBlue + pix[i - 1][j + 1].rgbtBlue + pix[i - 1][j - 1].rgbtBlue) / 9.0);
                    red = (round)((pix[i][j].rgbtRed + pix[i][j + 1].rgbtRed + pix[i][j - 1].rgbtRed + pix[i + 1][j].rgbtRed +
                                   pix[i + 1][j + 1].rgbtRed + pix[i + 1][j - 1].rgbtRed +pix[i - 1][j].rgbtRed +
                                   pix[i - 1][j + 1].rgbtRed + pix[i - 1][j - 1].rgbtRed) / 9.0);

                    image[i][j].rgbtGreen = green;
                    image[i][j].rgbtBlue = blue;
                    image[i][j].rgbtRed = red;
                }
            }
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //gx and gy
    RGBTRIPLE pix[height][width];
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    //copy the image to a new array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pix[i][j].rgbtGreen = image[i][j].rgbtGreen;
            pix[i][j].rgbtBlue = image[i][j].rgbtBlue;
            pix[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    int xg, xb, xr, yg, yb, yr;

    //do the kernal
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            xg = xb = xr = yg = yb = yr = 0;
            for (int h = -1; h < 2; h++)
            {
                for (int w = -1; w < 2; w++)
                {
                    if (i + h < 0 || i + h > height - 1)
                    {
                        continue;
                    }
                    if (j + w < 0 || j + w > width - 1)
                    {
                        continue;
                    }
                    xr += pix[i + h][j + w].rgbtRed * Gx[h + 1][w + 1];
                    xg += pix[i + h][j + w].rgbtGreen * Gx[h + 1][w + 1];
                    xb += pix[i + h][j + w].rgbtBlue * Gx[h + 1][w + 1];

                    yr += pix[i + h][j + w].rgbtRed * Gy[h + 1][w + 1];
                    yg += pix[i + h][j + w].rgbtGreen * Gy[h + 1][w + 1];
                    yb += pix[i + h][j + w].rgbtBlue * Gy[h + 1][w + 1];
                }
            }
            image[i][j].rgbtRed = fmin(round(sqrt(xr * xr  + yr * yr)), 255);
            image[i][j].rgbtGreen = fmin(round(sqrt(xg * xg + yg * yg)), 255);
            image[i][j].rgbtBlue = fmin(round(sqrt(xb * xb + yb * yb)), 255);
        }
    }

    return;
}
