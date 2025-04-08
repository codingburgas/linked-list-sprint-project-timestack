#include "../TimeStack/HeaderFiles/precompiler.h"

// Loads events from the file and stores them in a linked list
void loadEvents() {
    std::ifstream file(filename);
    if (!file) return;  // Exit if file can't be opened

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string datePart, name, description;

        // Split the line into parts using '-' as delimiter
        std::getline(ss, datePart, '-');
        std::getline(ss, name, '-');
        std::getline(ss, description);

        // Trim leading/trailing whitespace
        auto trim = [](std::string& str) {
            str.erase(0, str.find_first_not_of(" \t"));
            str.erase(str.find_last_not_of(" \t") + 1);
            };
        trim(datePart);
        trim(name);
        trim(description);

        // Create and populate new event node
        Event* newEvent = new Event{ datePart, name, description, nullptr };

        // Add the new node to the end of the list
        if (!head)
            head = newEvent;
        else {
            Event* temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newEvent;
        }
    }
}
