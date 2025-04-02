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

    do {
        std::cout << "Enter date (DD MM YYYY): ";
        std::cin.ignore();
        std::getline(std::cin, newEvent.date);

        if (!isValidDate(newEvent.date)) {
            std::cout << "Invalid date format! Please enter again.\n";
        }
    } while (!isValidDate(newEvent.date));

    std::cout << "Enter event name: ";
    std::getline(std::cin, newEvent.name);

    std::cout << "Enter event description: "; // Add this line
    std::getline(std::cin, newEvent.description); // Add this line

    system("cls");
    events.push_back(newEvent);
    saveEvents();
}

void saveEvents() {
    std::ofstream file(filename, std::ios::app);  // Append mode instead of truncating
    if (!file) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    file << events.back().date << " " << events.back().name << " " << events.back().description << "\n";  // Append the new event with description
    file.close();
}
