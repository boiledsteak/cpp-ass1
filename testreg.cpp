#include <iostream>
#include <iomanip>

using namespace std;

void printGrid(int coordinates[][2], int size) 
{
    // Find the dimensions of the grid
    int maxX = 13;
    int maxY = 20;
    // set the padding for x axis. 3 space wide default
    int spacingamt = 3;
    string spacing = string(spacingamt,' ');

    // Print points with y-axis labels
    for (int y = maxY; y >= 0; --y) 
    {
        cout << y;
        for (int x = 0; x <= maxX; ++x) 
        {
            string point = spacing + " ";
            for (int i = 0; i < size; ++i) 
            {
                if (coordinates[i][0] == x && coordinates[i][1] == y) 
                {
                    point = spacing + "X";
                }
            }
            cout << point;
        }
        cout << "\n";
    }

    // print the bottom #
    cout << " ";// move x axis lables away from y axis labels. Don't change
    for (int i=0; i <= maxX; i++)
    {
        cout << spacing+"#";
    }
    cout << "\n";

    // Print x-axis labels
    cout << " ";// move x axis lables away from y axis labels. Don't change
    for (int x = 0; x <= maxX; ++x) 
    {
        cout << spacing << x;
    }
    cout << "\n";
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
