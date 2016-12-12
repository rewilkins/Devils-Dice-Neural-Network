#pragma once
#ifndef RANDOM_AI
#define RANDOM_AI

#include <iostream>
#include <string>
#include <fstream>
#include "Player.h"

class RandomAI : public Player {

private:
	bool passed = true;
	int inf_RollCount = 0;		// how many times the A.I. has rolled	
	int inf_OpponentsScore = 0;	// the overall score of the AI's opponent
	double inf_FreqOf1s = 0.0;	// the frequency at which 1s are being roled.
	int overallNumOfTurns = 0;	// tracks the overall number of times the AI has rolled.  overallNum1sRolled/overallNumOfTurns = 1s frequency or inf_FreqOf1s
	int overallNum1sRolled = 0;	// The number of 1s that have been rolled.  AI becomes more cautious and reserved due to superstition.

public:

	int choice = 0;

	RandomAI() {
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

	RandomAI(std::string name, bool _withPauses, bool _withPrint) {
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

		choice = -1;

		std::fstream fout;
		fout.open("data.txt", std::fstream::in | std::fstream::out | std::fstream::app);
		fout << (double)(inf_RollCount / 100.0f) << " " << (double)inf_FreqOf1s << " " << (double)(turnScore / 100.0f) << " " << (double)(savedScore / 100.0f) << " " << (double)(inf_OpponentsScore / 100.0f) << " " << (int)(choice == 1 || turnScore == 0) << "\n";
		fout.close();

		if (turnScore == 0) {
			inf_RollCount++;
			if (withPrint) std::cout << "            I choose to roll.";
			if (withPauses) pause(1);
			return 'r';
		}

		choice = randomNumGen(0, 1);

		if (choice == 1) {
			inf_RollCount++;
			if (withPrint) std::cout << "            I choose to roll.";
			if (withPauses) pause(1);
			return 'r';
		}
		else {
			if (withPrint) std::cout << "            I choose to pass.";
			if (withPauses) pause(1);
			return 'p';
		}
	}

	void additionalPrint(int player, int i, bool player1sTurn) {

		if (player == 0) {

			if (i == 95) std::cout << "            Choise:    " << choice;
		
		}

		if (player == 1) {

			if (i == 45) std::cout << "            Choise:    " << choice;
			
		}

	}

};

#endif