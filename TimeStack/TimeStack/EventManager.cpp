#include "precompiler.h"

bool isValidDate(int day, int month, int year) {
    if (day < 1 || day > 31) return false;
    if (month < 1 || month > 12) return false;
    if (year > 2100) return false;
    return true;
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first == std::string::npos || last == std::string::npos) {
        return "";
    }
    return str.substr(first, last - first + 1);
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

    std::cin.ignore();
    std::cout << "Enter event name: ";
    std::getline(std::cin, newEvent.name);

    std::cout << "Enter event description: ";
    std::getline(std::cin, newEvent.description);

    system("cls");
    events.push_back(newEvent);
    saveEvents();
}

void deleteEvent() {
    std::string day, month, year, eventName;
    std::cout << "Enter date of event to delete (DD MM YYYY): ";
    std::cin >> day >> month >> year;
    std::cin.ignore();
    std::cout << "Enter the name of the event: ";
    std::getline(std::cin, eventName);

    std::string fullDate = trim(day) + " " + trim(month) + " " + trim(year);
    eventName = trim(eventName);

    bool found = false;
    auto it = events.begin();
    while (it != events.end()) {
        if (it->date == fullDate && it->name == eventName) {
            it = events.erase(it);
            found = true;
        }
        else {
            ++it;
        }
    }

    if (found) {
        saveEvents();
        std::cout << "Event deleted successfully.\n";
    }
    else {
        std::cout << "Event not found.\n";
    }
}

void listEvents() {
    for (const auto& event : events) {
        std::cout << event.date << " - " << event.name;
        if (!event.description.empty()) {
            std::cout << " - " << event.description;
        }
        std::cout << "\n";
    }
}

void saveEvents() {
    std::ofstream file(filename);
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
