//Анисимова М.В. РИ-280001
#include <iostream>
#include <chrono>
#include "queue.h"

using namespace std;
using namespace std::chrono;

constexpr int sizeArrayForSearch = 10000;
constexpr int rangeValue1 = 1000;

constexpr int sizeArrayForBSearch = 100;
constexpr int rangeValue2 = 10;

constexpr int targetValue = 7;
constexpr int countOutputValues = 50;

int Search(int* arr, int end, int desired)
{
    for (int i = 0; i < end; ++i)
        if (arr[i] == desired)
            return i;
    return -1;
}

void QuickSortWithRecursion(int* array, int start, int end)
{
    int indx = start;
    int pivot = array[end];
    for (int i = start; i < end; i++)
        if (array[i] <= pivot)
        {
            int t = array[i];
            array[i] = array[indx];
            array[indx] = t;
            indx++;
        }
    array[end] = array[indx];
    array[indx] = pivot;
    if (indx > start) QuickSortWithRecursion(array, start, indx - 1);
    if (indx < end) QuickSortWithRecursion(array, indx + 1, end);
}

void QuickSortWithoutRecursion(int* array, int start, int end)
{
    queueInt starts;
    queueInt ends;
    starts.push(start);
    ends.push(end);
    while (starts.head && ends.head)
    {
        start = starts.head->value;
        end = ends.head->value;
        int indx = start;
        int pivot = array[end];
        for (int i = start; i < end; i++)
            if (array[i] <= pivot)
            {
                int t = array[i];
                array[i] = array[indx];
                array[indx] = t;
                indx++;
            }
        array[end] = array[indx];
        array[indx] = pivot;
        starts.pop();
        ends.pop();
        if (indx > start)
        {
            starts.push(start);
            ends.push(indx - 1);
        }
        if (indx < end)
        {
            starts.push(indx + 1);
            ends.push(end);
        }
    }
}

int BSearch(int desired, int* array, int left, int right)
{
    if (left < right)
    {
        int center = (right + left) / 2;
        if (desired <= array[center])
            return BSearch(desired, array, left, center);
        else
            return BSearch(desired, array, center + 1, right);
    }
    else
    {
        if (array[right] == desired)
            return right;
        return -1;
    }
}

int BSearchWithoutRecursion(int desired, int* array, int left, int right)
{
    while (left < right)
    {
        int center = (right + left) / 2;
        if (desired <= array[center])
            right = center;
        else if (desired > array[center])
            left = center + 1;
    }
    if (array[right] == desired)
        return right;
    return -1;
}

void FullingArray(int* array, int end, int border)
{
    for (int i = 0; i < end; i++)
        array[i] = rand() % (border * 2) - border;
}

void PrintArray(int* array)
{
    for (int i = 0; i < countOutputValues; i++)
        cout << array[i] << " ";
    cout << endl;
}

void ComparingSpeedSearchElement()
{
    srand(time(NULL));
    int arr[sizeArrayForSearch];
    FullingArray(arr, sizeArrayForSearch, rangeValue1);
    auto start = steady_clock::now();
    int index = Search(arr, sizeArrayForSearch, targetValue);
    auto stop = steady_clock::now();
    auto time = duration_cast<nanoseconds>(stop - start);
    cout << "Time Search in array " << sizeArrayForSearch << ": " << time.count() << " nanoseconds" << endl;

    QuickSortWithRecursion(arr, 0, sizeArrayForSearch - 1);
    start = steady_clock::now();
    index = BSearch(targetValue, arr, 0, sizeArrayForSearch - 1);
    stop = steady_clock::now();
    time = duration_cast<nanoseconds>(stop - start);
    cout << "Time BSearch in array " << sizeArrayForSearch << ": " << time.count() << " nanoseconds" << endl;
}

int main()
{
    int arr[sizeArrayForSearch];
    FullingArray(arr, sizeArrayForSearch, rangeValue1);
    int index = Search(arr, sizeArrayForSearch, targetValue);
    if (index == -1)
        cout << "Element not found" << endl;
    else
        cout << "Search() Result: Index = " << index << endl;

    int arr2[sizeArrayForBSearch];
    FullingArray(arr2, sizeArrayForBSearch, rangeValue2);
    cout << "The array before sorting : ";
    PrintArray(arr2);
    QuickSortWithRecursion(arr2, 0, sizeArrayForBSearch - 1);
    cout << "Array after sorting with recursion : ";
    PrintArray(arr2);

    FullingArray(arr2, sizeArrayForBSearch, rangeValue2);
    cout << "The array before sorting : ";
    PrintArray(arr2);
    QuickSortWithoutRecursion(arr2, 0, sizeArrayForBSearch - 1);
    cout << "Array after sorting without recursion : ";
    PrintArray(arr2);

    int result = BSearch(targetValue, arr2, 0, sizeArrayForBSearch - 1);
    if (result == -1)
        cout << "Element not found" << endl;
    else
        cout << "BSearch() Result: Index = " << result << endl;
    result = BSearchWithoutRecursion(targetValue, arr2, 0, sizeArrayForBSearch - 1);
    if (result == -1)
        cout << "Element not found" << endl;
    else
        cout << "BSearchWithoutRecursion() Result: Index = " << result << endl;
    ComparingSpeedSearchElement();
}

