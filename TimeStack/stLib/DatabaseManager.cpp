#include "../TimeStack/precompiler.h"

void loadEvents() {
    std::ifstream file(filename);
    if (!file) return;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int day, month, year;
        char dash;
        iss >> day >> month >> year >> dash;

        std::string name, desc;
        std::getline(iss, name, '-');
        std::getline(iss, desc);

        Event* newEvent = new Event;
        newEvent->date = std::to_string(day) + " " + std::to_string(month) + " " + std::to_string(year);
        newEvent->name = name;
        newEvent->description = desc;
        newEvent->next = nullptr;

        if (!head) head = newEvent;
        else {
            Event* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newEvent;
        }
    }
}


