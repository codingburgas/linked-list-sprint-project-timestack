#include "precompiler.h"
#include "../stLib/entries.cpp"

void addEvent() {
    Event newEvent;
    std::cout << "Enter date (YYYY-MM-DD): ";
    std::cin >> newEvent.date;
    std::cin.ignore();
    std::cout << "Enter event name: ";
    std::getline(std::cin, newEvent.name);
    system("cls");
    events.push_back(newEvent);
    saveEvents();  // Save after adding
}

void saveEvents() {
    std::ofstream file(filename, std::ios::app);  // Append mode instead of truncating
    if (!file) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    file << events.back().date << " " << events.back().name << "\n";  // Append only the new event
    file.close();
}
