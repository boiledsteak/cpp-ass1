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
using namespace std;

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
        while (getline(confile, lp))
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

//display city map. Menu option 2
int men2(vector<string> fivelines)
{
    


    return 0;
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
                xys = xyer(xys, fivelines);
                cout << "000";
                //print the first line of #
                for (int i=0; i <= xys[1]+2; i++)
                {
                    cout << "#\t";
                }
                //TODO print the second line

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