#pragma once
#include "stdafx.h"
#include <map>

using namespace std;
//typedef std::bitset<4> gene;
 
class Genes
{
public:
	static map<string, int> genesMap;
	
	Genes();
	~Genes();
	static void printGenes();
	static int GetIntFromGeneString(string gene);
};