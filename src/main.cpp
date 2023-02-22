// Copyright (C) 2014 University of Kaiserslautern
// Microelectronic System Design Research Group
//
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
//
// Matthias Jung <jungma@eit.uni-kl.de>
// Christian De Schryver <schryver@eit.uni-kl.de>

#include <iostream>
#include <fstream>
#include "profiler.h"
#include "EasyBMP/EasyBMP.h"

using namespace std;

void medianFilter(unsigned char **input, unsigned char **output, unsigned int width, unsigned int height);

int main(int argc, char *argv[])
{
        if(argc != 2) {
                cout << "Error: Cantidad de argumentos inválida." << endl;
                return 1;
        }
        char* imgFile = argv[1];
        BMP inputImg;
        inputImg.ReadFromFile(imgFile);
        int height = inputImg.TellHeight();
        int width = inputImg.TellWidth();
        unsigned char **IN = new unsigned char *[height];
        for (int i = 0; i < height; i++)
        {
                IN[i] = new unsigned char[width];
        }

        unsigned char **OUT = new unsigned char *[height];
        for (int i = 0; i < height; i++)
        {
                OUT[i] = new unsigned char[width];
        }

        for (int i = 0; i < width; i++)
        {
                for (int j = 0; j < height; j++)
                {
                        IN[i][j] = inputImg(i, j)->Red;
                }
        }

        // Do a profiling of this block:
        {
                Profiler p;
                medianFilter(IN, OUT, width, height);
        }

        // Save Image:
        BMP outputImg;
        outputImg.SetSize(width, height);
        int x;
        for (x = 0; x < width; x++)
        {
                int y;
                for (y = 0; y < height; y++)
                {
                        outputImg(x, y)->Red = OUT[x][y];
                        outputImg(x, y)->Green = OUT[x][y];
                        outputImg(x, y)->Blue = OUT[x][y];
                        outputImg(x, y)->Alpha = 0;
                }
        }
        outputImg.WriteToFile("Output.bmp");
}

// Adding this method to sort the array of elements using bubble sort.
void sortElements(char arr[], int n)
{
        for (int i = 0; i < n - 1; i++)
        {
                for (int j = 0; j < n - i - 1; j++)
                {
                        if (arr[j] > arr[j + 1])
                        {
                                char tmp = arr[j];
                                arr[j] = arr[j + 1];
                                arr[j + 1] = tmp;
                        }
                }
        }
}

// This method will be called from main, it passes the input image, output, height and width of array. A 7 x 7 kernel is used to remove salt and pepper from the image
void medianFilter(unsigned char **input, unsigned char **output, unsigned int width, unsigned int height)
{
        char paddedArray[width + 6][height + 6];
        int i, j, row = 0, col = 0;
        for (i = 0; i < (width + 5); i++)
        {
                for (j = 0; j < (height + 5); j++)
                {
                        if ((i < 3) || (i >= (width + 1)) || (j < 3) || (j >= (height + 1)))
                        {
                                paddedArray[i][j] = 0;
                        }
                        else
                        {
                                paddedArray[i][j] = input[i - 3][j - 3];
                        }
                }
        }

        char sortArray[49];

        for (row = 3; row <= width + 2; ++row)
        {
                for (col = 3; col <= height + 2; ++col)
                {
                        sortArray[0] = paddedArray[row - 3][col - 3];
                        sortArray[1] = paddedArray[row - 3][col - 2];
                        sortArray[2] = paddedArray[row - 3][col - 1];
                        sortArray[3] = paddedArray[row - 3][col];
                        sortArray[4] = paddedArray[row - 3][col + 1];
                        sortArray[5] = paddedArray[row - 3][col + 2];
                        sortArray[6] = paddedArray[row - 3][col + 3];

                        sortArray[7] = paddedArray[row - 2][col - 3];
                        sortArray[8] = paddedArray[row - 2][col - 2];
                        sortArray[9] = paddedArray[row - 2][col - 1];
                        sortArray[10] = paddedArray[row - 2][col];
                        sortArray[11] = paddedArray[row - 2][col + 1];
                        sortArray[12] = paddedArray[row - 2][col + 2];
                        sortArray[13] = paddedArray[row - 2][col + 3];

                        sortArray[14] = paddedArray[row - 1][col - 3];
                        sortArray[15] = paddedArray[row - 1][col - 2];
                        sortArray[16] = paddedArray[row - 1][col - 1];
                        sortArray[17] = paddedArray[row - 1][col];
                        sortArray[18] = paddedArray[row - 1][col + 1];
                        sortArray[19] = paddedArray[row - 1][col + 2];
                        sortArray[20] = paddedArray[row - 1][col + 3];

                        sortArray[21] = paddedArray[row][col - 3];
                        sortArray[22] = paddedArray[row][col - 2];
                        sortArray[23] = paddedArray[row][col - 1];
                        sortArray[24] = paddedArray[row][col];
                        sortArray[25] = paddedArray[row][col + 1];
                        sortArray[26] = paddedArray[row][col + 2];
                        sortArray[27] = paddedArray[row][col + 3];

                        sortArray[29] = paddedArray[row + 1][col - 2];
                        sortArray[30] = paddedArray[row + 1][col - 1];
                        sortArray[31] = paddedArray[row + 1][col];
                        sortArray[32] = paddedArray[row + 1][col + 1];
                        sortArray[33] = paddedArray[row + 1][col + 2];
                        sortArray[34] = paddedArray[row + 1][col + 3];

                        sortArray[35] = paddedArray[row + 2][col - 3];
                        sortArray[36] = paddedArray[row + 2][col - 2];
                        sortArray[37] = paddedArray[row + 2][col - 1];
                        sortArray[38] = paddedArray[row + 2][col];
                        sortArray[39] = paddedArray[row + 2][col + 1];
                        sortArray[40] = paddedArray[row + 2][col + 2];
                        sortArray[41] = paddedArray[row + 2][col + 3];

                        sortArray[42] = paddedArray[row + 3][col - 3];
                        sortArray[43] = paddedArray[row + 3][col - 2];
                        sortArray[44] = paddedArray[row + 3][col - 1];
                        sortArray[45] = paddedArray[row + 3][col];
                        sortArray[46] = paddedArray[row + 3][col + 1];
                        sortArray[47] = paddedArray[row + 3][col + 2];
                        sortArray[48] = paddedArray[row + 3][col + 3];

                        sortElements(sortArray, 49);
                        paddedArray[row - 3][col - 3] = sortArray[4];
                }
        }
        i = 0;
        j = 0;
        for (i = 1; i < (width + 1); i++)
        {
                for (j = 1; j < (height + 1); j++)
                {

                        output[i - 1][j - 1] = paddedArray[i][j];
                }
        }
}
