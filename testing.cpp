#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

using namespace std;

// Define a struct to represent the data
struct CityData {
    int x;
    int y;
    int category;
    string cityName;

    // Constructor to initialize the struct using a string
    CityData(const string& str) {
        // Use stringstream to split the string into components
        stringstream ss(str);
        char discard; // to discard '[' and ','
        ss >> discard >> x >> discard >> y >> discard >> category >> discard >> cityName;
    }
};

// Function to read data and populate structs
vector<CityData> readCityData() {
    // Provided data as a vector of strings
    vector<string> raw_data = {
        "[1, 1]-3-Big_City",
        "[1, 2]-3-Big_City",
        "[1, 3]-3-Big_City",
        "[2, 1]-3-Big_City",
        "[2, 2]-3-Big_City",
        "[2, 3]-3-Big_City",
        "[2, 7]-2-Mid_City",
        "[2, 8]-2-Mid_City",
        "[3, 1]-3-Big_City",
        "[3, 2]-3-Big_City",
        "[3, 3]-3-Big_City",
        "[3, 7]-2-Mid_City",
        "[3, 8]-2-Mid_City",
        "[7, 7]-1-Small_City"
    };

    // Populate structs
    vector<CityData> cityDataList;
    for (auto& data : raw_data) {
        cityDataList.emplace_back(data);
    }

    return cityDataList;
}

int main() {
    // Call the function to read data and populate structs
    vector<CityData> cities = readCityData();

    // Display the populated structs
    for (auto &city : cities) {
        city.category = abs(city.category);
        cout << "this is city x->\t" << city.x << "\n";
        cout << "this is city y->\t" << city.y << "\n";
        cout << "this is city cat->\t" << city.category << "\n";
        cout << "this is city name->\t" << city.cityName << "\n";
        cout << "-----------------\n";
    }

    return 0;
}
