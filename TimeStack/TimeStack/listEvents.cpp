#include "precompiler.h"

void listEvents() {
    for (const auto& event : events) {
        std::cout << event.date << " - " << event.name;

        if (!event.description.empty()) {
            std::cout << " - " << event.description;
        }

        std::cout << "\n";
    }
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first == std::string::npos || last == std::string::npos) {
        return "";  // String is empty
    }
    return str.substr(first, last - first + 1);
}

void deleteEvent() {
    std::string day, month, year, eventName;
    std::cout << "Enter date of event to delete (DD MM YYYY): ";
    std::cin >> day >> month >> year;
    std::cin.ignore();  // Clear newline from input buffer
    std::cout << "Enter the name of the event: ";
    std::getline(std::cin, eventName);

    // Format the date properly
    std::string fullDate = trim(day) + " " + trim(month) + " " + trim(year);
    eventName = trim(eventName);

    bool found = false;
    auto it = events.begin();

    while (it != events.end()) {
        if (it->date == fullDate && it->name == eventName) {
            it = events.erase(it); // Correctly delete the event
            found = true;
        }
        else {
            ++it;
        }
    }

    if (found) {
        saveEvents(); // Save the updated list to the file
        std::cout << "Event deleted successfully.\n";
    }
    else {
        std::cout << "Event not found.\n";
    }
}
