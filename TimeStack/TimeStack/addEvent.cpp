#include "precompiler.h"
#include "../stLib/entries.cpp"

bool isValidDate(int day, int month, int year) {
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

        if (!isValidDate(day, month, year)) {
            std::cout << "Invalid date format! Please enter again.\n";
        }
        else {
            newEvent.date = std::to_string(day) + " " + std::to_string(month) + " " + std::to_string(year);
        }

    } while (!isValidDate(day, month, year));

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
    std::ofstream file(filename);  // Overwrite mode to ensure deleted events are removed
    if (!file) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    for (const auto& event : events) {
        file << event.date << " - " << event.name;
        if (!event.description.empty()) {
            file << " - " << event.description;
        }
        file << "\n";
    }

    file.close();
}