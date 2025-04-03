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

    // Combine the input into "DD-MM-YYYY" format
    std::string fullDate = trim(day) + "-" + trim(month) + "-" + trim(year);
    eventName = trim(eventName);  // Ensure event name has no leading/trailing spaces

    // Debugging lines: show the formatted input
    std::cout << "Full Date Input: " << fullDate << std::endl;
    std::cout << "Event Name Input: " << eventName << std::endl;

    bool found = false;
    std::list<Event> tempEvents;

    // Loop through the events list and find the matching event
    for (const Event& e : events) {
        // Debugging lines: show the stored event details
        std::cout << "Stored Event Date: " << e.date << " | Stored Event Name: " << e.name << std::endl;

        // Check if both the date and name match
        if (e.date == fullDate && e.name == eventName) {
            found = true;
            continue;  // Skip adding this event (deleting it)
        }
        tempEvents.push_back(e);  // Keep other events in tempEvents
    }

    if (found) {
        events = tempEvents;  // Update the events list with the remaining events
        saveEvents();  // Save the modified list back to the file
        std::cout << "Event deleted successfully.\n";
    }
    else {
        std::cout << "Event not found.\n";
    }
}