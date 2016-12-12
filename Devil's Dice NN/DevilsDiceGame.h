#pragma once
#ifndef DEVILS_DICE_GAME
#define DEVILS_DICE_GAME

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <random>
#include <memory>
#include "Player.h"
#include "Human.h"
#include "OriginalAI.h"
#include "OptimalAI.h"
#include "RandomAI.h"
#include "OriginalNN.h"
#include "OptimalNN.h"
#include "RandomNN.h"
#include "HybridNN.h"

class DevilsDiceGame {

private:

	bool demoMode = false;

	bool gameRunning = true;
	bool player1sTurn = true;
	char playerAction;
	bool invalidInput = false;

	bool reset = false;
	bool quit = false;
	bool winner = false;

	bool withPauses = false;
	bool withPrint = false;
	bool capGame = false;
	int gameCap = 0;

	int gameCount = 0;
	int turnCount = 0;

	std::vector<Player*> players;

	int dice = 0;

	void intro() {
		std::cout << std::endl;
		std::cout << "            Welcome to Devil's Dice!" << std::endl;
		std::cout << std::endl;
		std::cout << "                        Role the dice to obtain points" << std::endl;
		std::cout << "                        Pass when you feel your luck slipping away and bank your collected points" << std::endl;
		std::cout << "                        Roling a \"1\" will make you loose your collected points for the round" << std::endl;
		std::cout << "                        First to 100 points wins!" << std::endl;
		std::cout << std::endl;
		system("pause");
	}

	void setup() {
		std::string name;

		players.clear();

		gameRunning = true;
		player1sTurn = true;
		invalidInput = false;

		reset = false;
		quit = false;
		winner = false;

		if (demoMode == true) {
			players.push_back(new OptimalNN("comp19", withPauses, withPrint));
			players.push_back(new OptimalAI("comp20", withPauses, withPrint));
		}
		if (demoMode == false) {
			invalidInput = true;
			while (invalidInput == true) {

				clearConsole();

				std::cout << "         ** Plr 1               Plr 2" << std::endl;
				std::cout << "          -----        <--        -----" << std::endl;
				std::cout << std::endl;
				std::cout << "Is player 1 Human or Computer? [h/c] ";
				std::cin >> playerAction;

				if (playerAction == 'h' || playerAction == 'H') {

					invalidInput = false;
					std::cout << "What is player 1's name? ";
					std::cin >> name;
					players.push_back(new Human(name, withPauses, withPrint));
					//player1.reset(new Human(name));

				}
				if (playerAction == 'c' || playerAction == 'C') {

					invalidInput = false;
					std::cout << "What is player 1's name? ";
					std::cin >> name;
					players.push_back(new OriginalAI(name, withPauses, withPrint));
					//player1.reset(new OriginalAI(name));

				}
				if (invalidInput == true) {
					std::cout << "   Invalid Input" << std::endl;
					if(withPauses) pause(2);
				}

			}

			invalidInput = true;
			while (invalidInput == true) {

				clearConsole();

				std::cout << "            Plr 1               Plr 2 **" << std::endl;
				std::cout << "          -----        -->        -----" << std::endl;
				std::cout << std::endl;
				std::cout << "Is player 2 Human or Computer? [h/c] ";
				std::cin >> playerAction;

				if (playerAction == 'h' || playerAction == 'H') {

					invalidInput = false;
					std::cout << "What is player 2's name? ";
					std::cin >> name;
					players.push_back(new Human(name, withPauses, withPrint));
					//player2.reset(new Human(name));

				}
				if (playerAction == 'c' || playerAction == 'C') {

					invalidInput = false;
					std::cout << "What is player 2's name? ";
					std::cin >> name;
					players.push_back(new OriginalNN(name, withPauses, withPrint));
					//player2.reset(new OriginalAI(name));

				}
				if (invalidInput == true) {
					std::cout << "   Invalid Input" << std::endl;
					if (withPauses) pause(2);
				}

			}
		}

	}

	void pause(int seconds)
	{
		time_t start, current;
		time(&start);
		do
		{
			time(&current);
		} while ((current - start) < seconds);
	}

	void clearConsole() {
		system("cls");
		//std::cout << std::string(30, '\n');
	}

