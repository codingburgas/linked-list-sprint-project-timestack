#include "precompiler.h"

Event* head = nullptr;

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

    Event* temp = head;
    while (temp != nullptr) {
        std::istringstream dateStream(temp->date);
        int day, month, year;
        dateStream >> day >> month >> year;

        file << day << " " << month << " " << year << " - " << temp->name;
        if (!temp->description.empty()) {
            file << " - " << temp->description;
        }
        file << "\n";

        temp = temp->next;
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
    } while (!isValidDate(day, month, year));

    std::cin.ignore();  // Clear buffer before reading text
    std::cout << "Enter event name: ";
    std::getline(std::cin, newEvent->name);

    std::cout << "Enter event description: ";
    std::getline(std::cin, newEvent->description);

    // Add to linked list
    newEvent->next = nullptr;
    if (!head) {
        head = newEvent;
    }
    else {
        Event* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newEvent;
    }

    // Save to file
    saveEvents();
}

void editEvent() {
    std::string day, month, year, eventName;
    std::cout << "Enter date of event to edit (DD MM YYYY): ";
    std::cin >> day >> month >> year;
    std::cin.ignore();  // clear newline

    std::cout << "Enter the name of the event: ";
    std::getline(std::cin, eventName);

    std::string targetDate = trim(day) + " " + trim(month) + " " + trim(year);
    eventName = trim(eventName);

    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Could not open file for reading.\n";
        return;
    }

    std::ofstream tempFile("temp.txt");
    if (!tempFile) {
        std::cerr << "Could not open temp file for writing.\n";
        return;
    }

    std::string line;
    bool found = false;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int d, m, y;
        std::string name, desc;
        char dash;

        iss >> d >> m >> y >> dash;
        std::getline(iss, name, '-');
        std::getline(iss, desc);

        std::string fileDate = std::to_string(d) + " " + std::to_string(m) + " " + std::to_string(y);
        name = trim(name);
        desc = trim(desc);

        if (fileDate == targetDate && name == eventName) {
            found = true;

            std::cout << "\nEvent found!\n";
            std::cout << "1. Edit date\n";
            std::cout << "2. Edit name\n";
            std::cout << "3. Edit description\n";
            std::cout << "4. Cancel\n";
            std::cout << "Choose what to edit: ";

            int choice;
            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
            case 1: {
                int newDay, newMonth, newYear;
                std::cout << "Enter new date (DD MM YYYY): ";
                std::cin >> newDay >> newMonth >> newYear;
                fileDate = std::to_string(newDay) + " " + std::to_string(newMonth) + " " + std::to_string(newYear);
                std::cin.ignore();
                break;
            }
            case 2: {
                std::cout << "Enter new name: ";
                std::getline(std::cin, name);
                break;
            }
            case 3: {
                std::cout << "Enter new description: ";
                std::getline(std::cin, desc);
                break;
            }
            case 4:
                std::cout << "Edit cancelled.\n";
                tempFile << line << "\n";
                continue;
            default:
                std::cout << "Invalid option.\n";
                tempFile << line << "\n";
                continue;
            }

            tempFile << fileDate << " - " << trim(name);
            if (!desc.empty()) tempFile << " - " << trim(desc);
            tempFile << "\n";

        }
        else {
            tempFile << line << "\n";
        }
    }

    infile.close();
    tempFile.close();

    if (found) {
        std::remove(filename.c_str());
        std::rename("temp.txt", filename.c_str());
        std::cout << "Event updated successfully.\n";
        system("cls");
    }
    else {
        std::remove("temp.txt");  // clean up
        std::cout << "Event not found.\n";
    }
}


void deleteEvent() {
    std::string day, month, year, eventName;
    std::cout << "Enter date of event to delete (DD MM YYYY): ";
    std::cin >> day >> month >> year;
    std::cin.ignore();  // clear leftover newline

    std::cout << "Enter the name of the event: ";
    std::getline(std::cin, eventName);

    std::string targetDate = trim(day) + " " + trim(month) + " " + trim(year);
    eventName = trim(eventName);

    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Could not open file for reading.\n";
        return;
    }

    std::ofstream tempFile("temp.txt");
    if (!tempFile) {
        std::cerr << "Could not open temp file for writing.\n";
        return;
    }

    std::string line;
    bool found = false;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int d, m, y;
        std::string name, desc;
        char dash;

        iss >> d >> m >> y >> dash;
        std::getline(iss, name, '-');
        std::getline(iss, desc);

        std::string fileDate = std::to_string(d) + " " + std::to_string(m) + " " + std::to_string(y);
        name = trim(name);

        if (fileDate == targetDate && name == eventName) {
            found = true;
            continue;  // Skip writing this line (delete it)
        }

        tempFile << line << "\n";  // Write back all other lines
    }

    infile.close();
    tempFile.close();

    // Replace original file with temp file
    std::remove(filename.c_str());
    std::rename("temp.txt", filename.c_str());

    if (found) {
        std::cout << "Event deleted successfully.\n";
        // Now delete from the linked list as well
        deleteFromList(targetDate, eventName);
    }
    else {
        std::cout << "Event not found.\n";
    }
}

void deleteFromList(const std::string& date, const std::string& name) {
    Event* temp = head;
    Event* prev = nullptr;

    while (temp != nullptr) {
        if (temp->date == date && temp->name == name) {
            if (prev == nullptr) {
                head = temp->next;  // If the head is being deleted
            }
            else {
                prev->next = temp->next;
            }
            delete temp;
            break;
        }
        prev = temp;
        temp = temp->next;
    }
}



void listEvents() {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error: Could not open file.\n";
        return;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int day, month, year;
        std::string name, desc;
        char dash;

        iss >> day >> month >> year >> dash;
        std::getline(iss, name, '-');
        std::getline(iss, desc);

        std::cout << day << " " << month << " " << year << " - " << name;
        if (!desc.empty()) {
            std::cout << " - " << desc;
        }
        std::cout << "\n";
    }
}
