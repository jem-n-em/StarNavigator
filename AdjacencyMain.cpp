#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include<cmath>
#include<iomanip>
#include<algorithm>
#include<set>
#include<sstream>
#include<climits>
#include<list>
#include<fstream>
#include<float.h>
#include<queue>
#include<Windows.h>
#include<chrono>
using namespace std;

class Stars
{
private:
	int id;
	double x;
	double y;
	double z;
	double dist;
public:
	Stars(int id, double x, double y, double z, double dist);
	double getX();
	double getY();
	double getZ();
	double getDist();
	int getID();
};

Stars::Stars(int id, double x, double y, double z, double dist)
{
	this->id = id;
	this->x = x;
	this->y = y;
	this->z = z;
	this->dist = dist;
}

int Stars::getID()
{
	return id;
}

double Stars::getX()
{
	return x;
}

double Stars::getY()
{
	return y;
}

double Stars::getZ()
{
	return z;
}

double Stars::getDist()
{
	return dist;
}

class Graph
{
private:
	map<int, vector<pair<int,double>>>graph;	
	int numVertices;
public:
	
	void insertEdge(int from, int to, double weight);
	void printGraph();
	map<int, double> dijkstra(set<int> s,int src);
	vector<int> getAdjacent(int vertex);
	int getVertices();
};

void Graph::insertEdge(int from, int to, double weight)
{
	graph[from].push_back(make_pair(to, weight));
	if (graph.find(to) == graph.end())
	{
		graph[to] =
		{
		};
	}
	numVertices++;
	
}

int Graph::getVertices() {
	return numVertices;
}

vector<int> Graph::getAdjacent(int vertex) {
	vector<int> v;
	for (auto iter = graph[vertex].begin(); iter != graph[vertex].end(); ++iter) {
		v.push_back(iter->first);
	}
	sort(v.begin(), v.end());
	return v;
}

map<int, double> Graph::dijkstra(set<int> s, int src) {
	map<int, double> dist;
	auto it = s.begin();
	while (it != s.end()) {			
		dist[*it] = DBL_MAX;
		it++;
	}
	
	dist[src] = 0.0;

	priority_queue<pair<int, double>, vector<pair<int, double>>, greater<pair<int, double>>> pq;
	pq.push({ 0, src });

	while (!pq.empty()) {
		double u = pq.top().second;
		pq.pop();

		for (pair<int, double> x : graph[u]) {
			int v = x.first;
			double weight = x.second;

			if (dist[u] + weight < dist[v]) {
				dist[v] = double(dist[u]) + double(weight);
				pq.push({ dist[v], v });
			}
			
		}
		
	}
	return dist;
}

void Graph::printGraph() {
	int key = 0;
	for (auto it = graph.begin(); it != graph.end(); ++it)
	{
		if (it->second.size() > 0)
		{
			cout << it->first << "->";
			for (int j= 0; j < it->second.size(); j++)
			{
				key = j;
				if (j + 1 == it->second.size())
				{
					cout << it->second[j].first;
				}
				else
				{
					cout << it->second[j].first << " ";
				}
			}
			cout << "\n";
			if (graph.count(it->second[key].first) == 0)
			{
				cout << it->second[key].first << endl;
			}
		}
	}
}

double calcDistance(double x, double y, double z, double x2, double y2, double z2)
{
	double distance = 0.0;
	distance = sqrt(pow((x - x2), 2) + pow((y - y2), 2) + pow((z - z2), 2));
	return distance;
}

int calcOctant(double x, double y, double z) {
	if (x >= 0 && y >= 0 && z >= 0)
		return 1;

	else if (x < 0 && y >= 0 && z >= 0)
		return 2;

	else if (x < 0 && y < 0 && z >= 0)
		return 3;

	else if (x >= 0 && y < 0 && z >= 0)
		return 4;

	else if (x >= 0 && y >= 0 && z < 0)
		return 5;

	else if (x < 0 && y >= 0 && z < 0)
		return 6;

	else if (x < 0 && y < 0 && z < 0)
		return 7;

	else if (x >= 0 && y < 0 && z < 0)
		return 8;
}

