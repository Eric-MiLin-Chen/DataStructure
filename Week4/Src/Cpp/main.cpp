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
    Ans ans = quickSort(arr, 10);
    for (int i = 0; i < 10; ++i)
        cout << arr[i] << " ";
    cout << endl;
    cout << ans.CompareCount << " " << ans.MoveCount << endl;
}