	void print() {
		clearConsole();

		std::cout << "                  Devil's  Dice" << std::endl;
		if (player1sTurn == true) {
			std::cout << "         ** Plr 1               Plr 2" << std::endl;
			std::cout << "          -----        <--        -----" << std::endl;
		}
		if (player1sTurn == false) {
			std::cout << "            Plr 1               Plr 2 **" << std::endl;
			std::cout << "          -----        -->        -----" << std::endl;
		}


		for (int i = 100; i >= 0; i -= 5) {

			if (players[0]->getSavedScore() >= i && players[0]->getSavedScore() < i + 5) std::cout << std::setw(3) << std::right << players[0]->getSavedScore();
			else std::cout << "   ";
			if (players[0]->getTurnScore() + players[0]->getSavedScore() >= i && players[0]->getTurnScore() + players[0]->getSavedScore() < i + 5) std::cout << std::setw(3) << std::right << players[0]->getTurnScore() + players[0]->getSavedScore() << " >";
			else std::cout << "     ";

			std::cout << "--" << std::left << std::setw(3) << i;

			if (i == 90) std::cout << "          die          ";
			else if (i == 85) std::cout << "          ---          ";
			else if (i == 80) std::cout << "         | " << dice << " |         ";
			else if (i == 75) std::cout << "          ---          ";

			else if (i == 50) std::cout << "       r - Roll        ";
			else if (i == 45) std::cout << "       p - Pass        ";

			else if (i == 35) std::cout << "       R - Reset       ";
			else if (i == 30) std::cout << "       Q - Quit        ";

			else std::cout << "                       ";

			std::cout << std::right << std::setw(3) << i << "--";

			if (players[1]->getTurnScore() + players[1]->getSavedScore() >= i && players[1]->getTurnScore() + players[1]->getSavedScore() < i + 5) std::cout << "< " << std::setw(3) << std::left << players[1]->getTurnScore() + players[1]->getSavedScore();
			else std::cout << "     ";
			if (players[1]->getSavedScore() >= i && players[1]->getSavedScore() < i + 5) std::cout << std::setw(3) << std::left << players[1]->getSavedScore();
			else std::cout << "   ";

			if (i == 100) std::cout << "      Player 1:            W: " << players[0]->getWinCount() << " L: " << players[0]->getLossCount();
			if (i == 50) std::cout << "      Player 2:            W: " << players[1]->getWinCount() << " L: " << players[1]->getLossCount();

			if (withPrint) players[0]->additionalPrint(0, i, player1sTurn);
			if (withPrint) players[1]->additionalPrint(1, i, player1sTurn);

			std::cout << std::endl;

		}

	}

	int rollDice() {
		std::random_device rd;
		std::mt19937 e2(rd());
		std::uniform_real_distribution<> dist(1, 6 + 1);
		return dist(e2);
	}

	void roll(Player *player) {
		dice = rollDice();
		if (dice > 1) {
			player->setTurnScore(player->getTurnScore() + dice);
			checkForWin(player);
			if (!winner) {
				if (withPrint) print();
			}
		}
		else {
			player->setTurnScore(0);
			if (withPrint) print();
			if (withPauses) pause(2);
			dice = 0;
			player1sTurn = !player1sTurn;
			if (withPrint) print();
		}
	}

	void pass(Player *player) {
		player->setSavedScore(player->getSavedScore() + player->getTurnScore());
		player->setTurnScore(0);
		if (withPrint) print();
		if (withPauses) pause(2);
		dice = 0;
		player1sTurn = !player1sTurn;
		if (withPrint) print();
	}

	void resetGame() {
		invalidInput = true;
		while (invalidInput == true) {
			clearConsole();

			std::cout << "      Are you sure you want to Reset? [y/n] ";
			std::cin >> playerAction;
			if (playerAction == 'y' || playerAction == 'Y') {
				invalidInput = false;
				reset = true;
				gameRunning = false;
			}

			if (playerAction == 'n' || playerAction == 'N') {
				invalidInput = false;
				if (withPrint) print();
			}

			if (invalidInput == true) {
				std::cout << "   Invalid Input" << std::endl;
				if (withPauses) pause(2);
			}

		}
	}

	void quitGame() {
		invalidInput = true;
		while (invalidInput == true) {
			clearConsole();

			std::cout << "      Are you sure you want to Quit? [y/n] ";
			std::cin >> playerAction;
			if (playerAction == 'y' || playerAction == 'Y') {
				invalidInput = false;
				quit = true;
				gameRunning = false;
			}
			if (playerAction == 'n' || playerAction == 'N') {
				invalidInput = false;
				if (withPrint) print();
			}
			if (invalidInput == true) {
				std::cout << "   Invalid Input" << std::endl;
				if (withPauses) pause(2);
			}

		}
	}

