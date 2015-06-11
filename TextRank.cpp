#include "stdafx.h"

using namespace std;

double const d = 0.85;
double const constValue = 1 - d;
double const errorRate = 0.00001;
vector<int> visited;

double vScore(int, Graph);

int main(int argc, char *argv[])
{
	//TextRank algorithm:
	//S(Vi) = (1 - d) + d* SUM j c In(Vi) [ 1/|Out(Vj)| * S(Vj) ]

	
	string fileName = argv[1];
	int windowSize = atoi(argv[2]);
	bool test = false;
	char controlChar;


		Graph testGraph;

		test = testGraph.createGraphFromFile(fileName + ".txt", windowSize);
		//testGraph.createGraphToFile(5, "graph.txt");
		//testGraph.readGraphFromFile("graph.txt");
		//testGraph.showGraph();

		vector<double> tmpScore;
		bool exit = false;
		int it = 0;
		do
		{
			it++;
			for (int i = 0; i < (int)testGraph.graph_set.size(); i++){
				testGraph.graph_set[i].score = vScore(i, testGraph);
				//cout << "Roz: " << std::fixed << std::setprecision(10) << abs(testGraph.graph_set[i].scorePrev - testGraph.graph_set[i].score) << endl;
				if (abs(testGraph.graph_set[i].score - testGraph.graph_set[i].scorePrev) < errorRate){
					exit = true;
					break;
				}

				testGraph.graph_set[i].scorePrev = testGraph.graph_set[i].score;
				visited.clear();
			}

			//cout << "++++++++++++++++++++++++++++++++" << endl;
		} while (!exit);

		for (int i = 0; i < (int)testGraph.graph_set.size(); i++)
		{
			for (int j = 0; j < (int)testGraph.graph_set.size() - 1; j++)
			{
				if (testGraph.graph_set[j].score < testGraph.graph_set[j + 1].score)
					swap(testGraph.graph_set[j], testGraph.graph_set[j + 1]);

			}
		}

		double srednia = 0;
		//double max_ten =  atof(argv[3]) * (int)testGraph.graph_set.size();

		for (int i = 0; i < (int)testGraph.graph_set.size(); i++){
			srednia = srednia + testGraph.graph_set[i].score;
		}
		
		srednia = srednia/(int)testGraph.graph_set.size(); 
		
		for (int i = 0; i < (int)testGraph.graph_set.size(); i++){
		//	if((srednia >= testGraph.graph_set[i].score ) || ((i+1) >= 10 ))
		//		break;
			cout << testGraph.graph_set[i].word << endl;			

		}

		//iny w Vi nie moga byc takie same jak outy w Vi+k
		//patrzymy na in np. IN(1): 3, 4
		//	-> lecimy do wierzcholka 3
		//	-> w wierzcholku 3 sprawdzamy czy w Out jest 1
		//		-> TAK: usuwamy
		//		-> NIE: wracamy do vectora IN(1), rozwazamy kolejny element, jesli koniec/pusty, przechodzimy do kolejnego wektora IN




	
	return 0;

	system("PAUSE");
}

double vScore(int nr, Graph testGraph){

	for (int &x : visited){
		if (x == nr) return testGraph.graph_set[nr].score;
	}
	
	visited.push_back(testGraph.graph_set[nr].id - 1);
	double sumVj = 0.0;

	for (int j = 0; j < (int) testGraph.graph_set[nr].inID.size(); j++){
		double tmp = (double)testGraph.graph_set[testGraph.graph_set[nr].inID[j] - 1].outID.size();
		sumVj = sumVj + (pow((tmp+1),-1.0)*vScore(testGraph.graph_set[testGraph.graph_set[nr].inID[j] - 1].id - 1, testGraph));
	}

	return constValue + (d * (sumVj));
}





