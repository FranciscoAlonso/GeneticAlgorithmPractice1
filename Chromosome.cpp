#include "Chromosome.h"

using namespace std;
int Chromosome::lenght = 36;
float Chromosome::targetNumber;

Chromosome::Chromosome()
{
	fitnessScore = -2;
}

Chromosome::Chromosome(string chromoString, float targetNum)
{
	chromosomeString = chromoString;
	targetNumber = targetNum;
	getGenes();
	fitnessScore = GetFitnessScore();
	if (fitnessScore == -1)
	{
		//solution found
		//cout << "solution found: " << chromosomeString << endl;
		//PrintChromosome();
	}
	//cout << "FitnessScore: " << Chromosome::fitnessScore << endl;
}

Chromosome::~Chromosome()
{ 
}

void Chromosome::PrintChromosomeString()
{
	cout << Chromosome::chromosomeString << endl;
}

/*
Puts the genes values into a string array and a int array to be used later
*/
void Chromosome::getGenes()
{
	//size_t is used to avoid type comparison warning 
	for (size_t i = 0; i < chromosomeString.size(); i = i + 4)
	{
		geneStringArray.push_back(chromosomeString.substr(i, 4));
		geneIntArray.push_back(Genes::GetIntFromGeneString(geneStringArray.back()));
		//cout << geneStringArray.back() << " " << geneIntArray.back() << endl;
	}
}

/*
Calculates the fitness score of the chromosome.
When it founds an error in the genes it skips to the next valid gene.
*/
float Chromosome::GetFitnessScore()
{
	float fitnessScore = 0.0;
	bool operand = true;
	int currentOperator = 10;
	for (size_t i = 0; i < geneIntArray.size(); i++)
	{
		try
		{
			if (geneIntArray.at(i) >= 0 && geneIntArray.at(i) < 10 && operand)
			{
				operand = false;
				fitnessScore = Chromosome::Calculate(fitnessScore, currentOperator, geneIntArray.at(i));
				//cout << "current operand: " << geneIntArray.at(i) << " cumulative: " << fitnessScore << endl;
			}
			else if (geneIntArray.at(i) >= 10 && geneIntArray.at(i) <= 13 && !operand)
			{
				operand = true;
				currentOperator = geneIntArray.at(i);
				//cout << "operator: " << geneIntArray.at(i) << endl;
			}
			else if(geneIntArray.at(i) > 13)
			{
				//cout << "gene error" << endl;
				continue;
			}
		}
		catch (std::out_of_range o)
		{
			cout << "index out of range: " << i << "Error: " << o.what() << endl;
		}
	}

	//cout << "Score: " << fitnessScore << endl;
	if (fitnessScore == Chromosome::targetNumber)
	{
		//cout << "FitnessScore: EQUAL" << fitnessScore << endl;
		return -1;
	}
	else
	{
		//cout << "FitnessScore: " << 1 / (Chromosome::targetNumber - fitnessScore) << endl;
		return abs(1 / (Chromosome::targetNumber - fitnessScore));
	}
}

/*
Returns the result depending on the code assigned to the operator
*/
float Chromosome::Calculate(float a, int operand, int b)
{
	switch (operand)
	{
	case 10:
		return a + b;
		break;
	case 11:
		return a - b;
		break;
	case 12:
		return a * b;
		break;
	case 13:
		return a / b;
		break;
	default:
		return a;
		break;
	}
}

void Chromosome::PrintChromosome()
{
	for (size_t i = 0; i < geneIntArray.size(); i++)
	{
		try
		{
			if (geneIntArray.at(i) >= 0 && geneIntArray.at(i) < 10)
			{
				cout << geneIntArray.at(i) << " ";
			}
			else if (geneIntArray.at(i) == 10)
			{
				cout << " + ";
			}
			else if (geneIntArray.at(i) == 11)
			{
				cout << " - ";
			}
			else if (geneIntArray.at(i) == 12)
			{
				cout << " * ";
			}
			else if (geneIntArray.at(i) == 13)
			{
				cout << " / ";
			}
			else if (geneIntArray.at(i) > 13)
			{
				cout << " error ";
			}
		}
		catch (std::out_of_range o)
		{
			cout << "index out of range: " << i << "Error: " << o.what() << endl;
		}
		//cout << geneStringArray.back() << " " << geneIntArray.back() << endl;
	}
	cout << endl;
}