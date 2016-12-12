#include "Neuron.h"
#include <iostream>
#include <vector>
#include <random>

void Neuron::loadWeights(std::vector<double> newWeights) {
	for (int i = 0; i < newWeights.size(); i++) {
		weights.push_back(newWeights[i]);
	}
}

void Neuron::loadInputs(std::vector<double> newInputs) {
	inputs.clear();
	//weights.clear();
	inputs.push_back(1); // bias is in slot 0
	//weights.push_back(randomNumGen());  // weight on bias is in slot 0

	for (int i = 0; i < newInputs.size() + 1 - trainingModifier; i++) {
		inputs.push_back(newInputs[i]);
		//weights.push_back(randomNumGen());
	}
	if (neuronMode != 3) {
		expectedResult = newInputs[newInputs.size() - 1];
	}
}

void Neuron::toggleMode(int mode) {
	if (mode == 1) neuronMode = 1;
	if (mode == 2) neuronMode = 1;
	if (mode == 3) neuronMode = 0;
	neuronMode = mode;
}

void Neuron::clearErrorList() {
	errors.clear();
}

double Neuron::getAvrgError() {
	return averageError;
}

double Neuron::getOutput() {
	return activatedResult;
}

double Neuron::getAccuracy() {
	return accuracy;
}

void Neuron::run() {
	processInputs();
	activationFunction();
	computeError();
	updateWeights();
}

void Neuron::processInputs() {
	if (inputs.size() != weights.size()) {
		std::cout << "error: incorrect inputs and/or weights count" << std::endl;
	}
	else {
		processedResult = 0;
		for (int i = 0; i < inputs.size(); i++) {
			processedResult += (inputs[i] * weights[i]);
		}
	}
}

void Neuron::activationFunction() {
	activatedResult = (1 / (1 + (exp(-processedResult))));
	if (neuronMode == 2) {
		if (activatedResult > 0.5) {
			activatedResult = 1;
		}
		else {
			activatedResult = 0;
		}
		if (expectedResult == activatedResult) correctResponse++;
		else incorrectResponse++;
		accuracy = ((double)correctResponse / ((double)correctResponse + (double)incorrectResponse)) * 100;
	}
}

void Neuron::computeError() {
	if (neuronMode == 1) {
		// get curr error
		double newError;
		newError = pow((expectedResult - activatedResult), 2);
		errors.push_back(newError);

		// get average error
		averageError = 0.0;
		for (int i = 0; i < errors.size(); i++) {
			averageError += errors[i];
		}
		averageError /= errors.size();
	}
}

void Neuron::updateWeights() {
	if (neuronMode == 1) {
		double g = 1 / (1 + exp(-processedResult));
		double gPrime = g * (1 - g);
		for (int i = 0; i < inputs.size(); i++) {
			double deltaWeight = learningRate * (expectedResult - activatedResult) * gPrime * inputs[i];
			weights[i] += deltaWeight;
		}
	}
}

double Neuron::randomNumGen() {
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(0, 2);
	return dist(e2);
}