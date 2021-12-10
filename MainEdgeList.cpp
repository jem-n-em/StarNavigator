#include <iostream>
#include <fstream>
#include<sstream>
#include <vector>
#include <set>
#include <cmath>
#include <chrono>
#include <Windows.h>
#include "EdgeList.h"
#include "Star.h"
using namespace std;
vector<star*> storeData(string filename, vector<star*> starVec) {
    ifstream data;
    data.open(filename);

    if (data.is_open()) {
        string line;
        getline(data, line);

        while (getline(data, line)) {
            string id;
            int ID;
            float X;
            float Y;
            float Z;
            string next;

            istringstream stream(line);

            getline(stream, id, ',');
            ID = stoi(id);
            getline(stream, next, ',');
            X = stof(next);
            getline(stream, next, ',');
            Y = stof(next);
            getline(stream, next, ',');
            Z = stof(next);

            star* newStar = new star(ID, X, Y, Z);
            starVec.push_back(newStar);
        }
    }
    else {
        cout << "file failed to open";
    }
    data.close();
    return starVec;
}
int main() {
    string file = "hygdata_v3.csv";
    //Tools for Edge list;
    vector<star*> storeStars;
    storeStars = storeData(file, storeStars);
    EdgeList edgeList;
    //Begin User Input
    int destinationID;
    cout << "Enter the ID of the star you would like to visit (1-119615): " << endl;
    cin >> destinationID;
    edgeList.buildGraph(storeStars, storeStars[destinationID]);
    //Begin Dijkstra's and timing simulation
    chrono::steady_clock::time_point time1 = chrono::steady_clock::now();
    float distance = edgeList.Dijkstra(storeStars[destinationID]);
    chrono::steady_clock::time_point time2 = chrono::steady_clock::now();
    chrono::duration<double> performance = chrono::duration_cast<chrono::duration<double>>(time2 - time1);
    /*========Fun Print Statement=========*/
    const char rocket[] =         //Image from https://helloacm.com/simple-cc-rocket-animation/
        "           _\n\
          /^\\\n\
          |-|\n\
          | |\n\
          |D|\n\
          |I|\n\
          |J|\n\
          |K|\n\
          |S|\n\
          |T|\n\
          |R|\n\
          |A|\n\
         /| |\\\n\
        / | | \\\n\
       |  | |  |\n\
        `-\"\"\"-`\n\
"; 
    for (int i = 0; i < 30; i++) {
        cout << "\n";
    }
    cout << ("%s", rocket);
    int j = 500;
    for (int i = 0; i < 50; i++) {
        Sleep(j);
        j = (int)(j * 0.9);
        cout << "\n";
    }
    /*========End Fun Print Statement========*/
    cout << "Dijkstra's Algorithm with an edge list takes " << performance.count() << " seconds." << endl;
    if (distance == FLT_MAX)
        cout << "This star could not be reached because it is beyond the last refuel station." << endl;
    else {
        cout  << "TRIP SUMMARY" << endl;
        cout << "We entered octant " << storeStars[destinationID]->octant << endl;
        cout  << "The shortest path to the Star " << destinationID << " from Earth is " << distance << " light years!" << endl;
        cout  << "Your Spaceship SS Dijkstra visited " << int(distance / 100) << " refuel stations" << endl;
    }
   

    return 0;
}
