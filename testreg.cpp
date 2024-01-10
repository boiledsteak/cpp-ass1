#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

void printGrid(const vector<vector<int>>& coordinates) 
{
    int maxX = 16;
    int maxY = 16;
    // set the padding for x axis. Size changes dynamically
    // minimum value 3 to accommodate for 3 digit x and y axes values
    int spacingamt = 3;
    string border = "#";
    // Print coordinates with y-axis labels
    for (int y = maxY; y >= 0; --y) 
    {
        // print the left #
        cout << left << setw(spacingamt) << y << border;

        for (int x = 0; x <= maxX; ++x) 
        {
            // print the empty spaces
            cout << left << setw(spacingamt) << " ";

            for (const auto& coord : coordinates) 
            {
                if (coord[0] == x && coord[1] == y) 
                {
                    // print coordinates
                    cout << left << setw(spacingamt) << "X";
                }
            }
        }
        // cout << border; //this prints right side border but its senget due to logic error. I gave up
        cout << "\n";
    }
     // move x axis labels away from y axis labels. Don't change
    cout << setw(spacingamt) << " " << setw(spacingamt) << border << setw(border.length()) << " ";
    // print the bottom #
    for (int i = 0; i <= maxX + 1; i++)
    {
        cout << left << setw(spacingamt) << border;
    }
    cout << "\n";
    // move x axis lables away from y axis labels. Don't change
    cout << setw((spacingamt * 2) + border.length()) << " ";

    for (int x = 0; x <= maxX; ++x) 
    {
         // Print x-axis labels
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
        {1, 0}
    };

    printGrid(coordinates);

    return 0;
}
