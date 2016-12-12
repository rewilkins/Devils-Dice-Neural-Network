#pragma once
#ifndef ORIGINAL_NN
#define ORIGINAL_NN

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Player.h"
#include "Neuron.h"
#include "neuralNetwork.h"

class OriginalNN : public Player {

private:
	bool passed = true;
	int inf_RollCount = 0;		// how many times the A.I. has rolled	
	int inf_OpponentsScore = 0;	// the overall score of the AI's opponent
	double inf_FreqOf1s = 0.0;	// the frequency at which 1s are being roled.
	int overallNumOfTurns = 0;	// tracks the overall number of times the AI has rolled.  overallNum1sRolled/overallNumOfTurns = 1s frequency or inf_FreqOf1s
	int overallNum1sRolled = 0;	// The number of 1s that have been rolled.  AI becomes more cautious and reserved due to superstition.

public:
	OriginalNN() {
		std::ifstream fin;
		fin.open("player.txt");
		if (fin.good()) {
			fin >> winCount;
			fin >> lossCount;
			fin.close();
		}
		else {
			winCount = 0;
		}
		if (winCount < 0) winCount = 0;

	}

	OriginalNN(std::string name, bool _withPauses, bool _withPrint) {
		playerName = name;

		std::ifstream fin;
		fin.open(playerName + ".txt");
		if (fin.good()) {
			fin >> winCount;
			fin >> lossCount;
			fin.close();
		}
		else {
			winCount = 0;
		}
		if (winCount < 0) winCount = 0;

		withPauses = _withPauses;
		withPrint = _withPrint;
	}

	char getAction(int oppenentsScore) {
		if (turnScore == 0) { // once per turn event
			overallNumOfTurns++;
			inf_RollCount = 0; // reset rollCount on first turn
			inf_OpponentsScore = oppenentsScore;
			if (passed == false) { // must have rolled a 1 last turn we are here and this condition is true
				overallNum1sRolled++;
			}
		}
		passed = false;

		if (overallNumOfTurns == 0.0) inf_FreqOf1s = 0.0;
		else inf_FreqOf1s = (double)overallNum1sRolled / (double)overallNumOfTurns;



		neuralNetwork nn(5, 3, 1);
		nn.loadWeights("weights_Original.csv");
		double* pattern = new double[5];
		pattern[0] = (double)(inf_RollCount / 100.0f);
		pattern[1] = (double)inf_FreqOf1s;
		pattern[2] = (double)(turnScore / 100.0f);
		pattern[3] = (double)(savedScore / 100.0f);
		pattern[4] = (double)(inf_OpponentsScore / 100.0f);
		int* choice = nn.feedForwardPattern(pattern);



		if (*choice == 1) {
			inf_RollCount++;
			if (withPrint) std::cout << "            I choose to roll.";
			if (withPauses) pause(1);
			return 'r';
		}
		else {
			inf_RollCount = 0;
			passed = true;
			if (withPrint) std::cout << "            I choose to pass.";
			if (withPauses) pause(1);
			return 'p';
		}

	}

	void additionalPrint(int player, int i, bool player1sTurn) {

	}

};

#endif