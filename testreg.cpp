#include <iostream>

using namespace std;

void printGrid(int coordinates[][2], int size) 
{
    // Find the dimensions of the grid
    int maxX = 20;
    int maxY = 20;

    // Print x-axis labels
    cout << "  ";
    for (int x = 0; x <= maxX; ++x) 
    {
        cout << x  << " ";
    }
    cout << "\n";

    // Print grid with y-axis labels
    for (int y = 0; y <= maxY; ++y) 
    {
        cout << y  << " ";
        for (int x = 0; x <= maxX; ++x) 
        {
            char marking;
            for (int i = 0; i < size; ++i) 
            {
                if (coordinates[i][0] == x && coordinates[i][1] == y) 
                {
                    marking = 'X'; // or any other symbol you prefer
                    break;
                }
            }
            cout << marking << " ";
        }
        cout << "\n";
    }
}

int main() 
{
    // Example array of coordinates
    int coordinates[][2] = {
        {8, 7},
        {3, 4},
        {5, 1},
        {7, 15},
        {1, 0}
    };
    // find the number of x to print
    int size = sizeof(coordinates) / sizeof(coordinates[0]);

    // Print the grid
    printGrid(coordinates, size);

    return 0;
}
