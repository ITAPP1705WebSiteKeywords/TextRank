#include "stdafx.h"
#include "Localwords.h"

using namespace std;

Localwords::Localwords() 
{
}

Localwords::~Localwords() 
{
}

bool Localwords::loadWordsList(string fileName)
{
	ifstream iStream;
	iStream.open(fileName, std::ifstream::in);
	string tmp;

	if (iStream.is_open()){
		while (iStream.good()){	
			getline(iStream, tmp);
			listOfWords.push_back(tmp);
		}
	}
	else{
		cout << "Nie udalo sie otworzyc pliku: " << fileName << endl;
		return false;
	}

	iStream.close();
	return true;
}

void Localwords::setWordsDistance()
{
	// listOfWords
	pair<std::map<string, vector<int>>::iterator,bool> ret;

	for(int i = 0; i < listOfWords.size(); i++){
		vector<int> tmpDistance;
				
		if(checkWord(listOfWords[i])){ //sprawdzenie czy nie znak interpunkcyjny
			ret = localMatrix.insert ( pair<string,vector<int>>(listOfWords[i],tmpDistance) );

			if (ret.second==false) { //sprawdzenie czy sie powtarza
				cout << "element already existed with a value of " << endl;

				//uaktualnienie ostatniej pozycji
				map<string,int>::key_compare comp = lastRepeatMap.key_comp();
				string highest = lastRepeatMap.rbegin()->first;
				map<string,int>::iterator it = lastRepeatMap.begin();
				do{
					if(it->first.compare(listOfWords[i])){
						it->second = i+1;
					}
				} while ( comp((*it++).first, highest) );
			}
			else{ //nie interpunkcyjny i nie powtarza sie
				lastRepeatMap.insert(pair<string,int>(listOfWords[i],i+1));	
				for(int j = 1; j < lastRepeatMap.size(); j++){
				int tmpValue = 0;
					for(int k=1; k < lastRepeatMap.rbegin()->second; k++){
						tmpValue =+ setTmpDistanceValue(listOfWords[j]);
					}
				map<string, vector<int>>::iterator it2 = localMatrix.find(listOfWords[i]); 
				if (it2 != localMatrix.end())
    					it2->second.push_back(tmpValue);
				}

				tmpDistance.clear();
			}
		}
		else{
			cout << "Znak srututu" << endl; 
		}		
	}	
}

void Localwords::printWordsList()
{
	/*for(string &x : listOfWords){
		cout << x << endl;
	}*/
	
/*cout << "localMatrix" << endl;
for (std::map<char,int>::iterator it=localMatrix.begin(); it!=localMatrix.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';*/

cout << "lastRepeatMap" << endl;
for (std::map<string,int>::iterator it=lastRepeatMap.begin(); it!=lastRepeatMap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
}

int Localwords::setTmpDistanceValue(string word)
{	
	if(!word.compare(":")){
		return 2;
	}
	else if(!word.compare(";")){
		return 10;
	}
	else if(!word.compare(".")){
		return 30;
	}
	else if(!word.compare("!")){
		return 30;
	}	
	else if(!word.compare("?")){
		return 30;
	}
	else{
		return 1;
	}
		
}

bool Localwords::checkWord(string word)
{
	//dodaj regex
	if(!word.compare(":")){
		return false;
	}
	else if(!word.compare(";")){
		return false;
	}
	else if(!word.compare(".")){
		return false;
	}
	else if(!word.compare("!")){
		return false;
	}	
	else if(!word.compare("?")){
		return false;
	}
	else{
		return true;
	} 		
}
