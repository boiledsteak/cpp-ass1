#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>  // Added for setprecision

using namespace std;

// ... (Same code as provided previously)

void men7printer(vector<CityData> cities, vector<CloudData> clouds, vector<CloudData> pressure, int *xys) 
{
    // ... (Same code as provided previously)

    // Find average pressure and cloud cover
    for (const auto &count : printedCounts) 
    {
        avgp[count.first] = static_cast<double>(totalp[count.first]) / count.second;
        avgc[count.first] = static_cast<double>(totalc[count.first]) / count.second;
    }

    // Print average pressure for each city
    cout << "Average Pressure for each city:\n";
    for (const auto &ap : avgp) 
    {
        cout << "City " << ap.first << ": " << fixed << setprecision(2) << ap.second << endl;
    }

    // Print average cloud cover for each city
    cout << "Average Cloud Cover for each city:\n";
    for (const auto &ac : avgc) 
    {
        cout << "City " << ac.first << ": " << fixed << setprecision(2) << ac.second << endl;
    }
}

// ... (Same code as provided previously)
