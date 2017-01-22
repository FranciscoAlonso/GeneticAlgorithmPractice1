#pragma once
#include "stdafx.h"
#include "Genes.h"
#include <vector>
using namespace std;

class Chromosome
{
public:
	string chromosomeString;
	vector<string> geneStringArray;
	vector<int> geneIntArray;
	double fitnessScore;
	static int lenght;
	static float targetNumber;

	Chromosome();
	Chromosome(string chromoString, float targetNum);
	~Chromosome();
	void PrintChromosomeString();
	float GetFitnessScore();
	void PrintChromosome();
private:
	void getGenes();
	float Calculate(float a, int operand, int b);
};
