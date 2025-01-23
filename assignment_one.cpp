#include <iostream>
#include <stdio.h>
#include <string>
#include <exception>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

int main (int argc, char *argv[])
{
    string input;
    float tempFloat;
    float longitude;
    int count = 0;
    int countTwo = 0;
    vector<float> latitudeListOne, latitudeListTwo;
    vector<float> longitudeListOne, longitudeListTwo;

    cout << "Please enter latitudes for array 1. When finished, enter n. To quit, enter q:";
    
    while (true)
    {
        cin >> input;
        if (input == "n")
        {
            break;
        }
        else if (input == "q")
        {
            return 0;
        }
        try
        {
            tempFloat = stof(input);
            count += 1;
            latitudeListOne.push_back(tempFloat);
        }
        catch (const invalid_argument& e)
        {
            cout << "Please enter a valid latitude (float)." << endl;
        }
    }

    cout << "Please enter " << count << " longitudes for array 1. To quit, enter q:";
    
    int newCount = 0;
    while (newCount != count)
    {
        cin >> input;
        if (input == "q")
        {
            return 0;
        }
        try
        {
            tempFloat = stof(input);
            newCount++;
            longitudeListOne.push_back(tempFloat);
        }
        catch (const invalid_argument& e)
        {
            cout << "Please enter a valid longitude (float)." << endl;
        }
    }

    cout << "Please enter latitudes for array 2. When finished, enter n. To quit, enter q:";
    newCount = 0;
    while (true)
    {
        cin >> input;
        if (input == "n")
        {
            break;
        }
        else if (input == "q")
        {
            return 0;
        }
        try
        {
            tempFloat = stof(input);
            countTwo += 1;
            latitudeListTwo.push_back(tempFloat);
        }
        catch (const invalid_argument& e)
        {
            cout << "Please enter a valid latitude (float)." << endl;
        }
    }

    cout << "Please enter " << count << " longitudes for array 2. To quit, enter q:";
    
    newCount = 0;
    while (newCount != countTwo)
    {
        cin >> input;
        if (input == "q")
        {
            return 0;
        }
        try
        {
            tempFloat = stof(input);
            newCount++;
            longitudeListTwo.push_back(tempFloat);
        }
        catch (const invalid_argument& e)
        {
            cout << "Please enter a valid longitude (float)." << endl;
        }
    }

    cout << "Array 1: " << endl;
    for (int i = 0; i < count ; i++)
    {
        cout << "Point " << i + 1 << ": "<< latitudeListOne[i] << " " << longitudeListOne[i] << endl;
    }
    cout << endl;

    cout << "Array 2: " << endl;
    for (int i = 0; i < countTwo ; i++)
    {
        cout << "Point " << i + 1 << ": "<< latitudeListTwo[i] << " " << longitudeListTwo[i] << endl;
    }
    cout << endl;

    // Calculating the distance between points
    int R = 6371;   // km (radius of Earth)
    vector<int> closestIndexes;
    vector<int> closestDistances;
    for (int i = 0; i < count; i++)
    {
        closestIndexes.push_back(INT_MAX);
        closestDistances.push_back(INT_MAX);
    }

    float latitudeOne, latitudeTwo;
    float longitudeOne, longitudeTwo;
    float deltaLatitude;
    float deltaLongitude;
    double tempNum;
    double tempDistance;
    for (int i = 0; i < count; i++)
    {
        latitudeOne = latitudeListOne[i] * (3.14 / 180.0);
        longitudeOne = longitudeListOne[i]* (3.14 / 180.0);
        for (int j = 0; j < countTwo; j++)
        {
            latitudeTwo = latitudeListTwo[j]* (3.14 / 180.0);
            longitudeTwo = longitudeListTwo[j]* (3.14 / 180.0);
            deltaLatitude = latitudeTwo - latitudeOne;
            deltaLongitude = longitudeTwo - longitudeOne;

            tempNum = (sin(deltaLatitude / 2) * sin(deltaLatitude / 2)) + (cos(latitudeOne) * cos(latitudeTwo) * (sin(deltaLongitude / 2) * sin(deltaLongitude / 2)));
            tempDistance = 2 * R * atan2(sqrt(tempNum), sqrt(1 - tempNum));
            if (tempDistance < closestDistances[i])
            {
                closestDistances[i] = tempDistance;
                closestIndexes[i] = j;
            }
        }   
    }


    cout << "Closest Points in Arrays:" << endl;
    for (int i = 0; i < count ; i++)
    {
        cout << "Point " << i + 1 << ": "<< latitudeListOne[i] << " " << longitudeListOne[i] << endl;
        cout << "Closest Point: " << latitudeListTwo[closestIndexes[i]] << " " << longitudeListTwo[closestIndexes[i]] << endl;
        cout << "Distance Between Points: " << closestDistances[i] << " km" << endl;
    }

    return 0;
}
