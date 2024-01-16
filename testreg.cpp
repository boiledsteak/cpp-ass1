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

    // Vector to store coordinates of "X" along with city category
    vector<CoordinatesWithCategory> xCoordinates;

    // Map to store outerp sum for each category
    unordered_map<int, int> categorySums;

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
                        xCoordinates.push_back(CoordinatesWithCategory(x, y, city.category));
                        surroundPrinted = true;
                        break;
                    }                 
                }
            }
        }
    }
    //-------------------- END processing X

    // Sum surrounding pressure value for each category
    for (const auto &coord : xCoordinates) 
    {
        for (const auto &p : pressure) 
        {
            if (p.x == coord.x && p.y == coord.y) 
            {
                categorySums[coord.category] += p.cloud;
            }
        }
    }

    // Print the outerp sum for each category
    for (const auto &pair : categorySums) 
    {
        cout << "Category " << pair.first << ": " << pair.second << endl;
    }
}
