// Week4Chapter1Challenge1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
    Challenges:
        Implement a sorting algorithm using the chrono library profile, sometimes using varying sample sizes
*/

#include <iostream>
#include <chrono>
#include <stdlib.h>

const int RUN_SIZE = 100;
const int ARRAY_SIZE = 1000;

using namespace std;

void FillArray(int arrayToFill[], int sizeOfArray);
void BubbleSort(int arrayToSort[], int sizeOfArray);
void BubbleSortEfficient(int arrayToSort[], int arraySize);
void InsertionSort(int arrayToSort[], int arraySize);
void PrintArray(int arrayToPrint[], int sizeOfArray);
uint32_t GetNanos();

/*
    Testing with a RUN_SIZE of 100 and ARRAY_SIZE OF 1000...
    Bubble Sort average time:       1,172,687 ns
    Insertion Sort average time:      404,684 ns
*/
int main()
{
    uint32_t startNanos = 0;
    uint32_t endNanos = 0;

    uint32_t totalNanos = 0;

    for (int i = 0; i < RUN_SIZE; i++)
    {
        int dataset[ARRAY_SIZE];

        srand(time(nullptr));

        FillArray(dataset, ARRAY_SIZE);

        //PrintArray(dataset, ARRAY_SIZE);

        startNanos = GetNanos();
        InsertionSort(dataset, ARRAY_SIZE);
        endNanos = GetNanos();

        //PrintArray(dataset, ARRAY_SIZE);

        totalNanos += (endNanos - startNanos);
    }

    std::cout << "Average time: " << totalNanos / RUN_SIZE << endl << endl;
}

void PrintArray(int arrayToPrint[], int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; i++)
    {
        std::cout << arrayToPrint[i];

        if (i < sizeOfArray - 1)
        {
            std::cout << ", ";
        }
    }

    std::cout << endl << endl;
}

void FillArray(int arrayToFill[], int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        arrayToFill[i] = rand() % (ARRAY_SIZE * 10) + 1;
    }
}

void BubbleSort(int arrayToSort[], int arraySize)
{
    for (int pass = 0; pass < arraySize; pass++)
    {
        for (int i = 0; i < arraySize - 1; i++)
        {
            if (arrayToSort[i] > arrayToSort[i + 1])
            {
                int temp = arrayToSort[i];
                arrayToSort[i] = arrayToSort[i + 1];
                arrayToSort[i + 1] = temp;
            }
        }
    }
}

/*
    Bubble Sort but don't check the "sorted" section of the array.
    Using the VS diagnostic tools this seemed to have a considerable impact.
*/
void BubbleSortEfficient(int arrayToSort[], int arraySize)
{
    for (int pass = 0; pass < arraySize; pass++)
    {
        for (int i = 0; i < arraySize - 1 - pass; i++)
        {
            if (arrayToSort[i] > arrayToSort[i + 1])
            {
                int temp = arrayToSort[i];
                arrayToSort[i] = arrayToSort[i + 1];
                arrayToSort[i + 1] = temp;
            }
        }
    }
}

void InsertionSort(int arrayToSort[], int arraySize)
{
    for (int i = 1; i < arraySize; i++)
    {
        int current = arrayToSort[i];
        int j;
        
        for (j = i - 1; j >= 0 && arrayToSort[j] > current; j--)
        {
            arrayToSort[j + 1] = arrayToSort[j];
        }

        arrayToSort[j + 1] = current;
    }
}

uint32_t GetNanos()
{
    using namespace std::chrono;
    return static_cast<uint32_t>(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
}