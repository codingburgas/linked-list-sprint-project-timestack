#include "precompiler.h"
#include "EventManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
struct Question {
    std::string questionText;
    std::vector<std::string> options;
    int correctOption = -1;
};
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
void createTestForEvent() {
    std::string eventName;
    std::vector<Question> questions;
    char addMoreQuestions;

    std::cout << "Enter the name of the event: ";
    std::cin.ignore();
    std::getline(std::cin, eventName);

    do {
        Question q;
        std::cout << "Enter the question: ";
        std::getline(std::cin, q.questionText);

        int numOptions;
        std::cout << "Enter the number of options: ";
        std::cin >> numOptions;
        std::cin.ignore();

        for (int i = 0; i < numOptions; ++i) {
            std::string option;
            std::cout << "Enter option " << (i + 1) << ": ";
            std::getline(std::cin, option);
            q.options.push_back(option);
        }

        std::cout << "Enter the number of the correct option: ";
        std::cin >> q.correctOption;
        std::cin.ignore();

        questions.push_back(q);

        std::cout << "Do you want to add another question? (y/n): ";
        std::cin >> addMoreQuestions;
        std::cin.ignore();

    } while (addMoreQuestions == 'y' || addMoreQuestions == 'Y');
    std::cout << "\nTest for event '" << eventName << "':\n";
    for (size_t i = 0; i < questions.size(); ++i) {
        std::cout << "Q" << (i + 1) << ": " << questions[i].questionText << "\n";
        for (size_t j = 0; j < questions[i].options.size(); ++j) {
            std::cout << "  " << (j + 1) << ". " << questions[i].options[j] << "\n";
        }
        std::cout << "Correct option: " << questions[i].correctOption << "\n";
    }
}
void viewEventDetails() {
    std::string day, month, year, eventName;
    std::cout << "Enter date of event to view details (DD MM YYYY): ";
    std::cin >> day >> month >> year;
    std::cin.ignore();  // clear newline

    std::cout << "Enter the name of the event: ";
    std::getline(std::cin, eventName);

    std::string targetDate = trim(day) + " " + trim(month) + " " + trim(year);
    eventName = trim(eventName);

    Event* temp = head;
    bool found = false;
    while (temp) {
        if (temp->date == targetDate && temp->name == eventName) {
            std::cout << "Event Details:\n";
            std::cout << "Date: " << temp->date << "\n";
            std::cout << "Name: " << temp->name << "\n";
            std::cout << "Description: " << temp->description << "\n";
            found = true;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        std::cout << "Event not found.\n";
    }
}
void saveEvents() {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file for writing.\n";
        return;
    }

    Event* temp = head;
    while (temp) {
        file << temp->date << " - " << temp->name;
        if (!temp->description.empty()) {
            file << " - " << temp->description;
        }
        file << "\n";
        temp = temp->next;
    }

    file.close();
}

void searchEvents() {
    int searchOption;
    std::cout << "Search events by:\n";
    std::cout << "1. Name\n";
    std::cout << "2. Date\n";
    std::cout << "Enter your choice: ";
    std::cin >> searchOption;
    std::cin.ignore();

    if (searchOption == 1) {
        std::string searchName;
        std::cout << "Enter the name of the event: ";
        std::getline(std::cin, searchName);
        searchName = trim(searchName);

        Event* temp = head;
        bool found = false;
        while (temp) {
            if (temp->name.find(searchName) != std::string::npos) {
                std::cout << temp->date << " - " << temp->name;
                if (!temp->description.empty()) {
                    std::cout << " - " << temp->description;
                }
                std::cout << "\n";
                found = true;
            }
            temp = temp->next;
        }
        if (!found) {
            std::cout << "No events found with the name '" << searchName << "'.\n";
        }
    }
    else if (searchOption == 2) {
        std::string day, month, year;
        std::cout << "Enter date of event to search (DD MM YYYY): ";
        std::cin >> day >> month >> year;
        std::cin.ignore();

        std::string searchDate = trim(day) + " " + trim(month) + " " + trim(year);

        Event* temp = head;
        bool found = false;
        while (temp) {
            if (temp->date == searchDate) {
                std::cout << temp->date << " - " << temp->name;
                if (!temp->description.empty()) {
                    std::cout << " - " << temp->description;
                }
                std::cout << "\n";
                found = true;
            }
            temp = temp->next;
        }
        if (!found) {
            std::cout << "No events found on the date '" << searchDate << "'.\n";
        }
    }
    else {
        std::cout << "Invalid search option.\n";
    }
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

    std::cout << "\nEvent added successfully!";
    std::cout << "\nPress Enter to return to menu...";
    std::cin.get(); // only one enter needed now
    system("cls");
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
        deleteFromList(targetDate, eventName);
    }
    else {
        std::cout << "Event not found.\n";
    }

    std::cout << "\nPress Enter to return to menu...";
    std::cin.get();
    system("cls");
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

void sortEvents() {
    int option;
    std::cout << "Sort events by:\n";
    std::cout << "1. Year\n";
    std::cout << "2. Month\n";
    std::cout << "3. Day\n";
    std::cout << "4. Name (Alphabetically)\n";
    std::cout << "Enter your choice: ";
    std::cin >> option;

    bubbleSort(option);
    saveEvents();
    std::cout << "Events sorted successfully.\n";
    listEvents();
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

        // Ensure the line is in the correct format
        if (!(iss >> day >> month >> year >> dash)) {
            std::cerr << "Error: Invalid line format in file.\n";
            continue;  // Skip invalid lines
        }

        std::getline(iss, name, '-');
        std::getline(iss, desc);

        std::cout << day << " " << month << " " << year << " - " << name;
        if (!desc.empty()) {
            std::cout << " - " << desc;
        }
        std::cout << "\n";
    }
}
