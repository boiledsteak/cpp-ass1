void men7printer(vector<CityData> cities, vector<CloudData> clouds, vector<CloudData> pressure, int *xys) 
{
    int minX = xys[0];
    int maxX = xys[1];
    int minY = xys[2];
    int maxY = xys[3];
    
    int spacingamt = 3;
    string border = "#";

    cout << left << setw(spacingamt) << " " << setw(spacingamt) << border;
    for (int i = minX; i <= maxX + 1; i++)
    {
        cout << left << setw(spacingamt) << border;
    }
    cout << "\n";

    for (int y = maxY; y >= minY; --y) 
    {
        cout << left << setw(spacingamt) << y << border;

        for (int x = minX + 1; x <= maxX; ++x) 
        {
            bool printed = false;
            
            for (auto &city : cities)
            {
                for (auto &cloud : clouds)
                {
                    if (city.x == x && city.y == y && city.x == cloud.x && city.y == cloud.y) 
                    {
                        // Check for matching pressure value
                        for (auto &p : pressure)
                        {
                            if (p.x == x && p.y == y)
                            {
                                cout << right << setw(spacingamt) << p.cloud;
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
                        cout << right << setw(spacingamt) << "X";
                        surroundPrinted = true;
                        break;
                    }  
                }

                if (!surroundPrinted) 
                {
                    cout << setw(spacingamt) << " ";
                }
            }
        }

        cout << right << setw(spacingamt * 2) << border;
        cout << "\n";
    }

    cout << left << setw(spacingamt) << " " << setw(spacingamt) << border;
    for (int i = minX; i <= maxX + 1; i++)
    {
        cout << left << setw(spacingamt) << border;
    }
    cout << "\n";

    cout << setw(spacingamt * 2) << " ";
    for (int x = minX; x <= maxX; ++x) 
    {
        cout << left << setw(spacingamt) << x;
    }
    cout << "\n";
}
