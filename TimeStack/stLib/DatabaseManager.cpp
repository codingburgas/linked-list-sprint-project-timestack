#include "EventData.h"
#include <fstream>
#include <sstream>
#include <iostream>

void loadEvents() {
    std::ifstream file(filename);
    if (!file) {
        std::ofstream createFile(filename);
        createFile.close();
        return;
    }

    events.clear();

    int day, month, year;
    std::string name, description, tempLine;

    while (std::getline(file, tempLine)) {
        std::istringstream lineStream(tempLine);
        lineStream >> day >> month >> year;
        lineStream.ignore();  // Ignore space
        std::getline(lineStream, name, '-');
        std::getline(lineStream, description);

        name = name.substr(name.find_first_not_of(" "));
        description = description.substr(description.find_first_not_of(" "));

        Event newEvent;
        newEvent.date = std::to_string(day) + " " + std::to_string(month) + " " + std::to_string(year);
        newEvent.name = name;
        newEvent.description = description;

        events.push_back(newEvent);
    }

    file.close();
}
