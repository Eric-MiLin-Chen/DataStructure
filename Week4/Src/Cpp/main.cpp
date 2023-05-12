#include <iostream>
#include "Sort.h"
using namespace std;

int main()
{
    int arr[10];
    for (int i = 0; i < 10; ++i)
        arr[i] = 10 - i;
    for (int i = 0; i < 10; ++i)
        cout << arr[i] << " ";
    cout << endl;
    insertionSort(arr, 10);
    for (int i = 0; i < 10; ++i)
        cout << arr[i] << " ";
    cout << endl;
}