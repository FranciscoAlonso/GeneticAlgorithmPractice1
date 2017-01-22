#include "Genes.h"

using namespace std;

map<string, int> Genes::genesMap;

Genes::Genes()
{
	genesMap.insert(std::pair<string, int>("0000", 0)); // 0
	genesMap.insert(std::pair<string, int>("0001", 1)); // 1
	genesMap.insert(std::pair<string, int>("0010", 2)); // 2
	genesMap.insert(std::pair<string, int>("0011", 3)); // 3
	genesMap.insert(std::pair<string, int>("0100", 4)); // 4
	genesMap.insert(std::pair<string, int>("0101", 5)); // 5
	genesMap.insert(std::pair<string, int>("0110", 6)); // 6
	genesMap.insert(std::pair<string, int>("0111", 7)); // 7
	genesMap.insert(std::pair<string, int>("1000", 8)); // 8
	genesMap.insert(std::pair<string, int>("1001", 9)); // 9
	genesMap.insert(std::pair<string, int>("1010", 10)); // +
	genesMap.insert(std::pair<string, int>("1011", 11)); // -
	genesMap.insert(std::pair<string, int>("1100", 12)); // *
	genesMap.insert(std::pair<string, int>("1101", 13)); // /
	genesMap.insert(std::pair<string, int>("1110", 14)); //not valid
	genesMap.insert(std::pair<string, int>("1111", 15)); //not valid
}

Genes::~Genes()
{

}

void Genes::printGenes()
{
	//cout << "Genes" << endl;
	//cout << &Genes::_0 << endl;
	//string str = _1.template to_string<char, char_traits<char>, allocator<char>>();
	//cout << str << endl;
}

int Genes::GetIntFromGeneString(string gene)
{
	return Genes::genesMap.at(gene);
}
