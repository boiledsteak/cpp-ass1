#include <iostream>
#include <iomanip>

const int GRID_SIZE = 10;  // Adjust the grid size as needed

void printGrid(int coordinates[][2], int numPoints) {
    // Print top border
    std::cout << "+----------------------+" << std::endl;

    // Print y-axis and grid
    for (int y = GRID_SIZE - 1; y >= 0; y--) {
        // Print y-axis label
        std::cout << "| " << std::setw(2) << y << " ";

        // Print grid points
        for (int x = 0; x < GRID_SIZE; x++) {
            bool pointExists = false;
            for (int i = 0; i < numPoints; i++) {
                if (coordinates[i][0] == x && coordinates[i][1] == y) {
                    pointExists = true;
                    break;
                }
            }
            if (pointExists) {
                std::cout << "* ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "|" << std::endl;
    }

    // Print bottom border
    std::cout << "+----------------------+" << std::endl;

    // Print x-axis labels
    std::cout << "  ";
    for (int x = 0; x < GRID_SIZE; x++) {
        std::cout << std::setw(2) << x << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Example coordinates (you can modify this array)
    int coordinates[][2] = {{1, 2}, {3, 4}, {6, 8}};

    // Calculate the number of points in the array
    int numPoints = sizeof(coordinates) / sizeof(coordinates[0]);

    // Print the grid with coordinates
    printGrid(coordinates, numPoints);

    return 0;
}
