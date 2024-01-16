#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct CityData 
{
    int x;
    int y;
    int category;
    string cityName;

    CityData(string &str) 
    {
        stringstream ss(str);
        char discard;
        ss >> discard >> x >> discard >> y >> discard >> category >> discard >> cityName;
    }
};

struct CloudData 
{
    int x;
    int y;
    int cloud;

    CloudData(string &strr) 
    {
        stringstream sss(strr);
        char discard;
        sss >> discard >> x >> discard >> y >> discard >> cloud;
    }
};

// Struct to store coordinates and category
struct CoordinatesWithCategory 
{
    int x;
    int y;
    int category;

    CoordinatesWithCategory(int x, int y, int category) : x(x), y(y), category(category) {}
};

void men7printer(vector<CityData> cities, vector<CloudData> clouds, vector<CloudData> pressure, int *xys) 
{
    int minX = xys[0];
    int maxX = xys[1];
    int minY = xys[2];
    int maxY = xys[3];

    int innerp = 0;
    int outerp = 0; // should be 314 with default values

    // Unordered map to store innerp values for each category
    unordered_map<int, int> innerpByCategory;

    //-------------------- END processing X
    for (int y = maxY; y >= minY; --y) 
    {
        for (int x = minX; x <= maxX; ++x) 
        {
            bool printed = false;

            for (auto &city : cities)
            {
                for (auto &cloud : clouds)
                {
                    if (city.x == x && city.y == y && city.x == cloud.x && city.y == cloud.y) 
                    {
                        for (auto &p : pressure)
                        {
                            if (p.x == x && p.y == y)
                            {
                                printed = true;
                                innerp += p.cloud;

                                // Store innerp value in the unordered_map for the corresponding category
                                innerpByCategory[city.category] += p.cloud;
                                break;
                            }
                        }
                        break;
                    }
                }
            }

            if (!printed) 
            {
                // Check for surrounding coordinates
                bool surroundPrinted = false;
                for (auto &city : cities) 
                {
                    if (abs(city.x - x) <= 1 && abs(city.y - y) <= 1 ) 
                    {
                        // Store coordinates of "X" along with city category
                        outerp += p.cloud;
                        surroundPrinted = true;
                        break;
                    }                 
                }
            }
        }
    }
    //-------------------- END processing X

    // Output or use the summed values as needed...
    cout << "Inner Pressure: " << innerp << endl;
    cout << "Outer Pressure: " << outerp << endl;

    // Print innerp values for each category
    cout << "Inner Pressure by Category:\n";
    for (const auto &entry : innerpByCategory) 
    {
        cout << "Category " << entry.first << ": " << entry.second << endl;
    }
}
