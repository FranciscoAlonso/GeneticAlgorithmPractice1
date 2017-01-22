// Genetic1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Genes.h"
#include "Chromosome.h"
#include "GeneticAlgorithm.h"
#include <Windows.h>

int main()
{
	Genes mGenes = *new Genes(); //instance for gene operations
	GeneticAlgorithm mGeneticAlgorithm = *new GeneticAlgorithm(40, 3);
	Chromosome result = mGeneticAlgorithm.EvolutionCycle();
	if (result.fitnessScore == -2)
	{
		cout << "Error at finding a solution." << endl;
	}
	else
	{
		cout << "solution found at THE END: " << result.chromosomeString << endl;
		result.PrintChromosome();
	}
    return 0;
}



