#include "../TimeStack/precompiler.h"

void loadEvents() {
    std::ifstream file(filename);
    if (!file) return;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string datePart, name, description;

        std::getline(ss, datePart, '-');
        std::getline(ss, name, '-');
        std::getline(ss, description);

        // Trim whitespace
        auto trim = [](std::string& str) {
            str.erase(0, str.find_first_not_of(" \t"));
            str.erase(str.find_last_not_of(" \t") + 1);
            };

        trim(datePart);
        trim(name);
        trim(description);

        Event* newEvent = new Event;
        newEvent->date = datePart;
        newEvent->name = name;
        newEvent->description = description;
        newEvent->next = nullptr;

        if (!head) head = newEvent;
        else {
            Event* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newEvent;
        }
    }
}
