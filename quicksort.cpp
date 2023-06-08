#include <iostream>
using namespace std;

int partition(int arr[], int start, int end)
{
    int pivot = arr[start];
    int i = start - 1;
    for (int j = start; j < end; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            // swap
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    i++;
    int temp = arr[i];
    arr[i] = pivot;
    arr[start] = temp;
    return i; // pivot index
}

void quickSort(int arr[], int start, int end)
{
    if (start < end)
    {
        int pidx = partition(arr, start, end);
        quickSort(arr, start, pidx - 1);
        quickSort(arr, pidx + 1, end);
    }
}

int main()
{
    int arr[] = {6, 3, 9, 5, 2, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] + " ";
    }
    return 0;
}
