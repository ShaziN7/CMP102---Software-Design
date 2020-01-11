#include "Display.h"


Display::Display()
{
}

Display::~Display()
{
}

// The title screen
void Display::initialDisplay()
{
	system("CLS");

	std::cout << "                             >====>           >>       >======>     >===>>=====>   >=>>=>   " << std::endl;
	std::cout << "                             >=>   >=>       >>=>      >=>    >=>        >=>     >=>    >=> " << std::endl;
	std::cout << "                             >=>    >=>     >> >=>     >=>    >=>        >=>      >=>       " << std::endl;
	std::cout << "                             >=>    >=>    >=>  >=>    >> >==>           >=>        >=>     " << std::endl;
	std::cout << "                             >=>    >=>   >=====>>=>   >=>  >=>          >=>           >=>  " << std::endl;
	std::cout << "                             >=>   >=>   >=>      >=>  >=>    >=>        >=>     >=>    >=> " << std::endl;
	std::cout << "                             >====>     >=>        >=> >=>      >=>      >=>       >=>>=>   " << std::endl << std::endl << std::endl << std::endl << std::endl;



	std::cout << "                                             ,-\'\"\"\"`-,         ,-----. " << std::endl;
	std::cout << "                                           ,\' \\ _|_ / `.       | 501 |      " << std::endl;
	std::cout << "                                          /`.,\'\\ | /`.,\'\\      `-----'       |          " << std::endl;
	std::cout << "                                         (  /`. \\|/ ,\'\\  )                |  H             " << std::endl;
	std::cout << "                                         |--|--;=@=:--|--|             |  H  U             " << std::endl;
	std::cout << "                                         (  \\,\' /|\\ `./  )             H  U  |             " << std::endl;
	std::cout << "                                          \\,\'`./ | \\,\'`./              U  | (|)            " << std::endl;
	std::cout << "                                           `. / \"\"\" \\ ,\'               | (|) " << std::endl;
	std::cout << "                                             \'-._|_,-`                (|) " << std::endl << std::endl << std::endl << std::endl << std::endl;
}

// The main screen for the Interactive Game
void Display::displayScreen(Player player1, Player player2, int gameCounter, int setCounter)
{
	system("CLS");

	std::cout << "                                            " << "*   " << "DARTS WORLD CHAMPIONSHIPS" << "   *" << std::endl;
	std::cout << "                                            *                               *" << std::endl;
	std::cout << "                                            *          " << "Game: " << gameCounter << " / 5" << "          *" << std::endl;
	std::cout << "                                            *          " << "Set: " << setCounter << " / 13" << "          *" << std::endl;
	std::cout << "                                            * * * * * * * * * * * * * * * * *" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "                            " << player1.getName() << "                            " << "vs" << "                            " << player2.getName() << std::endl;
	std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "                    " << "Current Points: " << player1.getPoints() << "                     " << "|" << "                     " << "Current Points: " << player2.getPoints() << std::endl;
	std::cout << "                      " << "Total Throws: " << player1.getThrowCounter() << "                       " << "|" << "                       " << "Total Throws: " << player2.getThrowCounter() << std::endl;
	std::cout << "                       " << "Total Bulls: " << player1.getBullCounter() << "                       " << "|" << "                       " << "Total Bulls: " << player2.getBullCounter() << std::endl;
	std::cout << "                        " << "Games Won: " << player1.getGamesWon() << "                        " << "|" << "                        " << "Games Won: " << player2.getGamesWon() << std::endl;
	std::cout << "                        " << "Sets Won: " << player1.getSetsWon() << "                         " << "|" << "                         " << "Sets Won: " << player2.getSetsWon() << std::endl;
	std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl << std::endl;
	std::cout << std::endl << std::endl << std::endl << std::endl;
}