	void checkForWin(Player *player) {
		if (player->getSavedScore() + player->getTurnScore() >= 100) {
			player->setSavedScore(player->getSavedScore() + player->getTurnScore());
			player->setTurnScore(0);
			if (withPrint) print();
			if (withPauses) pause(2);
			dice = 0;
			if (withPrint) print();
			winner = true;
			gameRunning = false;
		}
	}

	void postGame(Player *triggerPlayer, Player *otherPlayer) {

		gameCount++;
		if (!withPrint) std::cout << gameCount << " : ";
		if (!withPrint) std::cout << turnCount << std::endl;

		if (winner) {
			triggerPlayer->setWinCount(triggerPlayer->getWinCount() + 1);
			otherPlayer->setLossCount(otherPlayer->getLossCount() + 1);
			if (withPrint) clearConsole();
			if (withPrint) std::cout << "   " << triggerPlayer->getPlayerName() << " Wins !!!" << std::endl << std::endl;
			if (withPauses) pause(2);

			if (demoMode == true) reset = true;
			if (demoMode == false) {
				invalidInput = true;
				while (invalidInput == true) {

					std::cout << "Play again? [y/n] ";
					std::cin >> playerAction;
					if (playerAction == 'y' || playerAction == 'Y') {
						invalidInput = false;
						reset = true;
					}
					if (playerAction == 'n' || playerAction == 'N') {
						invalidInput = false;
						quit = true;
					}
					if (invalidInput == true) {
						std::cout << "   Invalid Input" << std::endl;
						if (withPauses) pause(2);
					}

				}
			}

		}


		if (!withPrint) std::cout << "\t" << triggerPlayer->getPlayerName() << " - W: " << triggerPlayer->getWinCount() << " | L: " << triggerPlayer->getLossCount() << std::endl;
		if (!withPrint) std::cout << "\t" << otherPlayer->getPlayerName() << " - W: " << otherPlayer->getWinCount() << " | L: " << otherPlayer->getLossCount() << std::endl;


		bool systemQuit = false;
		if (capGame == true && gameCount >= gameCap) {
			reset = false;
			systemQuit = true;
		}
		

		if (reset) {
			if(!winner) triggerPlayer->setLossCount(triggerPlayer->getLossCount() + 1);
			if (withPrint) clearConsole();
			if (withPrint) std::cout << "   Game Reseting" << std::endl << std::endl;
			if (withPauses) pause(2);
		}
		if (quit || systemQuit) {
			if (!withPrint) pause(3);
			if (!winner && !systemQuit) triggerPlayer->setLossCount(triggerPlayer->getLossCount() + 1);
			clearConsole();
			std::cout << "   Game Ended" << std::endl << std::endl;
			pause(2);
		}
		if (players.size() > 0) {
			players[0]->saveScore();
			players[1]->saveScore();
		}

	}

public:
	DevilsDiceGame() {
		
	}

	void setDemoMode(bool mode, bool _withPauses, bool _withPrint, bool _capGame, int _gameCap) {
		demoMode = mode;
		withPauses = _withPauses;
		withPrint = _withPrint;
		capGame = _capGame;
		gameCap = _gameCap;
	}

	void run() {

		intro();

		reset = true;
		while (reset) { // reset loop
			reset = false;

			setup();
			if (withPrint) print();

			gameRunning = true;
			while (gameRunning) { // game loop

				turnCount++;
				switch (player1sTurn) {
				case true:
					playerAction = players[0]->getAction(players[1]->getSavedScore());
					if (playerAction == 'r') roll(players[0]);
					if (playerAction == 'p') pass(players[0]);
					break;
				case false:
					playerAction = players[1]->getAction(players[0]->getSavedScore());
					if (playerAction == 'r') roll(players[1]);
					if (playerAction == 'p') pass(players[1]);
					break;
				}
				if (playerAction == 'R') resetGame();
				if (playerAction == 'Q') quitGame();

			} // end game loop

			if (player1sTurn) postGame(players[0], players[1]);
			if (!player1sTurn) postGame(players[1], players[0]);

		} // end reset loop

	}

};

#endif 