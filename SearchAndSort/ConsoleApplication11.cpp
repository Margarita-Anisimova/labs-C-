//Анисимова М.В. РИ-280001
#include <iostream>
#include <time.h>
#include <vector> 
#include <queue> 
#include <chrono>

using namespace std;
using namespace std::chrono;

int Search(int* arr, int end, int desired)
{
    for (int i = 0; i < end;++i)
        if (arr[i] == desired)
            return i;
    return -1;
}

int DistributionElements(int* array, int start, int end)
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
    return indx;
}

void QuickSortWithRecursion(int* array, int start, int end)
{    
    int indx = DistributionElements(array, start, end);    
    if (indx > start) QuickSortWithRecursion(array, start, indx - 1);
    if (indx < end) QuickSortWithRecursion(array, indx + 1, end);
}

void QuickSortWithoutRecursion(int* array, int start, int end)
{    
    queue<int> starts ;
    queue<int> ends ;
    starts.push(start);
    ends.push(end);
    while (!starts.empty())
    {
        start = starts.front();
        end = ends.front();
        int indx = DistributionElements(array, start, end);
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
        else if(desired > array[center])
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
    return array;
}

void PrintArray(int* array)
{
    for (int i = 0; i < 50; i++)
        cout << array[i] << " ";
    cout << endl;
}

void ComparingSpeedSearchElement()
{
    int arr[10000];
    int s = sizeof(arr)/sizeof(&arr);
    FullingArray(arr, s, 1000);
    auto start = steady_clock::now();
    int index = Search(arr, s, 344);
    auto stop = steady_clock::now();
    auto time = duration_cast<nanoseconds>(stop - start);
    cout << "Time Search: " << time.count() << " nanoseconds" << endl;

    QuickSortWithRecursion(arr, 0, s - 1);
    start = steady_clock::now();   
    index = BSearch(345, arr, 0, s - 1);
    stop = steady_clock::now();
    time = duration_cast<nanoseconds>(stop - start);
    cout << "Time BSearch: " << time.count() << " nanoseconds" << endl;
}

int main()
{
    int arr[10000];
    int s = sizeof(arr) / sizeof(&arr);
    srand(time(NULL));
    FullingArray(arr, s, 1000);
    int index = Search(arr, s, 376);
    if (index == -1)
        cout << "Element not found" << endl;
    else 
        cout << "Search() Result: Index = " << index << endl;

    int arr2[100];
    s = sizeof(arr2) / sizeof(&arr2);
    FullingArray(arr2, s, 10);
    cout << "The array before sorting : ";
    PrintArray(arr2);
    QuickSortWithRecursion(arr2, 0, s-1);
    cout << "Array after sorting with recursion : ";
    PrintArray(arr2);    

    FullingArray(arr2, s, 10);
    cout << "The array before sorting : ";    
    PrintArray(arr2);
    QuickSortWithoutRecursion(arr2, 0, s - 1);
    cout << "Array after sorting without recursion : ";
    PrintArray(arr2);
    
    int result = BSearch(7, arr2, 0, s - 1);
    if (result == -1)
        cout << "Element not found" << endl;
    else
        cout << "BSearch() Result: Index = " << result << endl;
    result = BSearchWithoutRecursion(7, arr2, 0, s - 1);    
    if (result == -1)
        cout << "Element not found" << endl;
    else
        cout << "BSearchWithoutRecursion() Result: Index = " << result << endl;
    ComparingSpeedSearchElement();
}

