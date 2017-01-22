#pragma once
#include "stdafx.h"
#include "Genes.h"
#include <vector>
#include "Chromosome.h"

using namespace std;

class  GeneticAlgorithm
{
public:
	 GeneticAlgorithm(float targetNum, int cycles);
	~ GeneticAlgorithm();
	static int populationQty;
	static vector<Chromosome> population; 
	//TODO: reserve() the needed space
	//TODO: use vector<int>::at and catch(std::out_of_range o) 
	//TODO: use iterators. Edit: I might not need iterators.
	static int seed;
	static float targetNumber;
	static double crossoverRate;
	static double mutationRate;
	static int numberOfCycles;

	Chromosome GetMaxFitnessChromosome();
	Chromosome EvolutionCycle();
private:
	double populationMaxFitness;
	Chromosome GenerateFirstPopulation();
	Chromosome GenerateRandomChromosome();
	int RouletteWheelSelection();
	Chromosome GenerateNewPopulation();
	string ChromosomeCrossover(string a, string b, int index);
	string ChromosomeMutation(string mutateChromosomeString);
	void FlipBit(char& bit);
};

