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

void bubbleSort(unsigned char arr[], int n)
{
        for (int i = 0; i < n - 1; i++)
        {
                for (int j = 0; j < n - i - 1; j++)
                {
                        if (arr[j] > arr[j + 1])
                        {
                                unsigned char tmp = arr[j];
                                arr[j] = arr[j + 1];
                                arr[j + 1] = tmp;
                        }
                }
        }
}

void quickSort(unsigned char arr[], int n)
{
        if (n <= 1)
                return; // base case

        unsigned char pivot = arr[n - 1];
        int i = -1;
        for (int j = 0; j < n - 1; j++)
        {
                if (arr[j] < pivot)
                {
                        i++;
                        std::swap(arr[i], arr[j]);
                }
        }
        std::swap(arr[i + 1], arr[n - 1]);

        quickSort(arr, i + 1);
        quickSort(arr + i + 2, n - i - 2);
}

void insertionSort(unsigned char arr[], int n)
{
        for (int i = 1; i < n; i++)
        {
                unsigned char key = arr[i];
                int j = i - 1;
                while (j >= 0 && arr[j] > key)
                {
                        arr[j + 1] = arr[j];
                        j--;
                }
                arr[j + 1] = key;
        }
}

void medianFilter(unsigned char **input, unsigned char **output, unsigned int width, unsigned int height, int kernelSize, void (*sortingFunc)(unsigned char[], int), int filterIterations);

int main(int argc, char *argv[])
{
        if (argc != 6)
        {
                cout << "Bad arguments" << endl;
                return 1;
        }
        void (*sortingFunc)(unsigned char[], int);
        char *imgInputFile = argv[1];
        char *imgOutputFile = argv[2];
        int kernelSize = atoi(argv[3]);
        int sortingAlgo = atoi(argv[4]);
        int filterIterations = atoi(argv[5]);

        switch (sortingAlgo)
        {
        case 0:
                sortingFunc = bubbleSort;
                break;
        case 1:
                sortingFunc = quickSort;
                break;
        case 2:
                sortingFunc = insertionSort;
                break;
        default:
                cout << "No sorting algorithm mapped to " << sortingAlgo << endl;
                return 1;
        }

        BMP inputImg;
        inputImg.ReadFromFile(imgInputFile);
        int height = inputImg.TellHeight();
        int width = inputImg.TellWidth();
        unsigned char **IN = new unsigned char *[width];
        for (int i = 0; i < width; i++)
        {
                IN[i] = new unsigned char[height];
        }

        unsigned char **OUT = new unsigned char *[width];
        for (int i = 0; i < width; i++)
        {
                OUT[i] = new unsigned char[height];
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
                medianFilter(IN, OUT, width, height, kernelSize, sortingFunc, filterIterations);
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
        outputImg.WriteToFile(imgOutputFile);
}

// This method will be called from main, it passes the input image, output, height and width of array. A 3 x 3 kernel is used to remove salt and pepper from the image
void medianFilter(unsigned char **input, unsigned char **output, unsigned int width, unsigned int height, int kernelSize, void (*sortingFunc)(unsigned char[], int), int filterIterations)
{
        unsigned char paddedArray[width + kernelSize - 1][height + kernelSize - 1];
        int i, j, row = 0, col = 0;
        int radius = (kernelSize - 1) / 2;
        for (i = 0; i < (width + kernelSize - 1); i++)
        {
                for (j = 0; j < (height + kernelSize - 1); j++)
                {
                        if ((i < radius) || (i >= (width + radius)) || (j < radius) || (j >= (height + radius)))
                        {
                                paddedArray[i][j] = 0;
                        }
                        else
                        {
                                paddedArray[i][j] = input[i - radius][j - radius];
                        }
                }
        }

        unsigned char sortArray[kernelSize * kernelSize];
        int sortArrayCount;
        for (int iteration = 0; iteration < filterIterations; iteration++)
        {
                for (row = radius; row <= width + radius - 1; ++row)
                {
                        for (col = radius; col <= height + radius - 1; ++col)
                        {
                                sortArrayCount = 0;

                                for (int i = -(radius); i <= (radius); i++)
                                {
                                        for (int j = -(radius); j <= (radius); j++)
                                        {
                                                sortArray[sortArrayCount] = paddedArray[row + i][col + j];
                                                sortArrayCount++;
                                        }
                                }

                                sortingFunc(sortArray, kernelSize * kernelSize);

                                if(iteration == (filterIterations - 1)) {
                                        output[row - (radius)][col - (radius)] = sortArray[((kernelSize * kernelSize - 1) / 2)];
                                } else {
                                        paddedArray[row][col] = sortArray[((kernelSize * kernelSize - 1) / 2)];
                                }
                                
                        }
                }
        }
}
