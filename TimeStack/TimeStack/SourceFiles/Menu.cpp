#include "../HeaderFiles/precompiler.h"

void startWindow()
{
    int screen;

    showMenu();

    std::cin >> screen;

    if (screen <= 11 && screen > 0)
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
            createTestForEvent();
            break;
        case 7:
            system("cls");
            searchEvents();
            break;
        case 8:
            system("cls");
            exportEvents();
            break;
        case 9:
            system("cls");
            takeTest();
            break;
        case 10:
            system("cls");
            gameOn = false;
            break;
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
    const char* logo[] = {
        " _________  ___  _____ ______   _______   ________  _________  ________  ________  ___  __     ",
        " \\___   ___\\\\  \\|\\   _ \\  _   \\|\\  ___ \\ |\\   ____\\|\\___   ___\\\\   __  \\|\\   ____\\|\\  \\|\\  \\   ",
        "\\|___ \\  \\_\\ \\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|\\ \\  \\___|\\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\___|\\ \\  \\/  /|_ ",
        "     \\ \\  \\ \\ \\  \\ \\  \\\\|__| \\  \\ \\  \\_|/_\\ \\_____  \\   \\ \\  \\ \\ \\   __  \\ \\  \\    \\ \\   ___  \\ ",
        "      \\ \\  \\ \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\|____|\\  \\   \\ \\  \\ \\ \\  \\ \\  \\ \\  \\____\\ \\  \\\\ \\  \\|",
        "       \\ \\__\\ \\ \\__\\ \\__\\    \\ \\__\\ \\_______\\____\\_\\  \\   \\ \\__\\ \\ \\__\\ \\__\\ \\_______\\ \\__\\\\ \\__\\",
        "        \\|__|  \\|__|\\|__|     \\|__|\\|_______|\\_________\\   \\|__|  \\|__|\\|__|\\|_______|\\|__| \\|__|"
    };

    // Determine content width based on logo
    int maxLogoWidth = 0;
    for (const char* line : logo) {
        int len = strlen(line);
        if (len > maxLogoWidth) maxLogoWidth = len;
    }

    int sidePadding = 4;
    int contentWidth = maxLogoWidth + sidePadding * 2;

    auto pad = [](int count) { for (int i = 0; i < count; ++i) std::cout << ' '; };

    // Top border
    std::cout << "+" << std::string(contentWidth, '_') << "+\n";
    std::cout << "|"; pad(contentWidth); std::cout << "|\n";

    // Logo
    for (const char* line : logo) {
        int len = strlen(line);
        int space = contentWidth - len;
        int left = space / 2;
        int right = space - left;

        std::cout << "|";
        pad(left);
        std::cout << line;
        pad(right);
        std::cout << "|\n";
    }

    // Space below logo
    std::cout << "|"; pad(contentWidth); std::cout << "|\n";
    std::cout << "+" << std::string(contentWidth, '_') << "+\n";
    std::cout << "|"; pad(contentWidth); std::cout << "|\n";

    // Menu items
    const char* menu[] = {
        "[1]  Add an event",        "[2]  Edit an event",        "[3]  Delete an event",
        "[4]  List all events",     "[5]  Sort events",          "[6]  Create test for event",
        "[7]  Search events",       "[8]  Export events",        "[9] Take test",
        "[10] Exit"
    };

    const int columns = 3;
    const int itemCount = sizeof(menu) / sizeof(menu[0]);
    const int itemWidth = contentWidth / columns;

    for (int i = 0; i < itemCount; i += columns) {
        std::cout << "|";
        for (int j = 0; j < columns; ++j) {
            int idx = i + j;
            if (idx < itemCount) {
                int len = strlen(menu[idx]);
                std::cout << " " << menu[idx];
                pad(itemWidth - len - 1);
            }
            else {
                pad(itemWidth);
            }
        }
        std::cout << "|\n";
        std::cout << "|"; pad(contentWidth); std::cout << "|\n";
    }

    // Bottom border
    std::cout << "+" << std::string(contentWidth, '_') << "+\n";

    std::cout << "\nSelect an option by number: ";
}