// The end screen for the Interactive Game
void Display::endScreen(Player player1, Player player2, int gameCounter, int setCounter)
{
	system("CLS");

	std::cout << "                                            " << "*   " << "DARTS WORLD CHAMPIONSHIPS" << "   *" << std::endl;
	std::cout << "                                            *                               *" << std::endl;
	std::cout << "                                            *          " << "Game: " << gameCounter << " / 5" << "          *" << std::endl;
	std::cout << "                                            *          " << "Set: " << setCounter << " / 13" << "           *" << std::endl;
	std::cout << "                                            * * * * * * * * * * * * * * * * *" << std::endl;
	std::cout << std::endl << std::endl;
	
	if (player1.getSetsWon() == 7)
	{
		std::cout << player1.getName() << " has won the Darts World Championships with " << player1.getSetsWon() << " sets to " << player2.getName() << "'s " << player2.getSetsWon() << " sets." << std::endl << std::endl;
		std::cout << "Thank you for playing!";
		std::cout << std::endl << std::endl << std::endl;
	}

	else if (player2.getSetsWon() == 7)
	{
		std::cout << player2.getName() << " has won the Darts World Championships with " << player2.getSetsWon() << " sets to " << player1.getName() << "'s " << player1.getSetsWon() << " sets." << std::endl << std::endl;
		std::cout << "Thank you for playing!";
		std::cout << std::endl << std::endl << std::endl;
	}
}

// The end screen for the Simulation
void Display::simulationResults(Player player1, Player player2, int scores[2][8], int simNum)
{
	system("CLS");
	std::cout << "The results of your simulation are: " << std::endl << std::endl << std::endl;
	std::cout << player1.getName() << "  :  " << player2.getName() << "    |     " << "Frequency" << std::endl;
	std::cout << "---------------------------------------" << std::endl;
	std::cout << " 7" << "   :   " << "6" << "     |     " << scores[1][6] << " / " << simNum << " -> " << (static_cast<float>(scores[1][6]) / simNum) * 100 << "%" << std::endl;
	std::cout << " 7" << "   :   " << "5" << "     |     " << scores[1][5] << " / " << simNum << " -> " << (static_cast<float>(scores[1][5]) / simNum) * 100 << "%" << std::endl;
	std::cout << " 7" << "   :   " << "4" << "     |     " << scores[1][4] << " / " << simNum << " -> " << (static_cast<float>(scores[1][4]) / simNum) * 100 << "%" << std::endl;
	std::cout << " 7" << "   :   " << "3" << "     |     " << scores[1][3] << " / " << simNum << " -> " << (static_cast<float>(scores[1][3]) / simNum) * 100 << "%" << std::endl;
	std::cout << " 7" << "   :   " << "2" << "     |     " << scores[1][2] << " / " << simNum << " -> " << (static_cast<float>(scores[1][2]) / simNum) * 100 << "%" << std::endl;
	std::cout << " 7" << "   :   " << "1" << "     |     " << scores[1][1] << " / " << simNum << " -> " << (static_cast<float>(scores[1][1]) / simNum) * 100 << "%" << std::endl;
	std::cout << " 7" << "   :   " << "0" << "     |     " << scores[1][0] << " / " << simNum << " -> " << (static_cast<float>(scores[1][0]) / simNum) * 100 << "%" << std::endl;
	std::cout << " 6" << "   :   " << "7" << "     |     " << scores[0][6] << " / " << simNum << " -> " << (static_cast<float>(scores[0][6]) / simNum) * 100 << "%" << std::endl;
	std::cout << " 5" << "   :   " << "7" << "     |     " << scores[0][5] << " / " << simNum << " -> " << (static_cast<float>(scores[0][5]) / simNum) * 100 << "%" << std::endl;
	std::cout << " 4" << "   :   " << "7" << "     |     " << scores[0][4] << " / " << simNum << " -> " << (static_cast<float>(scores[0][4]) / simNum) * 100 << "%" << std::endl;
	std::cout << " 3" << "   :   " << "7" << "     |     " << scores[0][3] << " / " << simNum << " -> " << (static_cast<float>(scores[0][3]) / simNum) * 100 << "%" << std::endl;
	std::cout << " 2" << "   :   " << "7" << "     |     " << scores[0][2] << " / " << simNum << " -> " << (static_cast<float>(scores[0][2]) / simNum) * 100 << "%" << std::endl;
	std::cout << " 1" << "   :   " << "7" << "     |     " << scores[0][1] << " / " << simNum << " -> " << (static_cast<float>(scores[0][1]) / simNum) * 100 << "%" << std::endl;
	std::cout << " 0" << "   :   " << "7" << "     |     " << scores[0][0] << " / " << simNum << " -> " << (static_cast<float>(scores[0][0]) / simNum) * 100 << "%" << std::endl;
	std::cout << std::endl << std::endl << std::endl;
}