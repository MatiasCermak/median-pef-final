// Copyright (C) 2014 University of Kaiserslautern
// Microelectronic System Design Research Group
//
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
//
// Matthias Jung <jungma@eit.uni-kl.de>
// Christian De Schryver <schryver@eit.uni-kl.de>

#include"image.h"

//Adding this method to sort the array of elements using insertion sort.
void sortElements(char arr[], int n)
{
    int i, j; 
    char key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
  
        
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


// This method will be called from main, it passes the input image, output, height and width of array. A 3 x 3 kernel is used to remove salt and pepper from the image
void medianFilter(const unsigned char input[][HEIGHT], unsigned char output[][HEIGHT], unsigned int width, unsigned int height)
{

 char paddedArray[width+2][height+2];
 int i, j, row = 0, col = 0;
 for( i = 0; i < (width+2); i++){
     for( j = 0; j < (height+2); j++){
         if((i == 0) || (i == (width+1)) || (j == 0) || (j == (height+1))){
             paddedArray[i][j] = 0;
         }
        else{
            paddedArray[i][j] = input[i][j];
        }
    }
 }

char sortArray[9];

for( row = 1; row <= width; ++row)
    {
        for( col = 1; col <= height; ++col)
        {
            //neighbor pixel values are stored in window including this pixel
            sortArray[0] = paddedArray[row-1][col-1];
            sortArray[1] = paddedArray[row-1][col];
            sortArray[2] = paddedArray[row-1][col+1];
            sortArray[3] = paddedArray[row][col-1];
            sortArray[4] = paddedArray[row][col];
            sortArray[5] = paddedArray[row][col+1];
            sortArray[6] = paddedArray[row+1][col-1];
            sortArray[7] = paddedArray[row+1][col];
            sortArray[8] = paddedArray[row+1][col+1];
  
            //sort window array
            sortElements(sortArray,9); 
            //put the median to the new array
            paddedArray[row][col]=sortArray[4];    
        }
    }


i =0; j=0;
for( i = 1; i < (width+1); i++){
     for( j = 1; j < (height+1); j++){
        
            output[i-1][j-1] = paddedArray[i][j];
        
    }

 }


}