int main()
{
	string file = "hygdata_v3.csv";
	set<int> vertices;
	int destID = 0;
	int octant = 0;
	int octcount = 0;
	double maxDist = 0.0;
	string line;
	Graph galaxy;
	cout << "Enter the ID of the star you would like to visit (1-119615): " << endl;
	cin >> destID;
	
	ifstream inFile(file);

	getline(inFile, line);
	getline(inFile, line);

	while (getline(inFile, line))
	{
		istringstream iss(line);
		string data;
		int id;
		double x, y, z;


		getline(iss, data, ',');
		id = stoi(data);

		getline(iss, data, ',');
		x = stod(data);

		getline(iss, data, ',');
		y = stod(data);

		getline(iss, data, ',');
		z = stod(data);

		if (id == destID) {
			octant = calcOctant(x, y, z);
			break;
		}	
	}
	inFile.close();
	double x1 = 57.735;
	double x2 = 115.47;
	double x3 = 173.205;
	double x4 = 230.94;
	double x5 = 288.675;
	double x6 = 346.41;
	double y1 = 57.735;
	double y2 = 115.47;
	double y3 = 173.205;
	double y4 = 230.94;
	double y5 = 288.675;
	double y6 = 346.41;
	double z1 = 57.735;
	double z2 = 115.47;
	double z3 = 173.205;
	double z4 = 230.94;
	double z5 = 288.675;
	double z6 = 346.41;
	if (octant == 1) {
		cout << "";
	}
	else if (octant == 2) {
		x1 = -x1;
		x2 = -x2;
		x3 = -x3;
		x4 = -x4;
		x5 = -x5;
		x6 = -x6;
	}
	else if (octant == 3) {
		x1 = -x1;
		x2 = -x2;
		x3 = -x3;
		x4 = -x4;
		x5 = -x5;
		x6 = -x6;
		y1 = -y1;
		y2 = -y2;
		y3 = -y3;
		y4 = -y4;
		y5 = -y5;
		y6 = -y6;
	}
	else if(octant == 4){
		y1 = -y1;
		y2 = -y2;
		y3 = -y3;
		y4 = -y4;
		y5 = -y5;
		y6 = -y6;
	}
	else if (octant == 5) {
		z1 = -z1;
		z2 = -z2;
		z3 = -z3;
		z4 = -z4;
		z5 = -z5;
		z6 = -z6;
	}
	else if (octant == 6) {		
		x1 = -x1;
		x2 = -x2;
		x3 = -x3;
		x4 = -x4;
		x5 = -x5;
		x6 = -x6;
		z1 = -z1;
		z2 = -z2;
		z3 = -z3;
		z4 = -z4;
		z5 = -z5;
		z6 = -z6;
	}
	else if (octant == 7) {
		x1 = -x1;
		x2 = -x2;
		x3 = -x3;
		x4 = -x4;
		x5 = -x5;
		x6 = -x6;
		y1 = -y1;
		y2 = -y2;
		y3 = -y3;
		y4 = -y4;
		y5 = -y5;
		y6 = -y6;
		z1 = -z1;
		z2 = -z2;
		z3 = -z3;
		z4 = -z4;
		z5 = -z5;
		z6 = -z6;
	}
	else{
		y1 = -y1;
		y2 = -y2;
		y3 = -y3;
		y4 = -y4;
		y5 = -y5;
		y6 = -y6;
		z1 = -z1;
		z2 = -z2;
		z3 = -z3;
		z4 = -z4;
		z5 = -z5;
		z6 = -z6;
	}
	Stars earth(0, 0.0, 0.0, 0.0, 0.0);
	Stars refuel1(999990, x1, y1, z1, 100.0);
	Stars refuel2(999991, x2, y2, z2, 200.0);
	Stars refuel3(999992, x3, y3, z3, 300.0);
	Stars refuel4(999993, x4, y4, z4, 400.0);
	Stars refuel5(999994, x5, y5, z5, 500.0);
	Stars refuel6(999995, x6, y6, z6, 600.0);
	vertices.insert(0);
	vertices.insert(999990);
	vertices.insert(999991);
	vertices.insert(999992);
	vertices.insert(999993);
	vertices.insert(999994);
	vertices.insert(999995);

	ifstream fileName(file);
	getline(fileName, line);
	getline(fileName, line);

	while (getline(fileName, line)) {
		istringstream iss(line);
		string data;
		int id;
		double x, y, z;

		getline(iss, data, ',');
		id = stoi(data);

		getline(iss, data, ',');
		x = stod(data);

		getline(iss, data, ',');
		y = stod(data);

		getline(iss, data, ',');
		z = stod(data);

		double dist = calcDistance(0.0, 0.0, 0.0, x, y, z);
		
		if (calcOctant(x, y, z) == octant) {
			if (dist > 0 && dist <= 100) {
				galaxy.insertEdge(earth.getID(), id, dist);
				galaxy.insertEdge(id, refuel1.getID(),calcDistance(x, y, z, refuel1.getX(), refuel1.getY(), refuel1.getZ()));
				vertices.insert(id);
			} 
			else if (dist > 100 && dist <= 200) {
				galaxy.insertEdge(refuel1.getID(), id, calcDistance(x, y, z, refuel1.getX(), refuel1.getY(), refuel1.getZ()));
				galaxy.insertEdge(id, refuel2.getID(), calcDistance(x, y, z, refuel2.getX(), refuel2.getY(), refuel2.getZ()));
				vertices.insert(id);
			}
			else if (dist > 200 && dist <= 300) {
				galaxy.insertEdge(refuel2.getID(), id, calcDistance(x, y, z, refuel2.getX(), refuel2.getY(), refuel2.getZ()));
				galaxy.insertEdge(id, refuel3.getID(), calcDistance(x, y, z, refuel3.getX(), refuel3.getY(), refuel3.getZ()));
				vertices.insert(id);
			}
			else if (dist > 300 && dist <= 400) {
				galaxy.insertEdge(refuel3.getID(), id, calcDistance(x, y, z, refuel3.getX(), refuel3.getY(), refuel3.getZ()));
				galaxy.insertEdge(id, refuel4.getID(), calcDistance(x, y, z, refuel4.getX(), refuel4.getY(), refuel4.getZ()));
				vertices.insert(id);
			}
			else if (dist > 400 && dist <= 500) {
				galaxy.insertEdge(refuel4.getID(), id, calcDistance(x, y, z, refuel4.getX(), refuel4.getY(), refuel4.getZ()));
				galaxy.insertEdge(id, refuel5.getID(), calcDistance(x, y, z, refuel5.getX(), refuel5.getX(), refuel5.getZ()));
				vertices.insert(id);
			} 
			else if (dist > 500 && dist <= 600) {
				galaxy.insertEdge(refuel5.getID(), id, calcDistance(x, y, z, refuel5.getX(), refuel5.getX(), refuel5.getZ()));
				galaxy.insertEdge(id, refuel6.getID(), calcDistance(x, y, z, refuel6.getX(), refuel6.getY(), refuel6.getZ()));
			}
		}
	}
	auto start = chrono::high_resolution_clock::now();
	map<int, double> mp = galaxy.dijkstra(vertices, 0);
	auto end = chrono::high_resolution_clock::now();
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
	double distTraveled = 0.0;
	distTraveled = mp[destID];

	cout << "Elapsed time in milliseconds: "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< "milliseconds" << endl;

	if (distTraveled == 0) {
		cout << "This star could not be reached because it is beyond the last refuel station" << endl;
	}
	else {
		cout << "TRIP SUMMARY:" << endl;
		cout << "We entered octant " << octant << endl;
		cout << "The shortest path to the Star " << destID << " from Earth is " << distTraveled << " light years!" << endl;
		cout << "Your Spaceship SS Dijkstra visited " << int(distTraveled / 100) << " refuel stations" << endl;
	}
	return 0;
}


	

