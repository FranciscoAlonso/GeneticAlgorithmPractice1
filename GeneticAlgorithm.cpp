#include <random>
#include "GeneticAlgorithm.h"

int GeneticAlgorithm::populationQty = 100;
vector<Chromosome> GeneticAlgorithm::population;
int GeneticAlgorithm::seed = 42;
float GeneticAlgorithm::targetNumber;
double GeneticAlgorithm::crossoverRate = 0.7;
double GeneticAlgorithm::mutationRate = 0.001;
int GeneticAlgorithm::numberOfCycles;

GeneticAlgorithm::GeneticAlgorithm(float targetNum, int cycles)
{
	targetNumber = targetNum;
	numberOfCycles = cycles;
	population.reserve(populationQty);
	
	//cout << "Test Parent: " << endl << testParent.chromosomeString << endl;
	//cout << "fitness: " << testParent.fitnessScore << endl;
	//cout << "maxfitness: " << GetMaxFitness().at(0) << endl;
}

GeneticAlgorithm::~GeneticAlgorithm() //TODO: fix the memory issues here
{
	//http://stackoverflow.com/questions/10464992/c-delete-vector-objects-free-memory
	population.clear();
	population.swap(vector<Chromosome>(population));
}

Chromosome GeneticAlgorithm::GenerateFirstPopulation()
{
	double maxFitness = -1.0;
	
	for (int i = 0; i < populationQty; i++)
	{
		population.push_back(GenerateRandomChromosome());
		//cout << population.at(i).chromosomeString << endl;
		try
		{
			if (population.at(i).fitnessScore == -1)
			{
				cout << "solution found at FIRST: " << population.at(i).fitnessScore << endl;
				population.at(i).PrintChromosome();
				return population.at(i);
			}
			if (maxFitness < population.at(i).fitnessScore)
			{
				maxFitness = population.at(i).fitnessScore;
			}
		}
		catch (std::out_of_range o)
		{
			cout << "index out of range: " << i << "Error: " << o.what() << endl;
		}
	}
	populationMaxFitness = maxFitness;
	return *new Chromosome();
	//cout << population.size() << endl;
}

Chromosome GeneticAlgorithm::GenerateRandomChromosome()
{
	char asciiNumber = 0;
	string mChromosomeString = "";
	random_device rd;
	mt19937 mt(rd());
	//mt19937 mt(42);
	uniform_int_distribution<int> dist(48, 49);
	for (int i = 0; i < Chromosome::lenght; i++)
	{
		asciiNumber = dist(mt);
		mChromosomeString.push_back(asciiNumber);
	}	
	Chromosome newChromosome = *new Chromosome(mChromosomeString, GeneticAlgorithm::targetNumber);
	return newChromosome;
}

int GeneticAlgorithm::RouletteWheelSelection()
{
	/*
	Stocasthic acceptance method described in:
	https://arxiv.org/pdf/1109.3627v2.pdf
	*/
	random_device rd;
	mt19937 mt(rd());
	//mt19937 mt(42);
	uniform_int_distribution<int> intDist(0, population.size()-1);
	uniform_real_distribution<> realDist(0, 1);
	int index = 0;
	while (true)
	{
		index = intDist(mt);
		try
		{
			if (realDist(mt) < population.at(index).fitnessScore / populationMaxFitness)
			{
				//cout << population.at(index).fitnessScore << endl;
				//return population.at(index);
				return index;
			}
		}
		catch (std::out_of_range o)
		{
			cout << "index out of range: " << index << "Error: " << o.what() << endl;
		}
	}
}

Chromosome GeneticAlgorithm::GetMaxFitnessChromosome()
{
	double maxFitness = 0.0;
	int maxFitnessIndex = 0;

		for (size_t i = 0; i < population.size(); i++)
		{
			try
			{
				if (population.at(i).fitnessScore > maxFitness)
				{
					maxFitness = population.at(i).fitnessScore;
					maxFitnessIndex = i;
				}
			}
			catch (std::out_of_range o)
			{
				cout << "index out of range: " << i << "Error: " << o.what() << endl;
			}
		}
		return population.at(maxFitnessIndex);
}

