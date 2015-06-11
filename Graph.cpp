#include "stdafx.h"
#include "Graph.h"

using namespace std;

Graph::Graph() 
{
}

void Graph::createGraphToFile(int countVert, string fileName){
	ofstream oStream;
	time_t rawtime;
	srand(time(&rawtime));

	oStream.open(fileName, std::ifstream::out);

	if (oStream.is_open()){
		oStream << countVert << endl;
		for (int i = 0; i < countVert; i++){
			
			
			int edgeNumber = rand() % (4 - 1); // countVert - 1
			vector<int> tmp;
			tmp.push_back(i+1);

			while (edgeNumber){
				bool test = false;

				while (!test){
		
					
					int tmpVert = rand() % 3 + 1;// countVert + 1
					for (int &i : tmp){
						if (i == tmpVert){	
							test = true;
							break;
						}
					}

					if (!test) {
						tmp.push_back(tmpVert);								
						break;
					}
					else{
						test = false;
					}
				}
				
				edgeNumber--;
			}

			globalSetIn.push_back(tmp);

			edgeNumber = rand() % (4 - 1);
			vector<int> tmp1;
			tmp1.push_back(i + 1);

			while (edgeNumber){
				bool test = false;

				while (!test){


					int tmpVert = rand() % 3 + 1;
					for (int &i : tmp1){
						if (i == tmpVert){
							test = true;
							break;
						}
					}

					if (!test) {
						tmp1.push_back(tmpVert);
						break;
					}
					else{
						test = false;
					}
				}
				
				edgeNumber--;
			}

			globalSetOut.push_back(tmp1);
			
		}	//koniec glownego fora
	}
	else{
		cout << "brak pliku " << fileName << endl;
	}
	
	/*//USUWANIE Podwojnych krawedzi do tego samego wierzcholka
	for (int i = 0; i < globalSetIn.size(); i++){
		for (int j = 1; j < globalSetIn[i].size(); j++){	//pomijamy pierwszy el. - numer wierzcholka		
			for (int k = 1; k < globalSetOut[globalSetIn[i][j] - 1].size(); k++){
				if (globalSetOut[globalSetIn[i][j] - 1][k] == i + 1){			
					globalSetOut[globalSetIn[i][j] - 1][k] = 0;
				}		
			}
		}
	}*/


	//Zapis do pliku

	for (int i = 0; i < countVert; i++){
		oStream << "in:";
		for (int j = 1; j < globalSetIn[i].size(); j++){
			j + 1 == globalSetIn[i].size() ? oStream << globalSetIn[i][j] : oStream << globalSetIn[i][j] << "-";
		}
		oStream << " out:";
		for (int j = 1; j < globalSetOut[i].size(); j++){
			if (globalSetOut[i][j] != 0)
				j + 1 == globalSetOut[i].size() ? oStream << globalSetOut[i][j] : oStream << globalSetOut[i][j] << "-";
		}
		oStream << endl;
	}

	oStream.close();
}

void  Graph::readGraphFromFile(string fileName){

	ifstream iStream;
	vertice tmpVertice;
	vector<string> data;

	iStream.open(fileName, std::ifstream::in);

	if (iStream.is_open()){
		while (iStream.good()){
			data.push_back("");
			getline(iStream, data[data.size() - 1]);
		}

		Graph::size = stoi(data[0]);

		for (int i = 0; i < stoi(data[0]); i++){
			this->graph_set_random.push_back(tmpVertice);
			this->graph_set_random[i].id = i + 1;
		}

		regex wzorInOut("([[:digit:]]+)|(out:)");

		for (int i = 1; i < data.size(); i++){

			sregex_iterator it(data[i].begin(), data[i].end(), wzorInOut);
			sregex_iterator it_end;

			//Szukanie liczb IN, az osiagnie "out:"
			while (it != it_end) {
				if (!(*it).str().compare("out:"))
					break;	
				this->graph_set_random[i - 1].inID.push_back(stoi((*it).str()));			
				++it;
			}
	
			bool afterOut = false;

			//Szukanie liczb Out, po znalezieniu "out:"
			while (it != it_end) {
				if (!(*it).str().compare("out:")){
					afterOut = true;
					++it;
				}
					
				if (it == it_end)
					break;

				if (afterOut){	
					this->graph_set_random[i - 1].outID.push_back(stoi((*it).str()));
				}
				++it;
			}
		}
	}else{
		cout << "Nie udalo sie otworzyc pliku: " << fileName << endl;
	}
	iStream.close();
}

