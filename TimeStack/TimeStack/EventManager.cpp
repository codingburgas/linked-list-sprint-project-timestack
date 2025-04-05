#include "precompiler.h"

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first == std::string::npos || last == std::string::npos) return "";
    return str.substr(first, last - first + 1);
}

bool isValidDate(int day, int month, int year) {
    if (day < 1 || day > 31) return false;
    if (month < 1 || month > 12) return false;
    if (year > 2100) return false;
    return true;
}

void saveEvents() {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    Event* current = head;
    while (current) {
        file << current->date << " - " << current->name;
        if (!current->description.empty()) {
            file << " - " << current->description;
        }
        file << "\n";
        current = current->next;
    }

    file.close();
}

void addEvent() {
    Event* newEvent = new Event;
    int day, month, year;
    do {
        std::cout << "Enter date (DD MM YYYY): ";
        std::cin >> day >> month >> year;
        if (!isValidDate(day, month, year)) {
            std::cout << "Invalid date format! Please enter again.\n";
        }
        else {
            newEvent->date = std::to_string(day) + " " + std::to_string(month) + " " + std::to_string(year);
        }
    } 
    
while (!isValidDate(day, month, year));

    std::cin.ignore();
    std::cout << "Enter event name: ";
    std::getline(std::cin, newEvent->name);
    std::cout << "Enter event description: ";
    std::getline(std::cin, newEvent->description);
    newEvent->next = nullptr;

    if (!head) head = newEvent;
    else {
        Event* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newEvent;
    }
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

    Event* temp = head;
    Event* prev = nullptr;
    bool found = false;

    while (temp) {
        if (temp->date == fullDate && temp->name == eventName) {
            if (!prev) head = temp->next;
            else prev->next = temp->next;
            delete temp;
            found = true;
            break;
        }
        prev = temp;
        temp = temp->next;
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
    Event* temp = head;
    while (temp) {
        std::cout << temp->date << " - " << temp->name;
        if (!temp->description.empty()) std::cout << " - " << temp->description;
        std::cout << "\n";
        temp = temp->next;
    }
}