Chromosome GeneticAlgorithm::GenerateNewPopulation()
{
	vector<Chromosome> newPopulationVector;
	newPopulationVector.reserve(populationQty);
	Chromosome helperChromosome;
	int subjectIndex1 = 0;
	int subjectIndex2 = 0;
	Chromosome newSubject;
	string newChromosomeString;
	random_device rd;
	mt19937 mt(rd());
	//mt19937 mt(42);
	uniform_real_distribution<> realDist(0, 1);
	for (int i = 0; i < populationQty; i++)
	{
		subjectIndex1 = RouletteWheelSelection(); //select subject
		try
		{
			if (realDist(mt) < crossoverRate) //apply crossover rate
			{
				subjectIndex2 = RouletteWheelSelection();
				while (subjectIndex1 == subjectIndex2)
				{
					subjectIndex2 = RouletteWheelSelection();
				}
				uniform_int_distribution<int> intDist(0, Chromosome::lenght - 1);
				int crossoverIndex = intDist(mt);
				newChromosomeString = ChromosomeCrossover(population.at(subjectIndex1).chromosomeString
														, population.at(subjectIndex2).chromosomeString
														, crossoverIndex);
			}
			else
			{
				newChromosomeString = population.at(subjectIndex1).chromosomeString;
			}

			newChromosomeString = ChromosomeMutation(newChromosomeString); //apply mutation rate
			helperChromosome = *new Chromosome(newChromosomeString, targetNumber); //create new chromosome
			newPopulationVector.push_back(helperChromosome); //add to new population array
			if (newPopulationVector.at(i).fitnessScore == -1)
			{
				cout << "solution found at a NEW one: " << newPopulationVector.at(i).chromosomeString << endl;
				newPopulationVector.at(i).PrintChromosome();
				return newPopulationVector.at(i);
			}
		}
		catch (std::out_of_range o)
		{
			cout << "index out of range: " << i << "Error: " << o.what() << endl;
		}
	}
	population.swap(newPopulationVector);
	newPopulationVector.clear();
	newPopulationVector.swap(vector<Chromosome>(newPopulationVector));
	return *new Chromosome();
}

/*
replaces the string 'a' characters from 'index' with the string 'b' characters from 'index'
*/
string GeneticAlgorithm::ChromosomeCrossover(string a, string b, int index)
{
	string newString = a;
	//cout << newString << endl;
	newString.replace(index, newString.length() - index, b.substr(index, b.length() - index));
	//cout << newString << endl;
	return newString;
}

/*
Mutates each bit on the string based on the probability of mutationRate
*/
string GeneticAlgorithm::ChromosomeMutation(string mutateChromosomeString)
{
	random_device rd;
	mt19937 mt(rd());
	//mt19937 mt(42);
	uniform_real_distribution<> realDist(0, 1);
	for (size_t i = 0; i < mutateChromosomeString.length(); i++)
	{
		if (realDist(mt) < mutationRate)
		{
			try
			{
				FlipBit(mutateChromosomeString.at(i));
			}
			catch (std::out_of_range o)
			{
				cout << "index out of range: " << i << "Error: " << o.what() << endl;
			}
			
		}
	}

	return mutateChromosomeString;
}

/*
flips one character bit, if the character is different from 1 or 0 it does nothing
*/
void GeneticAlgorithm::FlipBit(char& bit)
{
	if (bit == '1')
	{
		bit = '0';
	}
	else if(bit == '0')
	{
		bit = '1';
	}
}

Chromosome GeneticAlgorithm::EvolutionCycle()
{
	int currentCycle = 0;
	Chromosome resultChromosome = GenerateFirstPopulation();

	while (currentCycle < numberOfCycles)
	{
		//cout << currentCycle << endl;
		if (resultChromosome.fitnessScore == -1)
		{
			return resultChromosome;
		}
		resultChromosome = GenerateNewPopulation();
		currentCycle++;
	}
	return GetMaxFitnessChromosome();
}