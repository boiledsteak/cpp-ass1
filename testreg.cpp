#include <iostream>
#include <iomanip>

using namespace std;

void printGrid(int coordinates[][2], int size) 
{
    // Find the dimensions of the grid. //TODO Rmb to cast string to int. Double to int
    int maxX = 16;
    int maxY = 16;
    int count = 0;
    // set the padding for x axis. Size changes dynamically
    // minimum values to accommodate for 3 digit x and y axes values
    int spacingamt = 3; //default minimum 4
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
            for (int i = 0; i < size; ++i) 
            {
                // print coordinates
                if (coordinates[i][0] == x && coordinates[i][1] == y) 
                {
                    cout << left << setw(spacingamt) << "X";
                    
                }
                                                             
            }
            
        }
        
        // cout << border; //this prints right side border but its senget due to logic error. I gave up
        cout << "\n";
    }

    // move x axis lables away from y axis labels. Don't change
    cout << setw(spacingamt) << " " << setw(spacingamt) << border << setw(border.length()) << " ";

    // print the bottom #
    for (int i=0; i <= maxX+1; i++)
    {
        cout << left << setw(spacingamt) << border;
    }
    cout << "\n";

    // Print x-axis labels
    cout << setw((spacingamt*2)+border.length()) << " ";// move x axis lables away from y axis labels. Don't change
    for (int x = 0; x <= maxX; ++x) 
    {
        cout << left << setw(spacingamt) << x;
    }
    cout <<"\n";
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
