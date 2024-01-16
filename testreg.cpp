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

    // Dictionaries to store surrounding and actual sum of pressure/cloud cover for each city
    unordered_map<int, int> outerpsums;  // default for city 2 is 314
    unordered_map<int, int> innerpsums;  // default for city 2 is 163
    unordered_map<int, int> outercsums;  // default for city 2 is 459
    unordered_map<int, int> innercsums;  // default for city 2 is 151
    unordered_map<int, int> printedCounts;  // to store the count of "printed" for each city category

    //-------------------- START processing surrounding coords
    for (int y = maxY; y >= minY; --y) 
    {
        for (int x = minX; x <= maxX; ++x) 
        {
            bool printed = false;
            for (auto &city : cities)
            {
                for (auto &c : clouds)
                {
                    if (city.x == x && city.y == y && city.x == c.x && city.y == c.y) 
                    {
                        for (auto &p : pressure)
                        {
                            if (p.x == x && p.y == y)
                            {
                                innerpsums[city.category] += p.cloud;
                                innercsums[city.category] += c.cloud;
                                printedCounts[city.category]++;  // Increment count of "printed"
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

                if (!surroundPrinted)
                {
                    // Increment count of "printed" for each city category
                    for (auto &city : cities)
                    {
                        if (abs(city.x - x) <= 1 && abs(city.y - y) <= 1)
                        {
                            printedCounts[city.category]++;
                        }
                    }
                }
            }
        }
    }
    //-------------------- END processing of surrounding coords

    // Sum surrounding pressure/cloud cover value for each city
    for (const auto &coord : surrounds) 
    {
        for (const auto &p : pressure) 
        {
            if (p.x == coord.x && p.y == coord.y) 
            {
                outerpsums[coord.category] += p.cloud;
            }
        }

        for (const auto &c : clouds)
        {
            if (c.x == coord.x && c.y == coord.y)
            {
                outercsums[coord.category] += c.cloud;
            }
        }
    }

    // Print outerp sum for each city
    cout << "Outer Pressure by City number:\n";
    for (const auto &op : outerpsums) 
    {
        cout << "City " << op.first << ": " << op.second << endl;
    }
    // Print outerc sum for each city
    cout << "Outer Cloud Cover by City number:\n";
    for (const auto &oc : outercsums) 
    {
        cout << "City " << oc.first << ": " << oc.second << endl;
    }
    // Print innerp sum for each city
    cout << "Inner Pressure by City number:\n";
    for (const auto &ip : innerpsums) 
    {
        cout << "City " << ip.first << ": " << ip.second << endl;
    }
    // Print innerc sum for each city
    cout << "Inner Cloud Cover by City number:\n";
    for (const auto &ic : innercsums) 
    {
        cout << "City " << ic.first << ": " << ic.second << endl;
    }
    // Print count of "printed" for each city
    cout << "Count of 'printed' for each City number:\n";
    for (const auto &count : printedCounts) 
    {
        cout << "City " << count.first << ": " << count.second << endl;
    }
}
