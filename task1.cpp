#include <iostream>
using namespace std;

void quickSort(int array[], int low, int high)
{
    if (low < high)
    {
        int pivot = array[high];
        int i = (low - 1);
        for (int j = low; j < high; j++)
        {
            if (array[j] <= pivot)
            {
                i++;
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        int temp = array[i + 1];
        array[i + 1] = array[high];
        array[high] = temp;
        quickSort(array, low, i);
        quickSort(array, i + 2, high);
    }
}

void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

int main()
{
    int data[] = {52, 37, 63, 14, 17, 8, 6, 25};
    int size = sizeof(data) / sizeof(data[0]);
    printArray(data, size);
    quickSort(data, 0, size - 1);
    cout << "Sorted array in ascending order: \n";
    printArray(data, size);
    return 0;
}
