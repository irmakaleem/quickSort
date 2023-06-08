#include <iostream>
using namespace std;

void sortCopies(int pile1[], int pile2[], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (pile1[i] > pile1[j])
            {
                int temp = pile1[i];
                pile1[i] = pile1[j];
                pile1[j] = temp;
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (pile2[i] > pile2[j])
            {
                int temp = pile2[i];
                pile2[i] = pile2[j];
                pile2[j] = temp;
            }
        }
    }
}

void printCopies(int pile1[], int pile2[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "Pile 1: " << pile1[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "Pile 2: " << pile2[i] << " ";
    }
    cout << endl;
}

int main()
{
    int pile1[5] = {101, 102, 103, 104, 105};
    int pile2[5] = {201, 202, 203, 204, 205};
    int size = sizeof(pile1) / sizeof(pile1[0]);
    sortCopies(pile1, pile2, size);
    printCopies(pile1, pile2, size);
    return 0;
}
