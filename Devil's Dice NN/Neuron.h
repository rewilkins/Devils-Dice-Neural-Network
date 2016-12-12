#pragma once
#ifndef NEURON   // if x.h hasn't been included yet...
#define NEURON

#include <vector>

class Neuron
{
public:

	void loadWeights(std::vector<double> newWeights);
	void loadInputs(std::vector<double> newInputs);
	void toggleMode(int mode);
	void clearErrorList();
	double getAvrgError();
	double getOutput();
	double getAccuracy();
	void run();

//private:

	void processInputs();
	void activationFunction();
	void computeError();
	void updateWeights();
	double randomNumGen();



	int neuronMode = 1;  // 1 = training; 2 = testing; 3 = using
	int trainingModifier = 1;
	double learningRate = 0.001;

	std::vector<double> inputs;
	std::vector<double> weights;

	double processedResult = 0.0;
	double activatedResult = 0.0;
	double expectedResult = 0.0;
	std::vector<double> errors;
	double averageError = 1.0;

	int incorrectResponse;
	int correctResponse;
	double accuracy = 0.0;

};

#endif 