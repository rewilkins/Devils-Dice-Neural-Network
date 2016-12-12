#pragma once
#ifndef PLAYER
#define PLAYER

#include "DevilsDiceGame.h"

class Player
{

protected:
	std::string playerName;
	int savedScore = 0;
	int turnScore = 0;
	int winCount = 0;
	int lossCount = 0;

	bool withPauses = false;
	bool withPrint = false;

	void pause(int seconds)
	{
		time_t start, current;
		time(&start);
		do
		{
			time(&current);
		} while ((current - start) < seconds);
	}

	int randomNumGen(int min, int max) {
		std::random_device rd;
		std::mt19937 e2(rd());
		std::uniform_real_distribution<> dist(min, max + 1);
		return dist(e2);
	}

public:

	virtual char getAction(int oppenentsScore) {
		std::cout << "Invalid player type" << std::endl;
		pause(2);
		return 'R';
	}

	virtual void additionalPrint(int player, int i, bool player1sTrun) {

	}

	std::string getPlayerName() {
		return playerName;
	}

	int getSavedScore() {
		return savedScore;
	}

	void setSavedScore(int input) {
		savedScore = input;
	}

	int getTurnScore() {
		return turnScore;
	}

	void setTurnScore(int input) {
		turnScore = input;
	}

	int getWinCount() {
		return winCount;
	}

	void setWinCount(int input) {
		winCount = input;
	}

	int getLossCount() {
		return lossCount;
	}

	void setLossCount(int input) {
		lossCount = input;
	}

	void reset() {
		savedScore = 0;
		turnScore = 0;
	}

	void saveScore() {
		std::ofstream fout;
		fout.open(playerName + ".txt");
		fout << winCount << std::endl;
		fout << lossCount << std::endl;
		fout.close();
	}

};

#endif