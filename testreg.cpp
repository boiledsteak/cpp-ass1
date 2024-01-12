#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

void printGrid( vector<vector<int>>& coordinates) 
{
    int maxX = 16;
    int maxY = 16;
    int spacingamt = 3;
    string border = "#";
    
    // Print coordinates with y-axis labels
    for (int y = maxY; y >= 0; --y) 
    {
        cout << left << setw(spacingamt) << y << border;

        for (int x = 0; x <= maxX; ++x) 
        {
            bool printed = false;

            for (auto& coord : coordinates) 
            {
                if (coord[0] == x && coord[1] == y) 
                {
                    cout << left << setw(spacingamt) << "X"; // Adjust width setting
                    printed = true;
                    break;
                }
            }

            if (!printed) {
                cout << left << setw(spacingamt) << " ";
            }
        }
        
        // Adjust the position of the right border
        cout << setw(spacingamt) << border;
        
        cout << "\n";
    }

    cout << setw(spacingamt) << " " << setw(spacingamt) << border << setw(border.length()) << " ";
    
    // Adjust the position of the right border
    for (int i = 0; i <= maxX; i++)
    {
        cout << left << setw(spacingamt) << border;
    }
    cout << "\n";

    cout << setw((spacingamt * 2) + border.length()) << " ";

    for (int x = 0; x <= maxX; ++x) 
    {
        cout << left << setw(spacingamt) << x;
    }
    cout << "\n";
}

int main() 
{
    vector<vector<int>> coordinates = {
        {8, 7},
        {3, 4},
        {5, 1},
        {7, 15},
        {1, 0},
        {4, 4},
        {3, 5},
        {9, 7} // Additional coordinate for testing adjacency
    };

    printGrid(coordinates);

    return 0;
}
