# Median C++ Functional - Instructions

This file is part of the FPGAHS Lab from TU Kaiserslautern (TUK).
Author: Christian De Schryver



## Goals
After completing this lab, you should be able to...

* ... create a functional reference of a median filter implementation.
* ... work with loops and 2D-arrays.
* ... configure, build, and run the C++ binary and see the output.



## Setup
The template for this task is contained in the "median.cpp" repository.

Please clone this repository to your working directory.
You will find template code for the given task and a file for the CMake build environment together with scripts for building and running the program.
In particular, execute...

* ... "./build.sh" to start the configuration and build process
* ... "./run.sh" to execute the generated binary
* ... "./clean.sh" to remove all build artefacts located in the "cmakebuild" folder.



## Task Descriptions


### Task 1: Setup

1) Clone the "median.cpp" repository to your working directory. Explore its contents and see where everything is located.
2) Execute "./build.sh" to check if the build environment is set up correctly. A binary without the Median filter functionality is created.
3) Execute "./run.sh" to run the binary. It creates an "Output.bmp" file with the generated image.
4) Set up and run your favorite IDE / editor for the following taks. We recommend using Visual Studio Code.
5) Inspect the contents of the "median.cpp" file. It contains a "TODO" tag where you should input your own solution of the Median filter.



### Task 2: Median Filter implementation

1) Open the "median.cpp" file. Implement your own median filter with kernel size 3x3 and neglect all possible border handling (ignore the borders and set them to 0 in the result).
   For a description of how median filtering works refer to https://en.wikipedia.org/wiki/Median_filter.
2) Try to compile your implementation with the "./build.sh" command until no errors are shown.
3) Execute "./run.sh" to run your successfully generated binary. If runtime errors are shown, please try to fix them and go back to step 3).
4) Inspect the "Output.bmp" image that is generated and investigate the contents.




## Exam Questions
* What is the purpose of Median filtering?
* What is the challenge regarding memory access for median filtering?
* How are 2D arrays passed to and received from functions in C / C++?
