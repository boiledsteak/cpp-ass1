#ifndef CONSTRUCTORS_H
#define CONSTRUCTORS_H
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct CityData 
{
    int x;
    int y;
    int category;
    string cityName;

    // Constructor to initialize the struct
    CityData(string &str) 
    {
        // Use stringstream to split the string into components
        stringstream ss(str);
        char discard; // to discard '[' and ','
        ss >> discard >> x >> discard >> y >> discard >> category >> discard >> cityName;
    }
};

struct CloudData 
{
    int x;
    int y;
    int cloud;
   
    // Constructor to initialize the struct
    CloudData(string &strr) 
    {
        // Use stringstream to split the string into components
        stringstream sss(strr);
        char discard; // to discard '[' and ','
        sss >> discard >> x >> discard >> y >> discard >> cloud;
    }
};

// Struct to store coordinates and category
struct surrounddata 
{
    int x;
    int y;
    int category;
    
    // surrounddata(int x, int y, int category) : x(x), y(y), category(category) {}
    surrounddata(int X, int Y, int CATEGORY)
    {
        x=X;
        y=Y;
        category=CATEGORY;
    }
};


#endif