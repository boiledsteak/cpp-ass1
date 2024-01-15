#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

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

void men7printer(vector<CityData> cities, vector<CloudData> clouds, vector<CloudData> pressure, int *xys) 
{
    int minX = xys[0];
    int maxX = xys[1];
    int minY = xys[2];
    int maxY = xys[3];

    int spacingamt = 3;
    string border = "#";

    cout << left << setw(spacingamt) << " " << setw(spacingamt) << border;
    for (int i = minX; i <= maxX + 1; i++)
    {
        cout << left << setw(spacingamt) << border;
    }
    cout << "\n";

    // Vector to store coordinates of "X"
    vector<pair<int, int>> xCoordinates;

    for (int y = maxY; y >= minY; --y) 
    {
        cout << left << setw(spacingamt) << y << border;

        for (int x = minX + 1; x <= maxX + 1; ++x) 
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
                                cout << right << setw(spacingamt) << p.cloud;
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
                    if (abs(city.x - x) <= 1 && abs(city.y - y) <= 1) 
                    {
                        // Store coordinates of "X"
                        xCoordinates.push_back(make_pair(x, y));
                        cout << right << setw(spacingamt) << "X";
                        surroundPrinted = true;
                        break;
                    }
                }

                if (!surroundPrinted) 
                {
                    cout << setw(spacingamt) << " ";
                }
            }
        }

        cout << right << setw(spacingamt) << border;
        cout << "\n";
    }

    // Print pressure values based on coordinates in xCoordinates
    cout << "Pressure values at 'X' coordinates: ";
    for (const auto &coord : xCoordinates) 
    {
        for (const auto &p : pressure) 
        {
            if (p.x == coord.first && p.y == coord.second) 
            {
                cout << "(" << coord.first << "," << coord.second << "): " << p.cloud << " ";
            }
        }
    }
    cout << "\n";

    cout << left << setw(spacingamt) << " " << setw(spacingamt) << border;
    for (int i = minX; i <= maxX + 1; i++)
    {
        cout << left << setw(spacingamt) << border;
    }
    cout << "\n";

    cout << setw(spacingamt * 2) << " ";
    for (int x = minX; x <= maxX; ++x) 
    {
        cout << left << setw(spacingamt) << x;
    }
    cout << "\n";
}

int main() 
{
    // Sample usage of the men7printer function with data...
    return 0;
}
