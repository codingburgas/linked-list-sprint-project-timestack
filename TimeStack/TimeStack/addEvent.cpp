#include "precompiler.h"
#include "../stLib/entries.cpp"

bool isValidDate(const std::string& date) {
    std::istringstream iss(date);
    int day, month, year;

    if (!(iss >> day >> month >> year)) return false;

    if (day < 1 || day > 31) return false;
    if (month < 1 || month > 12) return false;
    if (year > 2100) return false;

    return true;
}

void addEvent() {
    Event newEvent;

    int day, month, year;

    do {
        std::cout << "Enter date (DD MM YYYY): ";
        std::cin >> day >> month >> year;

        if (day < 1 || day > 31 || month < 1 || month > 12 || year > 2100) {
            std::cout << "Invalid date format! Please enter again.\n";
        }
        else {
            newEvent.date = std::to_string(day) + " " + std::to_string(month) + " " + std::to_string(year);
        }

    } while (day < 1 || day > 31 || month < 1 || month > 12 || year > 2100);

    std::cin.ignore();  // Clear buffer before reading text
    std::cout << "Enter event name: ";
    std::getline(std::cin, newEvent.name);

    std::cout << "Enter event description: ";
    std::getline(std::cin, newEvent.description);

    system("cls");
    events.push_back(newEvent);
    saveEvents();
}

void saveEvents() {
    std::ofstream file(filename, std::ios::app);  // Append mode instead of overwriting
    if (!file) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    // Properly save the date as separate values
    std::istringstream dateStream(events.back().date);
    int day, month, year;
    dateStream >> day >> month >> year;

    file << day << " " << month << " " << year << " - " << events.back().name;

    if (!events.back().description.empty()) {
        file << " - " << events.back().description;
    }

    file << "\n";
    file.close();
}
