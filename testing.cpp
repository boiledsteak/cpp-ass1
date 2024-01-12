#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

int main()
{
    cout << right << setw(3) << "A";
    cout << right << setw(3) << "A" ;
    cout << left << setw(3) << "B" ;
    cout << left << setw(3) << "A" <<"\n\n";

    return 0;
}