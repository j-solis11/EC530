#include <iostream>
#include <stdio.h>
#include <string>
#include <exception>
#include <vector>
#include <cmath>
#include <climits>
#include <fstream>
#include <sstream>

using namespace std;

#define ENABLE_UNIT_TEST_A

// Checking between two known locations and one starting
// What is closer to New York, Point 1 in Vector 2 is London and Point 2 in Vector 2 is Paris
// Answer should be Point 1
void UnitTestA(const string& filename)
{
    cout << "UNIT TEST 1 BEGIN" << endl;
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "ERROR: Cannot open file for unit test." << endl;
    }
    file << "firstLatitudes,firstLongitudes,secondLatitudes,secondLongitudes" << endl;
    file << 40.7128 << "," << 74.006 << "," << 51.5074 << "," << -0.1278 << endl;
    file << "," << "," << 35.6895 << "," << 139.6917 << endl;
    file.close();
    cout << "RESULT SHOULD BE 51.5074, 40.7128" << endl;
}

int main (int argc, char *argv[])
{
    vector<float> latitudeListOne, latitudeListTwo;
    vector<float> longitudeListOne, longitudeListTwo;
    int count = 0;
    int countTwo = 0;
    string filename = "data.csv";


    #ifdef ENABLE_UNIT_TEST_A
        UnitTestA(filename);
    #endif

    
    ifstream filePointer(filename);

    if (!filePointer)
    {
        cout << "ERROR: Cannot open file." << endl;
        return 0;
    }

    string line;
    getline(filePointer, line);     // getting header

    while (getline(filePointer, line))
    {
        stringstream ss(line);
        string latOne, lonOne, latTwo, lonTwo;
        getline(ss, latOne, ',');
        getline(ss, lonOne, ',');
        getline(ss, latTwo, ',');
        getline(ss, lonTwo, ',');
        cout << latOne << " " << lonOne << " " << latTwo << " " << lonTwo << endl;
        if (!latOne.empty())
        {
            float latOneFloat;
            try
            {
                latOneFloat = stof(latOne);
            }
            catch(const exception& e)
            {
                
            }
            
            latitudeListOne.push_back(latOneFloat);
            count++;
        }

        if (!lonOne.empty())
        {
            float lonOneFloat;
            try
            {
                lonOneFloat = stof(lonOne);
            }
            catch(const exception& e)
            {
                
            }
            longitudeListOne.push_back(lonOneFloat);
        }

        if (!latTwo.empty())
        {
            float latTwoFloat;
            try
            {
                latTwoFloat = stof(latTwo);
            }
            catch(const exception& e)
            {
                
            }
            latitudeListTwo.push_back(latTwoFloat);
            countTwo++;
        }

        if (!lonTwo.empty())
        {
            float lonTwoFloat;
            try
            {
                lonTwoFloat = stof(latOne);
            }
            catch(const exception& e)
            {
                
            }
            longitudeListTwo.push_back(lonTwoFloat);
        }
        
        
    }

    filePointer.close();    // Closing file

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
