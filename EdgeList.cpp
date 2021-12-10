#include <tuple>
#include <iostream>
#include <vector>
#include <stack>
#include<unordered_map>
#include <unordered_set>
#include <cfloat>
#include <queue>
#include <algorithm>
#include <functional>
#include "EdgeList.h"
using namespace std;

int star::getOctant() {
    bool xPos = x >= 0;
    bool yPos = y >= 0;
    bool zPos = z >= 0;
    if (xPos && yPos && zPos)
        return 1;
    else if (!xPos && yPos && zPos)
        return 2;
    else if (!xPos && !yPos && zPos)
        return 3;
    else if (xPos && !yPos && zPos)
        return 4;
    else if (xPos && yPos && !zPos)
        return 5;
    else if (!xPos && yPos && !zPos)
        return 6;
    else if (!(xPos || yPos || zPos))
        return 7;
    else if (xPos && !yPos && !zPos)
        return 8;
    else
        return -1;
}
void EdgeList::buildGraph(vector<star*>& storeStars, star* dest) {
    //load in octant
    for (star* s : storeStars) {
        if (s->octant == dest->octant) {
            star* newStar = s;
            stars.insert(newStar);
        }
    }
    stars.insert(earth);
    //load in refuel stations
    loadRefuelStations(dest->octant);
    for (star* s : stars) {
        //connect stars to respective fueling stations, fueling stations to stars, etc.
        if (s == earth || find(refuelStation.begin(), refuelStation.end(), s) != refuelStation.end())
            continue;
        if (getDistance(earth, s) > 0 && getDistance(earth, s) <= 100.0) {
            insertEdge(earth, s);
            insertEdge(s, refuelStation[0]);
        }
        else if (getDistance(earth, s) > 100.0 && getDistance(earth, s) <= 200.0) {
            insertEdge(refuelStation[0], s);
            insertEdge(s, refuelStation[1]);
        }
        else if (getDistance(earth, s) > 200.0 && getDistance(earth, s) <= 300.0) {
            insertEdge(refuelStation[1], s);
            insertEdge(s, refuelStation[2]);
        }
        else if (getDistance(earth, s) > 300.0 && getDistance(earth, s) <= 400.0) {
            insertEdge(refuelStation[2], s);
            insertEdge(s, refuelStation[3]);
        }
        else if (getDistance(earth, s) > 400.0 && getDistance(earth, s) <= 500.0) {
            insertEdge(refuelStation[3], s);
            insertEdge(s, refuelStation[4]);
        }
        else if (getDistance(earth, s) > 500.0 && getDistance(earth, s) <= 600.0) {
            insertEdge(refuelStation[4], s);
            insertEdge(s, refuelStation[5]);
        }
        else {  //stars are outside bounds of fueling stations
            if (getDistance(refuelStation[5], s) > MAX_DISTANCE) {
                continue;
            }
            else {
                insertEdge(refuelStation[5], s);
            }
        }  
    }
}
float EdgeList::Dijkstra(star* dest) {
    //all necessary data structures;
    unordered_set<star*> unvisited = stars;
    unordered_map<star*, float> paths;
    for (star* s : stars) {     //initialize predecessor and path columns
        paths[s] = FLT_MAX;
    }
    //priority queue to quickly extract min
    priority_queue<pair<float, star*>, vector<pair<float, star*>>, greater<pair<float, star*>>> minQueue;
    pair<float, star*> init(0.0, earth);
    paths[earth] = 0;
    minQueue.push(init);
    while (!minQueue.empty()) {
        //find minimum path among unvisited stars 
        pair<float, star*> top = minQueue.top();
        star* minStar = top.second;
        minQueue.pop();
        unvisited.erase(minStar);
        //relax minStar's adjacents
        vector<tuple<star*, star*, float>> adjacents = getAdjacents(minStar);
        for (tuple<star*, star*, float> edge : adjacents) {
            star* curStar = get<1>(edge);
            if (paths[minStar] + get<2>(edge) < paths[curStar]) {
                paths[curStar] = paths[minStar] + get<2>(edge);
                pair<float, star*> relaxEdge(paths[curStar], curStar);
                minQueue.push(relaxEdge);
            }
        }
        unvisited.erase(minStar);
    }
    float distance = paths[dest];
    return distance;
}
vector<tuple<star*, star*, float>> EdgeList::getAdjacents(star* source) {
    vector<tuple<star*, star*, float>> adjacents;
    for (tuple<star*, star*, float> edge: edges) {
        if (get<0>(edge) == source) {
            adjacents.push_back(edge);
        }
    }
    return adjacents;
}
void EdgeList::insertEdge(star* from, star* to) {
    tuple<star*, star*, float>edge(from, to, getDistance(from, to));
    edges.push_back(edge);
}
void EdgeList::loadRefuelStations(int octant) {
    //x,y,z coords that bring refuel stations to as close to an isometric angle as possible
    float iso1 = 57.735f;
    float iso2 = 115.47f;
    float iso3 = 173.205f;
    float iso4 = 230.94f;
    float iso5 = 288.675f;
    float iso6 = 346.41f;
    switch (octant) {
    case 1://+++
        refuelStation.push_back(new star(200000, iso1, iso1, iso1));
        refuelStation.push_back(new star(200001, iso2, iso2, iso2));
        refuelStation.push_back(new star(200002, iso3, iso3, iso3));
        refuelStation.push_back(new star(200003, iso4, iso4, iso4));
        refuelStation.push_back(new star(200004, iso5, iso5, iso5));
        refuelStation.push_back(new star(200005, iso6, iso6, iso6));
        break;
    case 2://-++
        refuelStation.push_back(new star(200000, iso1 * -1, iso1, iso1));
        refuelStation.push_back(new star(200001, iso2 * -1, iso2, iso2));
        refuelStation.push_back(new star(200002, iso3 * -1, iso3, iso3));
        refuelStation.push_back(new star(200003, iso4 * -1, iso4, iso4));
        refuelStation.push_back(new star(200004, iso5 * -1, iso5, iso5));
        refuelStation.push_back(new star(200005, iso6 * -1, iso6, iso6));
        break;
    case 3://--+
        refuelStation.push_back(new star(200000, iso1 * -1, iso1 * -1, iso1));
        refuelStation.push_back(new star(200001, iso2 * -1, iso2 * -1, iso2));
        refuelStation.push_back(new star(200002, iso3 * -1, iso3 * -1, iso3));
        refuelStation.push_back(new star(200003, iso4 * -1, iso4 * -1, iso4));
        refuelStation.push_back(new star(200004, iso5 * -1, iso5 * -1, iso5));
        refuelStation.push_back(new star(200005, iso6 * -1, iso6 * -1, iso6));
        break;
    case 4://+-+
        refuelStation.push_back(new star(200000, iso1, iso1 * -1, iso1));
        refuelStation.push_back(new star(200001, iso2, iso2 * -1, iso2));
        refuelStation.push_back(new star(200002, iso3, iso3 * -1, iso3));
        refuelStation.push_back(new star(200003, iso4, iso4 * -1, iso4));
        refuelStation.push_back(new star(200004, iso5, iso5 * -1, iso5));
        refuelStation.push_back(new star(200005, iso6, iso6 * -1, iso6));
        break;
    case 5://++-
        refuelStation.push_back(new star(200000, iso1, iso1, iso1 * -1));
        refuelStation.push_back(new star(200001, iso2, iso2, iso2 * -1));
        refuelStation.push_back(new star(200002, iso3, iso3, iso3 * -1));
        refuelStation.push_back(new star(200003, iso4, iso4, iso4 * -1));
        refuelStation.push_back(new star(200004, iso5, iso5, iso5 * -1));
        refuelStation.push_back(new star(200005, iso6, iso6, iso6 * -1));
        break;
    case 6://-+-
        refuelStation.push_back(new star(200000, iso1 * -1, iso1, iso1 * -1));
        refuelStation.push_back(new star(200001, iso2 * -1, iso2, iso2 * -1));
        refuelStation.push_back(new star(200002, iso3 * -1, iso3, iso3 * -1));
        refuelStation.push_back(new star(200003, iso4 * -1, iso4, iso4 * -1));
        refuelStation.push_back(new star(200004, iso5 * -1, iso5, iso5 * -1));
        refuelStation.push_back(new star(200005, iso6 * -1, iso6, iso6 * -1));
        break;
    case 7://---
        refuelStation.push_back(new star(200000, iso1 * -1, iso1 * -1, iso1 * -1));
        refuelStation.push_back(new star(200001, iso2 * -1, iso2 * -1, iso2 * -1));
        refuelStation.push_back(new star(200002, iso3 * -1, iso3 * -1, iso3 * -1));
        refuelStation.push_back(new star(200003, iso4 * -1, iso4 * -1, iso4 * -1));
        refuelStation.push_back(new star(200004, iso5 * -1, iso5 * -1, iso5 * -1));
        refuelStation.push_back(new star(200005, iso6 * -1, iso6 * -1, iso6 * -1));
        break;
    case 8://+--
        refuelStation.push_back(new star(200000, iso1, iso1 * -1, iso1 * -1));
        refuelStation.push_back(new star(200001, iso2, iso2 * -1, iso2 * -1));
        refuelStation.push_back(new star(200002, iso3, iso3 * -1, iso3 * -1));
        refuelStation.push_back(new star(200003, iso4, iso4 * -1, iso4 * -1));
        refuelStation.push_back(new star(200004, iso5, iso5 * -1, iso5 * -1));
        refuelStation.push_back(new star(200005, iso6, iso6 * -1, iso6 * -1));
        break;
    default:
        refuelStation.push_back(new star(200000, iso1, iso1, iso1));
        refuelStation.push_back(new star(200001, iso2, iso2, iso2));
        refuelStation.push_back(new star(200002, iso3, iso3, iso3));
        refuelStation.push_back(new star(200003, iso4, iso4, iso4));
        refuelStation.push_back(new star(200004, iso5, iso5, iso5));
        refuelStation.push_back(new star(200005, iso6, iso6, iso6));
        break;
    }
    stars.insert(refuelStation[0]);
    stars.insert(refuelStation[1]);
    stars.insert(refuelStation[2]);
    stars.insert(refuelStation[3]);
    stars.insert(refuelStation[4]);
    stars.insert(refuelStation[5]);
}
float EdgeList::getDistance(star* start, star* end) {
    float xDist = pow(end->x - start->x, 2);
    float yDist = pow(end->y - start->y, 2);
    float zDist = pow(end->z - start->z, 2);
    float distance = sqrt(xDist + yDist + zDist);
    return distance;
}
