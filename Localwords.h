#pragma once
using namespace std;

class Localwords
{
	private:
	map<string, vector<int>> localMatrix; // <slowo1 , <odleglosc1, odleglosc2, (...)>>
	map<string, int> lastRepeatMap; // <slowo, ostatnie wystapienie>
	
	vector<string> listOfWords; //lista wszystkich slow

	public:
	bool loadWordsList(string);
	void printWordsList();
	void setWordsDistance();
	int setTmpDistanceValue(string word);
	bool checkWord(string word);
	Localwords();
	~Localwords();
};
