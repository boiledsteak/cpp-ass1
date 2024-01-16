/*============================

Timothy Mah C++ module assignment
2 Jan 2024

issues
regex may be system agnostic


=============================*/

#include <iostream>
#include <string>
#include <iomanip>
#include <ios>
#include <fstream>
#include <regex>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <unordered_map>

using namespace std;

// store structs all in one .h file . Rmb to use header guard
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

    surrounddata(int x, int y, int category) : x(x), y(y), category(category) {}
};

void men7printer(vector<CityData> cities, vector<CloudData> clouds, vector<CloudData> pressure, int *xys) 
{
    int minX = xys[0];
    int maxX = xys[1];
    int minY = xys[2];
    int maxY = xys[3];

    // Vector to store coordinates of "X" along with city category
    vector<surrounddata> surrounds;
    
    // experiment using map instead of unordered map
    // dictionary to store surrounding and actual sum of pressure for each city
    unordered_map<int, int> outerpsums; //default for city 2 is 314
    unordered_map<int, int> innerpsums; //default for city 2 is 163
    // dictionary to store surrounding and actual sum of cloud cover for each city
    unordered_map<int, int> outercsums; //default for city 2 is 459
    unordered_map<int, int> innercsums; //default for city 2 is 151
    // dictionary to store count of cities (no of coordinates each city uses)
    unordered_map<int, int> printedCounts;  
    


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
                                printedCounts[city.category]++;
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
                        surrounds.push_back(surrounddata(x, y, city.category));
                        printedCounts[city.category]++;
                        surroundPrinted = true;
                        break;
                    }                 
                }

                // if (!surroundPrinted)
                // {
                //     // Increment count of "printed" for coordinates surrounding each city
                //     for (auto &city : cities)
                //     {
                //         if (abs(city.x - x) <= 1 && abs(city.y - y) <= 1)
                //         {
                //             printedCounts[city.category]++;
                //         }
                //     }
                // }
            }
        }
    }
    //-------------------- END processing of surrounding coords

    // Sum surrounding pressure value for each city
    for (const auto &coord : surrounds) 
    {
        
        for (const auto &p : pressure) 
        {
            if (p.x == coord.x && p.y == coord.y) 
            {
                outerpsums[coord.category] += p.cloud;
            }
        }
        
        for (auto &c : clouds)
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
    cout << "Outer cloud cover by City number:\n";
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
    cout << "Inner cloud cover by City number:\n";
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

vector<CloudData> men3reader(string cloudfilename, int option)
{   
    string lp; //line pointer when reading file
    fstream cloudfile(cloudfilename,ios::in);
    
    if (cloudfile.is_open()) //could add more input validation
    {
        // create the struct
        vector<CloudData> clouds;
        //read line by line config file
        while (getline(cloudfile >> ws, lp))
        {
            if (lp.size() != 0)
            {
                // fill the struct
                clouds.emplace_back(lp);
            }
        }
        // fix cloud cover value to be single digit positive number
        for (auto &cloud : clouds) 
        {
            if (option ==4)
            {
                cloud.cloud = abs(cloud.cloud);
            }
            else if (option==3)
            {
                cloud.cloud = abs(cloud.cloud) / 10;
            }
            
        } 
        return clouds;
    }
}

void men3printer(vector<CloudData> clouds, int *xys, int option)
{
    int minX = xys[0];
    int maxX = xys[1];
    int minY = xys[2];
    int maxY = xys[3];

    string lmh; //for option 4
    
    // set the padding for x axis. Size changes dynamically
    // minimum value 3 to accommodate for 3 digit x and y axes values
    int spacingamt =3;
    char border = '#';

    // move y axis labels away from y axis labels. Don't change. For top border
    cout <<left << setw(spacingamt) << " " << setw(spacingamt) << border;
    // print the top border
    for (int i = minX; i <= maxX + 1; i++)
    {
        cout << left << setw(spacingamt) << border;
    }
    cout << "\n";
    // Print coordinates with y-axis labels
    for (int y = maxY; y >= minY; --y) 
    {
        // print the left border
        cout << left << setw(spacingamt) << y << border;

        for (int x = minX; x <= maxX; ++x) 
        {
            bool printed = false;
            
            for (auto &cloud : clouds) 
            {
                if (cloud.x == x && cloud.y == y) 
                {
                    if (option == 4)
                    {
                        // for option 4. range L
                        if (cloud.cloud >= 0 && cloud.cloud <= 35)
                        {
                            lmh = "L";
                        }
                        // for option 4. range M
                        else if (cloud.cloud >= 36 && cloud.cloud <= 65)
                        {
                            lmh = "M";
                        }
                        // for option 4. range H
                        else if (cloud.cloud >= 66 && cloud.cloud <= 100)
                        {
                            lmh = "H";
                        }
                        // print coordinates
                        cout << right << setw(spacingamt) << lmh;
                        printed = true;
                        break;
                    }

                    else if (option == 3)
                    {
                        // print coordinates
                        cout << right << setw(spacingamt) << cloud.cloud;
                        printed = true;
                        break;
                    }
                }
            }
            if (!printed) 
            {
                cout << setw(spacingamt) << " ";
            }
        }
        // print the right border
        cout <<right << setw(spacingamt)<< border;
        cout << "\n";
    }
    // move x axis labels away from y axis labels. Don't change
    cout <<left << setw(spacingamt) << " " << setw(spacingamt) << border;
    // print the bottom border
    for (int i = minX; i <= maxX + 1; i++)
    {
        cout << left << setw(spacingamt) << border;
    }
    cout << "\n";
    // move x axis lables away from y axis labels. Don't change
    cout << setw(spacingamt * 2) << " ";

    for (int x = minX; x <= maxX; ++x) 
    {
         // Print x-axis labels
        cout << left << setw(spacingamt) << x;
    }
    cout << "\n";
}

vector<CityData> men2reader(string cityfilename)
{   
    string lp; //line pointer when reading file
    fstream cityfile(cityfilename,ios::in);
    
    if (cityfile.is_open()) //could add more input validation
    {
        // create the struct
        vector<CityData> cities;
        //read line by line config file
        while (getline(cityfile >> ws, lp))
        {
            if (lp.size() != 0)
            {
                // fill the struct
                cities.emplace_back(lp);
            }
        }
        // fix category to be positive number
        for (auto &city : cities) 
        {
            city.category = abs(city.category);
            
        } 
        return cities;
    }
}

void men2printer(vector<CityData> cities, int *xys) 
{
    int minX = xys[0];
    int maxX = xys[1];
    int minY = xys[2];
    int maxY = xys[3];
    
    // set the padding for x axis. Size changes dynamically
    // minimum value 3 to accommodate for 3 digit x and y axes values
    int spacingamt = 3;
    char border = '#';

    // move y axis labels away from y axis labels. Don't change. For top border
    cout <<left << setw(spacingamt) << " " << setw(spacingamt) << border;
    // print the top border
    for (int i = minX; i <= maxX + 1; i++)
    {
        cout << left << setw(spacingamt) << border;
    }
    cout << "\n";
    // Print coordinates with y-axis labels
    for (int y = maxY; y >= minY; --y) 
    {
        // print the left border
        cout << left << setw(spacingamt) << y << border;

        for (int x = minX; x <= maxX; ++x) 
        {
            bool printed = false;
            
            for (auto &city : cities) 
            {
                if (city.x == x && city.y == y) 
                {
                    // print coordinates
                    cout << right << setw(spacingamt) << city.category;
                    printed = true;
                    break;
                }
            }
            if (!printed) 
            {
                cout << setw(spacingamt) << " ";
            }
        }
        // print the right border
        cout <<right << setw(spacingamt)<< border;
        cout << "\n";
    }
    // move x axis labels away from y axis labels. Don't change
    cout <<left << setw(spacingamt) << " " << setw(spacingamt) << border;
    // print the bottom border
    for (int i = minX; i <= maxX + 1; i++)
    {
        cout << left << setw(spacingamt) << border;
    }
    cout << "\n";
    // move x axis lables away from y axis labels. Don't change
    cout << setw(spacingamt * 2) << " ";

    for (int x = minX; x <= maxX; ++x) 
    {
         // Print x-axis labels
        cout << left << setw(spacingamt) << x;
    }
    cout << "\n";
}

//take in string and delimiter, return vector. From Mr Thien
vector<string> tokenizeString (string input, string delimiter)
{
	size_t pos = 0;
	string token;
	vector<string> result;

	while ((pos = input.find(delimiter)) != string::npos) 
	{
    	token = input.substr(0, pos);
    	result.push_back (token);
		input.erase(0, pos + delimiter.length());
	}

	result.push_back (input);

	return (result);
}

//stores upper and lower X and Y
int *xyer(int *xys, vector<string> fivelines)
{
    vector<string> tempx = tokenizeString(fivelines[0], "-");
    vector<string> tempy = tokenizeString(fivelines[1], "-");
    
    xys[0] = stoi(tempx[0]);
    xys[1] = stoi(tempx[1]);
    xys[2] = stoi(tempy[0]);
    xys[3] = stoi(tempy[1]);
           
    return xys;
}


//reads and process config file. Menu option 1
vector<string> men1(string confilename, vector<string> fivelines) 
{
    string lp; //line pointer when reading file
    fstream confile(confilename,ios::in);
    vector<string> tokenStringVectorX; //temp holds the GridX_IdxRange=0-8. [0] is GridX..., [1] is 0-8
    vector<string> tokenStringVectorY; //temp holds the GridY_IdxRange=0-8. [0] is GridY..., [1] is 0-8
    
    if (confile.is_open()) //could add more input validation
    {
        //read line by line config file
        while (getline(confile >> ws, lp))
        {
            // if not a comment, continue
            if (!regex_match(lp,regex("//(.*)")))
            {
                //look for GridX
                if (regex_match(lp,regex("Grid[X]_IdxRange(.*)")))
                {
                    tokenStringVectorX = tokenizeString(lp, "=");
                    fivelines.push_back(tokenStringVectorX[1]);
                }
                //look for GridY
                if (regex_match(lp,regex("Grid[Y]_IdxRange(.*)")))
                {
                    tokenStringVectorY = tokenizeString(lp, "=");
                    fivelines.push_back(tokenStringVectorY[1]);
                }
                //look for .txt file
                if (regex_match(lp,regex(".*txt$")))
                {
                    fivelines.push_back(lp);
                }
            }  
        }   
        confile.close();

        cout << "Reading in GridX_IdxRange:	" << fivelines[0] << "	...done!" << "\n";
        cout << "Reading in GridY_IdxRange:	" << fivelines[1] << "	...done!" << "\n";
        cout << "\n";
        cout << "Storing data from input files: \n";
        cout << left << setw(20) << fivelines[2] << "...done!" << "\n";
        cout << left << setw(20) << fivelines[3] << "...done!" << "\n";
        cout << left << setw(20) << fivelines[4] << "...done!" << "\n";
        cout << "\n";
        cout << "All records successfully stored! Going back to main menu...\n\n";

    }
    else
    {
        cout << "\nfile not found :( Please try again...\n\n";
    }

    return fivelines;
}

void menuprinter()
{
    cout << "\n\n\n";
    cout << "Student ID:"  << "\t10258663\n";
    cout << "Student name:"  << "\tTimothy Mah\n";
    cout << "------------------------------------------------------\n";
    cout << "Welcome to weather information processing system!\n\n";
    cout << "1)" << "\tRead in and process a config file\n";
    cout << "2)" << "\tDisplay city map\n";
    cout << "3)" << "\tDisplay cloud coverage (cloudiness index)\n";
    cout << "4)" << "\tDisplay cloud coverage (LMH symbols)\n";
    cout << "5)" << "\tDisplay atmospheric pressure map (pressure index)\n";
    cout << "6)" << "\tDisplay atmospheric pressure map (LMH symbols)\n";
    cout << "7)" << "\tShow weather forecast summary report\n";
    cout << "8)" << "\tExit\n";
    cout << "\n\nTell me what you want!\n\n";
}

// @@@@@@@@@@@@ 
// MAIN
// @@@@@@@@@@@@
int main()
{
    int progflow = 1;
    int menuchoice = 0;
    string goback="nothing";
    string gobackmsg = " complete!\n Press ENTER to go back to main menu...";
    string noconfigmsg = "config file not processed!\nGoing back to main menu...";
    
    vector<string> fivelines; //[0] is GridX, [1] is GridY, [2] is citylocation.txt, [3] is cloudcover.txt, [4] is pressure.txt
    // int lowerx, upperx, lowery, uppery; //0-8 for gridX and 0-8 for GridY
    int *xys = new int[3]; //[0] is lower X, [1] is upper X, [2] is lower Y, [3] is upper Y

    while (progflow == 1)
    {
        menuprinter();
        // Check if cin expects an integer
        while (!(cin >> menuchoice)) 
        {
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            cout << "Invalid input! Please try again...\n";
            menuprinter();
        }      
        
        if (menuchoice ==1)
        {
            cout << ">>>>>>>>>>>>\t"<< "Option\t" << menuchoice << "\t>>>>>>>>>>>>\n\n";
            string confilename;
            while (fivelines.empty())
            {
                cout << "Please enter config file name:";
                cin >> confilename;
                cout << "\n";
                fivelines = men1(confilename, fivelines);
            }
            cout << "\nMenu choice "<< menuchoice << " completed! Going back to main menu...\n";
        }

        else if (menuchoice ==2)
        {
            cout << ">>>>>>>>>>>>\t"<< "Option\t" << menuchoice << "\t>>>>>>>>>>>>\n\n";
            if (!fivelines.empty())
            {
                // get the GridX and GriY
                xys = xyer(xys, fivelines);
                
                // create the struct to hold citylocation.txt data
                vector<CityData> cities = men2reader(fivelines[2]);
                
                // print the grid
                men2printer(cities, xys);

			    cout << "\nMenu choice "<< menuchoice <<gobackmsg;
                cin.ignore();
                // Loop until the Enter key is pressed
                while (true) 
                {
                    char ch = cin.get(); // Get a character from input
                    if (ch == '\n') {
                        // Enter key pressed, break out of the loop
                        break;
                    }
                }
            }
            else
            {
                cout << noconfigmsg;
            }
        }

        else if (menuchoice==3)
        {
            cout << ">>>>>>>>>>>>\t"<< "Option\t" << menuchoice << "\t>>>>>>>>>>>>\n\n";
            if (!fivelines.empty())
            {
                // get the GridX and GriY
                xys = xyer(xys, fivelines);
                // create the struct to hold cloudcover.txt data
                vector<CloudData> clouds = men3reader(fivelines[3],3);
                
                // print the grid
                men3printer(clouds, xys, 3);

			    cout << "\nMenu choice "<< menuchoice <<gobackmsg;
                cin.ignore();
                // Loop until the Enter key is pressed
                while (true) 
                {
                    char ch = cin.get(); // Get a character from input
                    if (ch == '\n') {
                        // Enter key pressed, break out of the loop
                        break;
                    }
                }
            }
            else
            {
                cout << noconfigmsg;
            }
        }

        else if (menuchoice==4)
        {
            cout << ">>>>>>>>>>>>\t"<< "Option\t" << menuchoice << "\t>>>>>>>>>>>>\n\n";
            if (!fivelines.empty())
            {
                // get the GridX and GriY
                xys = xyer(xys, fivelines);
                // create the struct to hold cloudcover.txt data
                vector<CloudData> clouds = men3reader(fivelines[3],4);
                
                // print the grid in LMH
                men3printer(clouds, xys, 4);

			    cout << "\nMenu choice "<< menuchoice <<gobackmsg;
                cin.ignore();
                // Loop until the Enter key is pressed
                while (true) 
                {
                    char ch = cin.get(); // Get a character from input
                    if (ch == '\n') {
                        // Enter key pressed, break out of the loop
                        break;
                    }
                }
            }
            else
            {
                cout << noconfigmsg;
            }
        }

        else if (menuchoice==5)
        {
            cout << ">>>>>>>>>>>>\t"<< "Option\t" << menuchoice << "\t>>>>>>>>>>>>\n\n";
            if (!fivelines.empty())
            {
                // get the GridX and GriY
                xys = xyer(xys, fivelines);
                // create the struct to hold pressure.txt data
                vector<CloudData> pressure = men3reader(fivelines[4],3);
                
                // print the grid
                men3printer(pressure, xys, 3);

			    cout << "\nMenu choice "<< menuchoice <<gobackmsg;
                cin.ignore();
                // Loop until the Enter key is pressed
                while (true) 
                {
                    char ch = cin.get(); // Get a character from input
                    if (ch == '\n') {
                        // Enter key pressed, break out of the loop
                        break;
                    }
                }
            }
            else
            {
                cout << noconfigmsg;
            }
        }

        else if (menuchoice==6)
        {
            cout << ">>>>>>>>>>>>\t"<< "Option\t" << menuchoice << "\t>>>>>>>>>>>>\n\n";
            if (!fivelines.empty())
            {
                // get the GridX and GriY
                xys = xyer(xys, fivelines);
                // create the struct to hold pressure.txt data
                vector<CloudData> pressure = men3reader(fivelines[4],4);
                
                // print the grid in LMH
                men3printer(pressure, xys, 4);

			    cout << "\nMenu choice "<< menuchoice <<gobackmsg;
                cin.ignore();
                // Loop until the Enter key is pressed
                while (true) 
                {
                    char ch = cin.get(); // Get a character from input
                    if (ch == '\n') {
                        // Enter key pressed, break out of the loop
                        break;
                    }
                }
            }
            else
            {
                cout << noconfigmsg;
            }
        }

        else if (menuchoice==7)
        {
            cout << ">>>>>>>>>>>>\t"<< "Option\t" << menuchoice << "\t>>>>>>>>>>>>\n\n";
            if (!fivelines.empty())
            {
                // get the GridX and GriY
                xys = xyer(xys, fivelines);
                // create the struct to hold citylocation.txt data
                vector<CityData> cities = men2reader(fivelines[2]);
                // create the struct to hold cloudcover.txt data
                vector<CloudData> clouds = men3reader(fivelines[3],4);
				// create the struct to hold pressure.txt data
                vector<CloudData> pressure = men3reader(fivelines[4],4);
                
                // print the grid
                men7printer(cities, clouds, pressure, xys);

			    cout << "\nMenu choice "<< menuchoice <<gobackmsg;
                cin.ignore();
                // Loop until the Enter key is pressed
                while (true) 
                {
                    char ch = cin.get(); // Get a character from input
                    if (ch == '\n') {
                        // Enter key pressed, break out of the loop
                        break;
                    }
                }
            }
            else
            {
                cout << noconfigmsg;
            }
        }


		else if (menuchoice ==8)
		{
            delete xys;
			progflow = 0;
		}

        else
        {
            cout << "\nWe don't have that option :( Please try again...\n\n";
        }

        cout << "\n\n\n";

    }
    

    return 0;
}