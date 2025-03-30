#include "../TimeStack/precompiler.h"

bool gameOn = true;

void loadEvents() {
    std::ifstream file(filename);
    if (!file) {
        std::ofstream createFile(filename); // Create file if it doesn't exist
        createFile.close();
    }
    std::string date, name;
    while (file >> date) {
        std::getline(file, name);
        events.push_back({ date, name });
    }
    file.close();
}