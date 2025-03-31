#include "../TimeStack/precompiler.h"

bool gameOn = true;

void loadEvents() {
    std::ifstream file(filename);
    if (!file) {
        std::ofstream createFile(filename); // Create if it doesn't exist
        createFile.close();
        return;
    }

    events.clear();  // Ensure list is empty before loading to prevent duplicates

    std::string date, name;
    while (file >> date) {
        file.ignore(); // Ignore whitespace
        std::getline(file, name);
        events.push_back({ date, name });
    }
    file.close();
}
