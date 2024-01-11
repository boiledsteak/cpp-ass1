/*============================

Timothy Mah C++ module assignment
2 Jan 2024

references
https://www.tutorialspoint.com/how-to-read-a-text-file-with-cplusplus
https://stackoverflow.com/questions/28338775/what-is-iosiniosout
https://www.softwaretestinghelp.com/regex-in-cpp/
possible extra feature
https://github.com/reo7sp/tgbot-cpp

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

using namespace std;

//TODO  figure out how to make CityData.categories to hold all categories
// Define a struct to hold city data
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
        return cities;
    }
}

void men2printer(const vector<vector<int>> &coordinates) 
{
    int maxX = 16;
    int maxY = 16;
    // set the padding for x axis. Size changes dynamically
    // minimum value 3 to accommodate for 3 digit x and y axes values
    int spacingamt = 3;
    string border = "#";
    // Print coordinates with y-axis labels
    for (int y = maxY; y >= 0; --y) 
    {
        // print the left #
        cout << left << setw(spacingamt) << y << border;

        for (int x = 0; x <= maxX; ++x) 
        {
            // print the empty spaces
            cout << left << setw(spacingamt) << " ";

            for (const auto& coord : coordinates) 
            {
                if (coord[0] == x && coord[1] == y) 
                {
                    // print coordinates
                    cout << left << setw(spacingamt) << "X";
                }
            }
        }
        // cout << border; //this prints right side border but its senget due to logic error. I gave up
        cout << "\n";
    }
     // move x axis labels away from y axis labels. Don't change
    cout << setw(spacingamt) << " " << setw(spacingamt) << border << setw(border.length()) << " ";
    // print the bottom #
    for (int i = 0; i <= maxX + 1; i++)
    {
        cout << left << setw(spacingamt) << border;
    }
    cout << "\n";
    // move x axis lables away from y axis labels. Don't change
    cout << setw((spacingamt * 2) + border.length()) << " ";

    for (int x = 0; x <= maxX; ++x) 
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
        cout << "\nfile not found";
    }

    return fivelines;
}

// @@@@@@@@@@@@ 
// MAIN
// @@@@@@@@@@@@
int main()
{
    int progflow = 1;
    int menuchoice = 0;
    
    
    vector<string> fivelines; //[0] is GridX, [1] is GridY, [2] is citylocation.txt, [3] is cloudcover.txt, [4] is pressure.txt
    // int lowerx, upperx, lowery, uppery; //0-8 for gridX and 0-8 for GridY
    int *xys = new int[3]; //[0] is lower X, [1] is upper X, [2] is lower Y, [3] is upper Y

    while (progflow == 1)
    {
        cout << "\n\n\n";
        cout << "Student ID:"  << "\t10258663\n";
        cout << "Student name:"  << "\tTimothy Mah\n";
        cout << "------------------------------------------------------\n";
        cout << "Welcome to weather information processing system!\n\n";
        cout << "1)" << "\tRead in and process a config file\n";
		cout << "2)" << "\tDisplay city map\n";
		cout << "8)" << "\tExit\n";
        cout << "\n\nTell me what you want!\n\n";
        cin >> menuchoice;
        cout << ">>>>>>>>>>>>\t"<< "Option\t" << menuchoice << "\t>>>>>>>>>>>>\n\n";

        if (menuchoice ==1)
        {
            string confilename;
            
            cout << "Please enter config file name:";
            cin >> confilename;
			cout << "\n";

            fivelines = men1(confilename, fivelines);
        }

        if (menuchoice ==2)
        {
            if (!fivelines.empty())
            {
                // get the GridX and GriY
                xys = xyer(xys, fivelines);
                // create the struct to hold citylocation.txt data
                vector<CityData> cities = men2reader(fivelines[2]);
                // hold all the coordinates in vector
                vector<vector<int>> coordinates;
     
                cout << "\nthis is the cities vector size->\t" << cities.size() << "\n";
                //fill the coordinates vector with coordinates from the cities struct vector
                for (auto &city : cities) 
                {
                    city.category = abs(city.category);
                    coordinates.push_back({city.x,city.y});
                }                                                                    
                int test = coordinates.size();

                                // print the grid
                men2printer(coordinates);
                // //print the first line of #
                // for (int i=0; i <= xys[1]+2; i++)
                // {
                //     cout << "#\t";
                // }
                // //TODO print the second line

			    cout << "\nMenu choice 2 complete!\nGoing back to main menu...";
            }
            else
            {
                cout << "config file not processed!\nGoing back to main menu...";
            }

            
        }

		if (menuchoice ==8)
		{
            delete xys;
			progflow = 0;
		}

        cout << "\n\n\n";

    }
    

    return 0;
}