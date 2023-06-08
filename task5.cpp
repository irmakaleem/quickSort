#include <iostream>
#include <algorithm>
using namespace std;

struct Parcel
{
    int weight;
    int index;
};

bool compareWeight(Parcel p1, Parcel p2)
{
    return p1.weight < p2.weight;
}

int main()
{
    Parcel parcels[10] = {{26, 0}, {5, 1}, {37, 2}, {1, 3}, {61, 4}, {11, 5}, {59, 6}, {15, 7}, {48, 8}, {19, 9}};

    cout << "Parcels: ";
    for (int i = 0; i < 10; i++)
    {
        cout << parcels[i].weight << " ";
    }
    cout << endl;

    sort(parcels, parcels + 10, compareWeight);

    cout << "Sorted list of Parcels according to their weights: ";
    for (int i = 0; i < 10; i++)
    {
        cout << parcels[i].weight << " ";
    }
    cout << endl;

    system("pause");
    return 0;
}
