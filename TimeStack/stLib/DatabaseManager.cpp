#include "../TimeStack/precompiler.h"
#include "../TimeStack/EventManager.cpp"

void loadEvents() {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open file for reading.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int day, month, year;
        std::string name, desc;

        if (!(iss >> day >> month >> year)) continue;

        std::getline(iss, name, '-');
        std::getline(iss, desc);

        Event* newEvent = new Event;
        newEvent->date = std::to_string(day) + " " + std::to_string(month) + " " + std::to_string(year);
        newEvent->name = name.empty() ? "Unnamed" : name;
        newEvent->description = desc;
        newEvent->next = nullptr;

        if (!head)
            head = newEvent;
        else {
            Event* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newEvent;
        }
    }
    file.close();
}
