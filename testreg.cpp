#include <regex>
#include <iostream>
using namespace std;

int main()
{
    string lp = "hellorgegrg";

    if (regex_match(lp,regex("\\bhello\\b")))
    {
        cout << "\nheyyy it works\n";
    }
    else
    {
        cout << lp << "\n";
    }
}