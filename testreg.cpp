#include <regex>
#include <iostream>
#include <string>
using namespace std;

void printer(char c, int n)
{
    // character c will be printed n times
    cout << string(n, c) << endl;
}

int main()
{
    printer('#',9);
    cout << string(9, '#');
}