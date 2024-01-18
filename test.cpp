#include <iostream>
#include <map>

using namespace std;

void printLineChart(const map<string, double>& avgp) {
    // Find the maximum value to scale the lines
    double maxValue = 0.0;
    for (const auto& pair : avgp) {
        maxValue = max(maxValue, pair.second);
    }

    // Print the line chart
    for (int height = 10; height >= 1; --height) {
        for (const auto& pair : avgp) {
            cout << "|";
            // Print '*' if the current height is less than or equal to the scaled value
            if (static_cast<int>((pair.second / maxValue) * 10) >= height) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }

    // Print the category labels at the bottom
    for (const auto& pair : avgp) {
        cout << "|" << pair.first;
    }
    cout << "|" << endl;
}

int main() {
    // Example map with average values
    map<string, double> avgp = {{"Category1", 25.5}, {"Category2", 40.0}, {"Category3", 15.75}};

    // Call the function to print the line chart
    printLineChart(avgp);

    return 0;
}
