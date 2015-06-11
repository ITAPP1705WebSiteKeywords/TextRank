#pragma once
using namespace std;

class Graph
{
public:
	int size = 0;

private:
	
	struct vertice{
		int id = -1;
		double score = 1.0;
		double scorePrev = 0.0;
		vector<int> inID;
		vector<int> outID;
	};

	vector<vector<int>> globalSetIn;
	vector<vector<int>> globalSetOut;
public:

	struct wordsVert{
		int id = -1;
		double score = 1.0;
		double scorePrev = 0.0;
		bool child = false;
		string word;
		vector<int> inID;
		vector<int> outID;
		wordsVert * ptrToParent;
	};

	vector<vertice> graph_set_random;
	vector<wordsVert> graph_set;

	Graph();
	void readGraphFromFile(string);
	void createGraphToFile(int, string);
	bool createGraphFromFile(string,int);
	vector<int> deleteLoops(vector<int>);
	void showGraph();
	virtual ~Graph();
};

