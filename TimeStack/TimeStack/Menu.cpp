#include "precompiler.h"

void startWindow()
{

	int screen;

	showMenu();

	std::cin >> screen;

	if (screen <= 6 && screen > 0)
	{
		switch (screen)
		{

		case 1:

			system("cls");
			addEvent();

			break;

		case 2:

			system("cls");
			editEvent();

			break;

		case 3:

			system("cls");
			deleteEvent();

			break;

		case 4:

			system("cls");
			listEvents();

			break;

		case 5:

			system("cls");
			sortEvents();

			break;

		case 6:

			system("cls");
			gameOn = false;

		default:
			system("cls");

			gameOn = false;
		}
	}
	else {

		system("cls");
		std::cout << "Invalid input";
		gameOn = false;

	}
}


void showMenu()
{

	std::cout << " _________  ___  _____ ______   _______   ________  _________  ________  ________  ___  __        " << std::endl;
    std::cout << " \\___   ___\\\\  \\|\\   _ \\  _   \\|\\  ___ \\ |\\   ____\\|\\___   ___\\\\   __  \\|\\   ____\\|\\  \\|\\  \\      " << std::endl;
    std::cout << "\\|___ \\  \\_\\ \\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|\\ \\  \\___|\\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\___|\\ \\  \\/  /|_    " << std::endl;
    std::cout << "     \\ \\  \\ \\ \\  \\ \\  \\\\|__| \\  \\ \\  \\_|/_\\ \\_____  \\   \\ \\  \\ \\ \\   __  \\ \\  \\    \\ \\   ___  \\   " << std::endl;
    std::cout << "      \\ \\  \\ \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\|____|\\  \\   \\ \\  \\ \\ \\  \\ \\  \\ \\  \\____\\ \\  \\\\ \\  \\  " << std::endl;
    std::cout << "       \\ \\__\\ \\ \\__\\ \\__\\    \\ \\__\\ \\_______\\____\\_\\  \\   \\ \\__\\ \\ \\__\\ \\__\\ \\_______\\ \\__\\\\ \\__\\ " << std::endl;
    std::cout << "        \\|__|  \\|__|\\|__|     \\|__|\\|_______|\\_________\\   \\|__|  \\|__|\\|__|\\|_______|\\|__| \\|__| " << std::endl;
    std::cout << "                                             \\|_________|                                         " << std::endl;

	std::cout << std::string(100, '_') << "\n\n\n";
	

	std::cout << "Choose option." << std::endl;
	std::cout << std::endl;
	std::cout << "1. Add an event" << std::endl;
	std::cout << "2. Edit an event" << std::endl;
	std::cout << "3. Delete an event" << std::endl;
	std::cout << "4. List events" << std::endl;
	std::cout << "5. Sort events" << std::endl;
	std::cout << "6. Exit" << std::endl;
}