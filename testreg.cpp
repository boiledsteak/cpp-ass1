#include <iostream>
#include <vector>
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
struct SurroundData 
{
    int x;
    int y;
    int category;

    SurroundData(int x, int y, int category) : x(x), y(y), category(category) {}
};

void men7printer(vector<CityData> cities, vector<CloudData> clouds, vector<CloudData> pressure, int *xys) 
{
    int minX = xys[0];
    int maxX = xys[1];
    int minY = xys[2];
    int maxY = xys[3];

    // Vector to store coordinates of "X" along with city category
    vector<SurroundData> surrounds;

    // Dictionary to store surrounding and actual sum of cloud.cloud for each city
    unordered_map<int, int> outerpsums;
    unordered_map<int, int> innerpsums;

    //-------------------- START processing surrounding coords
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
                                innerpsums[city.category] += cloud.cloud;  // Sum cloud.cloud for inner regions
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
                        // Store coordinates of surrounding coords along with city category
                        surrounds.push_back(SurroundData(x, y, city.category));
                        surroundPrinted = true;
                        break;
                    }                 
                }
            }
        }
    }
    //-------------------- END processing of surrounding coords

    // Sum surrounding cloud.cloud value for each city
    for (const auto &coord : surrounds) 
    {
        for (const auto &c : clouds) 
        {
            if (c.x == coord.x && c.y == coord.y) 
            {
                outerpsums[coord.category] += c.cloud;  // Sum cloud.cloud for outer regions
            }
        }
    }

    // Print outerp sum for each city
    cout << "Outer Cloud Sum by Category:\n";
    for (const auto &op : outerpsums) 
