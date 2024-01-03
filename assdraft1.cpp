/*============================

Timothy Mah C++ module assignment
2 Jan 2024

references
https://www.tutorialspoint.com/how-to-read-a-text-file-with-cplusplus
https://stackoverflow.com/questions/28338775/what-is-iosiniosout
possible extra feature
https://github.com/reo7sp/tgbot-cpp


=============================*/

#include <iostream>
#include <string>
#include <iomanip>
#include <ios>
#include <fstream>
using namespace std;

int men1(string confilename) //reads and process config file
{
    string lp; //line pointer when reading file
    fstream confile(confilename,ios::in); //why must put the ios
    if (confile.is_open())
    {
        while(getline(confile, lp))
        {
            cout << lp << "\n";
        }
        confile.close();
    }
    else
    {
        cout << "\nfile not found";
    }

    return 0;
}

int main()
{
    int progflow = 1;
    int menuchoice = 0;
    while (progflow == 1)
    {
        cout << "\n\n\n";
        cout << "Student ID:"  << "\t10258663\n";
        cout << "Student name:"  << "\tTimothy Mah\n";
        cout << "------------------------------------------------------\n";
        cout << "Welcome to weather information processing system!\n\n";
        cout << "1)" << "\tRead in and process a config file\n";
        cout << "\n\nTell me what you want!\n\n";
        cin >> menuchoice;
        cout << ">>>>>>>>>>>>\t"<< "Option\t" << menuchoice << "\t>>>>>>>>>>>>\n\n";

        if (menuchoice ==1)
        {
            string confilename;
            
            cout << "Please enter config file name:";
            cin >> confilename;

            men1(confilename);
        }
        

        cout << "\n\n\n";

        

        progflow = 0;
    }
    

    return 0;
}