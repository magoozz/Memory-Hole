## Project #: Homework 5 - Memory Hole

* Author: Megan Bartlett
* Class: CS452 
* Semester: Fall 2022

## Overview

This C project implements a memory allocator based on the buddy system designed to replace 'malloc'. It is able to do this through the use of a freeList, bitMap and other untils (found in until.c) that help to calculate the buddies address.
 
## Reflection

It took me quite a while to understand the architecture of how the existing skeletal code was formatted. Once I finally got a better understanding I was able to move forward with implementing the requirements. What took the most time though was getting myself to a point in which I felt that I completely understood the buddy system after completing readings. Before then working on Utils.c then freelist.c and fianlly balloc.c I also am not fully sure I created my makefile and well as my test suite in the correct way. I have not very much knowledge on those two and cannot say if they will compile correctly.

## Compiling and Using

cd hw5 
make — compile all the files
./hw5 — should run the test suite that utilizes deq.c