void Graph::showGraph(){
	for (int i = 0; i < (int) this->graph_set.size(); i++){
		cout << "ID wierzcholka: [" << this->graph_set[i].id << "]" << " slowo: " << this->graph_set[i].word <<  endl;
		cout << "ZBIOR In: " ;
		for (int &j : graph_set[i].inID){
			cout << j << ", ";
		}
		cout << endl << "Zbior Out: " ;
		for (int &j : graph_set[i].outID){
			cout << j << ", ";
		}
		cout << endl << "=======================" << endl;
	}
}

bool Graph::createGraphFromFile(string fileName, int window){
	ifstream iStream;
	iStream.open(fileName, std::ifstream::in);
	int id = 1;

	if (iStream.is_open()){
		while (iStream.good()){
			unique_ptr<wordsVert> tmp(new wordsVert);
			getline(iStream, tmp->word );
			graph_set.push_back(*tmp);
			graph_set[graph_set.size() - 1].id = id;
			id++;
		}
	}
	else{
		cout << "Nie udalo sie otworzyc pliku: " << fileName << endl;
		return false;
	}

	iStream.close();
	
	for (int i = 0; i < (int) graph_set.size(); i++){
		for (int j = i + 1; j < (int) graph_set.size(); j++){

			if (!graph_set[j].child){ // nie jest 'dzieckiem'
				if (graph_set[i].word.compare(graph_set[j].word) == 0) { //wyraz ten sam
					graph_set[j].word = "nope";
					graph_set[j].child = true;
					graph_set[j].ptrToParent = &graph_set[i];
				}
				
			}
		}
	}

	//PRZYDZEILANIE INÓW i OUTÓW
	for (int i = 0; i < (int) graph_set.size() - (window - 1); i++){
		for (int j = 0, it = i; j < window - 1; j++, it++){
			if (!graph_set[it+1].child){ //nie jest dzieckiem
				if (graph_set[i].word.compare(graph_set[it + 1].word) != 0){ //wyraz rozny

					if (!graph_set[i].child){
						graph_set[i].outID.push_back(graph_set[it + 1].id);
						graph_set[it + 1].inID.push_back(graph_set[i].id);
					}
					else{
						graph_set[i].ptrToParent->outID.push_back(graph_set[it + 1].id);
						graph_set[it+1].inID.push_back(graph_set[i].ptrToParent->id); 

					}
					
				}
			}
			else{

				if (!graph_set[i].child){
					graph_set[i].outID.push_back(graph_set[it + 1].ptrToParent->id);
					graph_set[it + 1].ptrToParent->inID.push_back(graph_set[i].id);
				}
				else{
					graph_set[i].ptrToParent->outID.push_back(graph_set[it + 1].ptrToParent->id);
					graph_set[it + 1].ptrToParent->inID.push_back(graph_set[i].ptrToParent->id); 
				}
				
				
			}
		}
	}


	//obrobka po - usuawnie nope i sprzatanie
	bool exit = false;
	int it = 0;
	do{	
		if (graph_set[it].child){
			graph_set.erase(graph_set.begin() + it);
			
			for (int i = it; i < (int) graph_set.size(); i++){
				graph_set[i].id--;
			}

			for (int i = 0; i < (int) graph_set.size(); i++){
				if (!graph_set[i].child){ //nie jest dzieckiem
					for (int &x : graph_set[i].inID){
						if (x > it + 1)
							x--;
					}
					for (int &x : graph_set[i].outID){
						if (x > it + 1)
							x--;
					}
				}
			}
			it--;
		}		
		it++;
		if (it == graph_set.size())
			exit = true;
	} while (!exit);

	//usuwanie zapetlen w in'ach i out'ach
	for (int i = 0; i < (int) graph_set.size(); i++){
		graph_set[i].inID = deleteLoops(graph_set[i].inID);
		graph_set[i].outID = deleteLoops(graph_set[i].outID);	
	}

	return true;
}

vector<int> Graph::deleteLoops(vector<int> tmpVec){
	for (int j = 0; j < (int) tmpVec.size(); j++){
		for (int k = j + 1; k < (int) tmpVec.size(); k++){
			if (tmpVec[j] == tmpVec[k]){
				tmpVec.erase(tmpVec.begin() + k);
				k--;
			}
		}
	}

	return tmpVec;
}

Graph::~Graph()
{
}
