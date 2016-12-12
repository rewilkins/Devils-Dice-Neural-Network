#include <iostream>
#include <fstream>
#include "DevilsDiceGame.h"

int main() {

	bool invalid = true;
	char mode = false;
	bool withPauses = false;
	bool withPrint = false;
	bool capGame = false;
	int gameCap = 0;
	DevilsDiceGame game;

	while (invalid) {
		system("cls");
		std::cout << "Load Demo Mode?  [y/n] ";
		std::cin >> mode;

		char choise = false;
		std::cout << "Run Game With Pauses?  [y/n] ";
		std::cin >> choise;
		if (choise == 'y' || choise == 'Y') withPauses = true;
		else withPauses = false;

		std::cout << "Run Game With Printing?  [y/n] ";
		std::cin >> choise;
		if (choise == 'y' || choise == 'Y') withPrint = true;
		else withPrint = false;

		std::cout << "Cap the Total Game Count?  [y/n] ";
		std::cin >> choise;
		if (choise == 'y' || choise == 'Y') capGame = true;
		else capGame = false;

		if (capGame) {
			std::cout << "Specify The Max Num of Games: ";
			std::cin >> gameCap;
		}

		if (mode == 'y' || mode == 'Y') {
			invalid = false;
			game.setDemoMode(true, withPauses, withPrint, capGame, gameCap);
			game.run();
		}
		if (mode == 'n' || mode == 'N') {
			invalid = false;
			game.setDemoMode(false, withPauses, withPrint, capGame, gameCap);
			game.run();
		}
	}

}