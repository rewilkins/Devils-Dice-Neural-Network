#pragma once
#ifndef OPTIMAL_AI
#define OPTIMAL_AI

#include <iostream>
#include <string>
#include <fstream>
#include "Player.h"

class OptimalAI : public Player {

private:
	bool passed = true;
	int inf_RollCount = 0;		// how many times the A.I. has rolled	
	int inf_OpponentsScore = 0;	// the overall score of the AI's opponent
	double inf_FreqOf1s = 0.0;	// the frequency at which 1s are being roled.
	int overallNumOfTurns = 0;	// tracks the overall number of times the AI has rolled.  overallNum1sRolled/overallNumOfTurns = 1s frequency or inf_FreqOf1s
	int overallNum1sRolled = 0;	// The number of 1s that have been rolled.  AI becomes more cautious and reserved due to superstition.

public:
	OptimalAI() {
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

	OptimalAI(std::string name, bool _withPauses, bool _withPrint) {
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

		std::fstream fout;
		fout.open("data.txt", std::fstream::in | std::fstream::out | std::fstream::app);
		fout << (double)(inf_RollCount / 100.0f) << " " << (double)inf_FreqOf1s << " " << (double)(turnScore / 100.0f) << " " << (double)(savedScore / 100.0f) << " " << (double)(inf_OpponentsScore / 100.0f) << " " << (int)(turnScore <= 20) << "\n";
		fout.close();

		if (turnScore <= 20) {
			inf_RollCount++;
			if (withPrint) std::cout << "            I choose to roll.";
			if (withPauses) pause(1);
			return 'r';
		}
		if (withPrint) std::cout << "            I choose to pass.";
		if (withPauses) pause(1);
		return 'p';
	}

	void additionalPrint(int player, int i, bool player1sTurn) {

	}

};

#endif