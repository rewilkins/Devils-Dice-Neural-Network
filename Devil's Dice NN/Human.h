#pragma once
#ifndef HUMAN_BASE
#define HUMAN_BASE

#include <iostream>
#include <string>
#include <fstream>
#include "Player.h"

class Human : public Player{
public:
	Human() {
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

	Human(std::string name, bool _withPauses, bool _withPrint) {
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
		char playerAction;
		std::cout << "            " + playerName + "'s action: ";
		std::cin >> playerAction;
		return playerAction;
	}

	void additionalPrint(int player, int i, bool player1sTurn) {

	}

};

#endif 