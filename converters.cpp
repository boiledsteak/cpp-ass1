#include "converters.h"

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

// use tokenizeString to return min max X Y
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

//convert amount to LMH
string lmher(int amount)
{
    string lmh;
    // range L
    if (amount >= 0 && amount <= 35)
    {
        lmh = "L";
    }
    // ange M
    else if (amount >= 36 && amount <= 65)
    {
        lmh = "M";
    }
    // range H
    else if (amount >= 66 && amount <= 100)
    {
        lmh = "H";
    }
    return lmh;
}

// compute rain probability
int rainer(string ap, string acc)
{
    int rainchance;

    if (ap == "L" && acc == "H")
    {
        rainchance = 90;
    }
    else if (ap == "L" && acc == "M")
    {
        rainchance = 80;
    }
    else if (ap == "L" && acc == "L")
    {
        rainchance = 70;
    }
    else if (ap == "M" && acc == "H")
    {
        rainchance = 60;
    }
    else if (ap == "M" && acc == "M")
    {
        rainchance = 50;
    }
    else if (ap == "M" && acc == "L")
    {
        rainchance = 40;
    }
    else if (ap == "H" && acc == "H")
    {
        rainchance = 30;
    }
    else if (ap == "H" && acc == "M")
    {
        rainchance = 20;
    }
    else if (ap == "H" && acc == "L")
    {
        rainchance = 10;
    }
    else
    {
        // Default case if none of the above conditions are met
        rainchance = 0;
    }

    return rainchance;
}