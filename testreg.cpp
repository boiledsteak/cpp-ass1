// Set to keep track of processed city categories
unordered_set<int> processedCities;

// ...

// Print average cloud cover for each city
cout << "Average Cloud Cover for each city:\n";
for (const auto &ac : avgc) 
{
    // Check if the city category has already been processed
    if (processedCities.find(ac.first) == processedCities.end()) 
    {
        cout << "City " << ac.first << ": " << fixed << setprecision(2) << ac.second << endl;
        processedCities.insert(ac.first);
    }
}

// ...

// Print report
for (auto &city : cities)
{
    // Check if the city category has already been processed
    if (processedCities.find(city.category) == processedCities.end()) 
    {
        cout << setw(15) << "City name: " << ": " << city.cityName << "\n";
        cout << setw(15) << "City ID: " << ": " << city.category << "\n";
        cout << setw(18) << "Avg cloud cover "<< left << setw(7) << "(ACC)" <<": " << fixed << setprecision(2) << avgc[city.category] << " " << lmher(avgc[city.category]) << "\n\n";
        processedCities.insert(city.category);
    }
}
