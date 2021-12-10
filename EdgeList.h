#pragma once
#include <tuple>
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <cfloat>
#include "Star.h"
using namespace std;
/*
    Declarations of star and EdgeList classes and their functions
    Author: Jerami Soriano
    Last updated: 12/9/2021
*/
class EdgeList {
private:
    const float MAX_DISTANCE = 100.0f;
    unordered_set<star*> stars;
    vector<tuple<star*, star*, float>> edges;   //vector of edges   {|| From || To || Weight ||}
    vector<star*> refuelStation;
public:
    star* earth = new star(-1, 0, 0, 0);  //Used as a "default star" in Dijkstra's algorithm
    void buildGraph(vector<star*>& storeStars, star* dest);
    void insertEdge(star* from, star* to);
    float Dijkstra(star* dest);
    void initDijkstra(unordered_map<star*, float>& paths, unordered_map<star*, star*>& predecessor);
    //vector<tuple<star*, star*, float>> getShortestPath();
    vector<tuple<star*, star*, float>> getAdjacents(star* source);
    float getDistance(star* start, star* end);
    void loadRefuelStations(int octant);
};
