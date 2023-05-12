#include "Sort.h"

// insertionSort
Ans insertionSort(int arr[], int n)
{
    int _CompareCount = 0;
    int _MoveCount = 0;
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        _MoveCount++;
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            _CompareCount++;
            arr[j + 1] = arr[j];
            _MoveCount++;
            j--;
        }
        arr[j + 1] = key;
        _MoveCount++;
    }
    return Ans(_CompareCount, _MoveCount);
}

// shellSort
Ans shellSort(int arr[], int n)
{
    int _CompareCount = 0;
    int _MoveCount = 0;
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; ++i)
        {
            int temp = arr[i];
            _MoveCount++;
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                _CompareCount++;
                arr[j] = arr[j - gap];
                _MoveCount++;
            }
            arr[j] = temp;
            _MoveCount++;
        }
    }
    return Ans(_CompareCount, _MoveCount);
}

// bubbleSort
Ans bubbleSort(int arr[], int n)
{
    int _CompareCount = 0;
    int _MoveCount = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                _CompareCount++;
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                _MoveCount += 3;
            }
        }
    }
    return Ans(_CompareCount, _MoveCount);
}

// quickSort
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j)
    {
        if (arr[j] < pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

Ans quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// selectionSort
Ans selectionSort(int arr[], int n)
{
    int _CompareCount = 0;
    int _MoveCount = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[j] < arr[minIndex])
            {
                _CompareCount++;
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
        _MoveCount += 3;
    }
    return Ans(_CompareCount, _MoveCount);
}

// heapSort
void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }
    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

Ans heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; --i)
    {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0; --i)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// mergeSort
void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (int i = 0; i < n1; ++i)
    {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < n2; ++i)
    {
        R[i] = arr[mid + 1 + i];
    }
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

Ans mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// radixSort
int getMax(int arr[], int n)
{
    int max = arr[0];
    for (int i = 1; i < n; ++i)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

void countSort(int arr[], int n, int exp)
{
    int output[n];
    int count[10] = {0};
    for (int i = 0; i < n; ++i)
    {
        count[(arr[i] / exp) % 10]++;
    }
    for (int i = 1; i < 10; ++i)
    {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; --i)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; ++i)
    {
        arr[i] = output[i];
    }
}

Ans radixSort(int arr[], int n)
{
    int max = getMax(arr, n);
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        countSort(arr, n, exp);
    }
}
