#pragma once
#ifndef ORIGINAL_AI
#define ORIGINAL_AI

#include <iostream>
#include <string>
#include <fstream>
#include "Player.h"

class OriginalAI : public Player{

private:
	bool passed = true;
	int inf_RollCount = 0;		// how many times the A.I. has rolled	
	int inf_OpponentsScore = 0;	// the overall score of the AI's opponent
	double inf_FreqOf1s = 0.0;	// the frequency at which 1s are being roled.
	int overallNumOfTurns = 0;	// tracks the overall number of times the AI has rolled.  overallNum1sRolled/overallNumOfTurns = 1s frequency or inf_FreqOf1s
	int overallNum1sRolled = 0;	// The number of 1s that have been rolled.  AI becomes more cautious and reserved due to superstition.
	int modifier_Score = 0;		// modifies the AI's confidence threshold based off of the collected score this turn
	int modifier_Opponent = 0;	// modifies the AI's confidence threshold based off of the opponent overall score
	int modifier_RollCount = 0;	// modifies the AI's confidence threshold based off of the number of times the dice has been rolled this turn
	int AI_Threshold = 0;		// the bar set to determine the AI's probability of rolling or passing
	int AI_Confidence = 0;		// the random number rolled to see if AI will roll or pass

public:
	OriginalAI() {
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

	OriginalAI(std::string name, bool _withPauses, bool _withPrint) {
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

		AI_Threshold = 0;  // 0 = 100% confident
		modifier_Score = 0;
		modifier_Opponent = 0;
		modifier_RollCount = 0;

		if (overallNumOfTurns == 0.0) inf_FreqOf1s = 0.0;
		else inf_FreqOf1s = (double) overallNum1sRolled / (double) overallNumOfTurns;

		if (inf_RollCount > 0) { // forces the choice in first turn to always be roll
			if (inf_FreqOf1s < 0.5) {
				if (turnScore >= 0 && turnScore < 6) modifier_Score = 0;				//50%
				if (turnScore >= 6 && turnScore < 11) modifier_Score = 3;
				if (turnScore >= 11 && turnScore < 14) modifier_Score = 7;
				if (turnScore >= 14 && turnScore < 17) modifier_Score = 15;
				if (turnScore >= 17 && turnScore < 20) modifier_Score = 30;
				if (turnScore >= 20) modifier_Score = 50;
			}
			else {
				if (turnScore >= 0 && turnScore < 6) modifier_Score = 7;
				if (turnScore >= 6 && turnScore < 11) modifier_Score = 19;
				if (turnScore >= 11 && turnScore < 14) modifier_Score = 30;
				if (turnScore >= 14 && turnScore < 17) modifier_Score = 50;
			}

			if (savedScore > inf_OpponentsScore + 40) modifier_Opponent = 18;			//30%
			if (savedScore > inf_OpponentsScore + 30 && savedScore <= inf_OpponentsScore + 40) modifier_Opponent = 16;
			if (savedScore > inf_OpponentsScore + 15 && savedScore <= inf_OpponentsScore + 30) modifier_Opponent = 14;
			if (savedScore > inf_OpponentsScore + 5 && savedScore <= inf_OpponentsScore + 15) modifier_Opponent = 12;
			if (savedScore > inf_OpponentsScore && savedScore <= inf_OpponentsScore + 5) modifier_Opponent = 10;
			if (savedScore == inf_OpponentsScore) modifier_Opponent = 8;
			if (savedScore < inf_OpponentsScore && savedScore >= inf_OpponentsScore - 5) modifier_Opponent = 5;
			if (savedScore < inf_OpponentsScore - 5 && savedScore >= inf_OpponentsScore - 15) modifier_Opponent = 3;
			if (savedScore < inf_OpponentsScore - 15 && savedScore >= inf_OpponentsScore - 30) modifier_Opponent = 2;
			if (savedScore < inf_OpponentsScore - 30 && savedScore >= inf_OpponentsScore - 40) modifier_Opponent = 1;
			if (savedScore < inf_OpponentsScore - 40) modifier_Opponent = 0;

			if (inf_FreqOf1s < 0.5) {
				if (inf_RollCount == 0) modifier_RollCount = 0;							//20%
				if (inf_RollCount == 1) modifier_RollCount = 1;
				if (inf_RollCount == 2) modifier_RollCount = 3;
				if (inf_RollCount == 3) modifier_RollCount = 6;
				if (inf_RollCount == 4) modifier_RollCount = 10;
				if (inf_RollCount == 5) modifier_RollCount = 15;
				if (inf_RollCount >= 6) modifier_RollCount = 20;
			}
			else {
				if (inf_RollCount == 0) modifier_RollCount = 0;
				if (inf_RollCount == 1) modifier_RollCount = 4;
				if (inf_RollCount == 2) modifier_RollCount = 10;
				if (inf_RollCount >= 3) modifier_RollCount = 20;
			}
		}

		AI_Threshold = 0 + modifier_Score + modifier_Opponent + modifier_RollCount;
		AI_Confidence = randomNumGen(0, 100);

		std::fstream fout;
		fout.open("data.txt", std::fstream::in | std::fstream::out | std::fstream::app);
		fout << (double)(inf_RollCount / 100.0f) << " " << (double)inf_FreqOf1s << " " << (double)(turnScore / 100.0f) << " " << (double)(savedScore / 100.0f) << " " << (double)(inf_OpponentsScore / 100.0f) << " " << (int)(AI_Confidence >= AI_Threshold) << "\n";
		fout.close();

		if (AI_Confidence >= AI_Threshold) {
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
		// end processing AI's decision

	}

	void additionalPrint(int player, int i, bool player1sTurn) {

		if (player == 0) {
			
			if (i == 95) std::cout << "            Num of 1s:    " << overallNum1sRolled;
			if (i == 90) std::cout << "            Num of turns: " << overallNumOfTurns;
			if (i == 85) std::cout << "            freq of 1s:   " << inf_FreqOf1s << "     switch at >= 0.5";
			if (i == 80) std::cout << "                 Num of rolls this round: " << inf_RollCount;

			if (i == 70) std::cout << "            score modifier:      " << modifier_Score;
			if (i == 70) std::cout << "       Confidence:     ";
			if (i == 70 && AI_Confidence >= AI_Threshold) std::cout << AI_Confidence;
			if (i == 65) std::cout << "            opponent modifier:   " << modifier_Opponent;
			if (i == 65 && player1sTurn) std::cout << "  -->  ";
			if (i == 65 && !player1sTurn) std::cout << "       ";
			if (i == 65) std::cout << "Threshold:  " << AI_Threshold;
			if (i == 60) std::cout << "            roll count modifier: " << modifier_RollCount;
			if (i == 60) std::cout << "       Confidence:     ";
			if (i == 60 && AI_Confidence < AI_Threshold) std::cout << AI_Confidence;
		}

		if (player == 1) {
			
			if (i == 45) std::cout << "            Num of 1s:    " << overallNum1sRolled;
			if (i == 40) std::cout << "            Num of turns: " << overallNumOfTurns;
			if (i == 35) std::cout << "            freq of 1s:   " << inf_FreqOf1s << "     switch at >= 0.5";
			if (i == 30) std::cout << "                 Num of rolls this round: " << inf_RollCount;

			if (i == 20) std::cout << "            score modifier:      " << modifier_Score;
			if (i == 20) std::cout << "       Confidence:     ";
			if (i == 20 && AI_Confidence >= AI_Threshold) std::cout << AI_Confidence;
			if (i == 15) std::cout << "            opponent modifier:   " << modifier_Opponent;
			if (i == 15 && !player1sTurn) std::cout << "  -->  ";
			if (i == 15 && player1sTurn) std::cout << "       ";
			if (i == 15) std::cout << "Threshold:  " << AI_Threshold;
			if (i == 10) std::cout << "            roll count modifier: " << modifier_RollCount;
			if (i == 10) std::cout << "       Confidence:     ";
			if (i == 10 && AI_Confidence < AI_Threshold) std::cout << AI_Confidence;
		}

	}

};

#endif