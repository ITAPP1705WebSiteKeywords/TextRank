#include "stdafx.h"

using namespace std;

int main(int argc, char *argv[])
{
	string fileName = argv[1];
	Localwords local;

	local.loadWordsList(fileName);
	local.setWordsDistance();
	local.printWordsList();
	return 0;
}

