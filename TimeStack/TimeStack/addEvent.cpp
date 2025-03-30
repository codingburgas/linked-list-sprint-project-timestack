#include "precompiler.h"
#include "../stLib/entries.cpp"

void addEvent() {
    Event newEvent;
    std::cout << "Enter date (YYYY-MM-DD): ";
    std::cin >> newEvent.date;
    std::cin.ignore();
    std::cout << "Enter event name: ";
    std::getline(std::cin, newEvent.name);
    events.push_back(newEvent);
    saveEvents();
}


void saveEvents() {
    std::ofstream file(filename, std::ios::trunc);  // Use std::ios::trunc to overwrite the file
    if (!file) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    // Print to console for debugging
    std::cout << "Saving events:\n";
    for (const Event& event : events) {
        std::cout << event.date << " " << event.name << "\n";  // Debugging output
        file << event.date << " " << event.name << "\n";
    }
    file.close();
}