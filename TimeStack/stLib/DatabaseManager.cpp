#include "../TimeStack/precompiler.h"

bool gameOn = true;

void loadEvents() {
    std::ifstream file(filename);
    if (!file) {
        std::ofstream createFile(filename); // Create the file if it doesn't exist
        createFile.close();
        return;
    }

    events.clear();  // Clear the list to prevent duplicates

    int day, month, year;
    std::string name, description;

    std::string tempLine;
    while (std::getline(file, tempLine)) {
        std::istringstream lineStream(tempLine);
        lineStream >> day >> month >> year; // Read date as separate values

        lineStream.ignore(); // Ignore the first '-'

        std::getline(lineStream, name, '-'); // Read name until the first '-'

        // Read the rest as description (if it exists)
        std::getline(lineStream, description);

        // Trim spaces
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
