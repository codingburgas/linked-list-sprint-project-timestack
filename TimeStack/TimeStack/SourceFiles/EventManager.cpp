#include "../HeaderFiles/precompiler.h"

// Removes leading and trailing spaces from a string
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    if (first == std::string::npos || last == std::string::npos) return "";
    return str.substr(first, last - first + 1);
}

// Validates a simple date (doesn't account for leap years or day/month correlation)
bool isValidDate(int day, int month, int year) {
    if (day < 1 || day > 31) return false;
    if (month < 1 || month > 12) return false;
    if (year > 2100) return false;
    return true;
}

// Adds a new event node at the beginning of the linked list
void addEventAtBeginning(Event* newEvent) {
    newEvent->next = head;
    head = newEvent;
}

// Inserts an event into the linked list in sorted order by date
void addEventSorted(Event* newEvent) {
    if (!head || compareDates(newEvent->date, head->date) < 0) {
        newEvent->next = head;
        head = newEvent;
        return;
    }

    Event* current = head;
    // Traverse until we find the correct position for insertion
    while (current->next && compareDates(newEvent->date, current->next->date) >= 0) {
        current = current->next;
    }

    newEvent->next = current->next;
    current->next = newEvent;
}

// Compares two date strings (assumes format "DD MM YYYY") and returns ordering
int compareDates(const std::string& d1, const std::string& d2) {
    std::stringstream ss1(d1), ss2(d2);
    int day1, month1, year1;
    int day2, month2, year2;

    ss1 >> day1 >> month1 >> year1;
    ss2 >> day2 >> month2 >> year2;

    // Compare year first, then month, then day
    if (year1 != year2) return year1 - year2;
    if (month1 != month2) return month1 - month2;
    return day1 - day2;
}

// Exports all current events from the linked list into a CSV file
void exportEvents() {
    std::ofstream outFile("database/events_export.csv");
    if (!outFile) {
        std::cout << "Error: Could not open file for writing.\n";
        std::cout << "\nPress Enter to return to the menu...";
        std::cin.ignore();
        std::cin.get();
        system("cls");
        return;
    }

    // CSV header
    outFile << "Date,Name,Description\n";

    // Loop through all events and write them
    Event* temp = head;
    while (temp) {
        outFile << temp->date << "," << temp->name << "," << temp->description << "\n";
        temp = temp->next;
    }

    outFile.close();

    std::cout << "Events exported successfully to events_export.csv\n";
    std::cout << "\nPress Enter to return to the menu...";
    std::cin.ignore();  // Clear leftover newline
    std::cin.get();     // Wait for user input
    system("cls");
}

// Saves all current events to a file (overwrites existing file)
void saveEvents() {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Failed to open file for saving.\n";
        return;
    }

    // Write each event as a line
    Event* current = head;
    while (current) {
        file << current->date << " - " << current->name;
        if (!current->description.empty()) {
            file << " - " << current->description;
        }
        file << "\n";
        current = current->next;
    }

    file.close();
}

// Searches for an event by date and name
void searchEvents() {
    std::string day, month, year, eventName;

    std::cout << "Enter date of the event to search (DD MM YYYY): ";
    std::cin >> day >> month >> year;
    std::cin.ignore();

    std::cout << "Enter the name of the event: ";
    std::getline(std::cin, eventName);

    std::string targetDate = trim(day) + " " + trim(month) + " " + trim(year);
    eventName = trim(eventName);

    std::ifstream infile(filename);
    if (!infile) {
        std::cout << "Could not open file for reading.\n";
        std::cout << "\nPress Enter to return to the menu...";
        std::cin.get();
        system("cls");
        return;
    }

    std::string line;
    bool found = false;

    // Search through the file line-by-line
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
            std::cout << "\nEvent found:\n";
            std::cout << fileDate << " - " << name;
            if (!desc.empty()) {
                std::cout << " - " << desc;
            }
            std::cout << "\n";
            found = true;
            break;
        }
    }

    infile.close();

    if (!found) {
        std::cout << "No event found with the given name and date.\n";
    }

    std::cout << "\nPress Enter to return to the menu...";
    std::cin.get();
    system("cls");
}

// Adds a new event through user input and saves it to file
void addEvent() {
    Event* newEvent = new Event;

    int day, month, year;

    // Loop until a valid date is provided
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

    std::cin.ignore();

    std::cout << "Enter event name: ";
    std::getline(std::cin, newEvent->name);

    std::cout << "Enter event description: ";
    std::getline(std::cin, newEvent->description);

    newEvent->next = nullptr;

    // Choose insertion mode
    int insertChoice;
    std::cout << "\nWhere do you want to add the event?\n";
    std::cout << "1. At the beginning\n";
    std::cout << "2. At the end\n";
    std::cout << "3. Sorted by date\n";
    std::cout << "Enter choice (1-3): ";
    std::cin >> insertChoice;

    switch (insertChoice) {
    case 1:
        addEventAtBeginning(newEvent);
        break;
    case 2:
        // Traverse to end of list to insert
        if (!head) head = newEvent;
        else {
            Event* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newEvent;
        }
        break;
    case 3:
        addEventSorted(newEvent);
        break;
    default:
        std::cout << "Invalid choice. Adding at end by default.\n";
        if (!head) head = newEvent;
        else {
            Event* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newEvent;
        }
    }

    // Append new event to file
    std::ofstream file(filename, std::ios::app);
    file << day << " " << month << " " << year << " - " << newEvent->name;
    if (!newEvent->description.empty()) {
        file << " - " << newEvent->description;
    }
    file << "\n";
    file.close();

    std::cout << "\nEvent added successfully!";
    std::cout << "\nPress Enter to return to menu...";
    std::cin.ignore();
    std::cin.get();
    system("cls");
}
void editEvent() {
    std::string day, month, year, eventName;

    // Get date and name of event to edit
    std::cout << "Enter date of event to edit (DD MM YYYY): ";
    std::cin >> day >> month >> year;
    std::cin.ignore();

    std::cout << "Enter the name of the event: ";
    std::getline(std::cin, eventName);

    // Format target date and clean up input
    std::string targetDate = trim(day) + " " + trim(month) + " " + trim(year);
    eventName = trim(eventName);

    std::ifstream infile(filename);
    if (!infile) {
        std::cout << "Could not open file for reading.\n";
        std::cout << "\nPress Enter to return to the menu...";
        std::cin.get();
        system("cls");
        return;
    }

    std::ofstream tempFile("temp.txt");
    if (!tempFile) {
        std::cout << "Could not open temp file for writing.\n";
        std::cout << "\nPress Enter to return to the menu...";
        std::cin.get();
        system("cls");
        return;
    }

    std::string line;
    bool found = false;

    // Read file line by line
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int d, m, y;
        std::string name, desc;
        char dash;

        // Parse event line: date - name - description
        iss >> d >> m >> y >> dash;
        std::getline(iss, name, '-');
        std::getline(iss, desc);

        std::string fileDate = std::to_string(d) + " " + std::to_string(m) + " " + std::to_string(y);
        name = trim(name);
        desc = trim(desc);

        // Check if current line matches the event to be edited
        if (fileDate == targetDate && name == eventName) {
            found = true;

            // Show edit options
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
                // Update date
                int newDay, newMonth, newYear;
                std::cout << "Enter new date (DD MM YYYY): ";
                std::cin >> newDay >> newMonth >> newYear;
                fileDate = std::to_string(newDay) + " " + std::to_string(newMonth) + " " + std::to_string(newYear);
                std::cin.ignore();
                break;
            }
            case 2: {
                // Update name
                std::cout << "Enter new name: ";
                std::getline(std::cin, name);
                break;
            }
            case 3: {
                // Update description
                std::cout << "Enter new description: ";
                std::getline(std::cin, desc);
                break;
            }
            case 4:
                // Skip modification, keep original line
                std::cout << "Edit cancelled.\n";
                tempFile << line << "\n";
                continue;
            default:
                // Handle invalid input
                std::cout << "Invalid option.\n";
                tempFile << line << "\n";
                continue;
            }

            // Write updated event to temp file
            tempFile << fileDate << " - " << trim(name);
            if (!desc.empty()) tempFile << " - " << trim(desc);
            tempFile << "\n";

        }
        else {
            // Write unmodified event to temp file
            tempFile << line << "\n";
        }
    }

    infile.close();
    tempFile.close();

    if (found) {
        // Replace old file with updated temp file
        std::remove(filename.c_str());
        std::rename("temp.txt", filename.c_str());
        std::cout << "Event updated successfully.\n";
    }
    else {
        std::remove("temp.txt");
        std::cout << "Event not found.\n";
    }

    std::cout << "\nPress Enter to return to the menu...";
    std::cin.get();
    system("cls");
}

void deleteEvent() {
    std::string day, month, year, eventName;

    // Get date and name of event to delete
    std::cout << "Enter date of event to delete (DD MM YYYY): ";
    std::cin >> day >> month >> year;
    std::cin.ignore();

    std::cout << "Enter the name of the event: ";
    std::getline(std::cin, eventName);

    // Prepare formatted search key
    std::string targetDate = trim(day) + " " + trim(month) + " " + trim(year);
    eventName = trim(eventName);

    std::ifstream infile(filename);
    if (!infile) {
        std::cout << "Could not open file for reading.\n";
        std::cout << "\nPress Enter to return to the menu...";
        std::cin.get();
        system("cls");
        return;
    }

    std::ofstream tempFile("temp.txt");
    if (!tempFile) {
        std::cout << "Could not open temp file for writing.\n";
        std::cout << "\nPress Enter to return to the menu...";
        std::cin.get();
        system("cls");
        return;
    }

    std::string line;
    bool found = false;

    // Process file line by line
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int d, m, y;
        std::string name, desc;
        char dash;

        // Parse event fields
        iss >> d >> m >> y >> dash;
        std::getline(iss, name, '-');
        std::getline(iss, desc);

        std::string fileDate = std::to_string(d) + " " + std::to_string(m) + " " + std::to_string(y);
        name = trim(name);

        // Skip writing matching event (i.e. delete it)
        if (fileDate == targetDate && name == eventName) {
            found = true;
            continue;
        }

        // Keep other events
        tempFile << line << "\n";
    }

    infile.close();
    tempFile.close();

    // Overwrite original file with temp
    std::remove(filename.c_str());
    std::rename("temp.txt", filename.c_str());

    if (found) {
        std::cout << "Event deleted successfully.\n";
        deleteFromList(targetDate, eventName); // Sync with in-memory list
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

    // Traverse linked list to find and delete the node
    while (temp != nullptr) {
        if (temp->date == date && temp->name == name) {
            if (prev == nullptr) {
                head = temp->next;
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
        std::cout << "Error: Could not open file.\n";
        std::cout << "\nPress Enter to return to menu...";
        std::cin.get();
        system("cls");
        return;
    }

    std::string line;
    bool found = false;

    // Read each event and display
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int day, month, year;
        std::string name, desc;
        char dash;

        if (!(iss >> day >> month >> year >> dash)) {
            std::cout << "Error: Invalid line format in file.\n";
            continue;
        }

        std::getline(iss, name, '-');
        std::getline(iss, desc);

        // Print event details
        std::cout << day << " " << month << " " << year << " - " << name;
        if (!desc.empty()) {
            std::cout << " - " << desc;
        }
        std::cout << "\n";
        found = true;
    }

    if (!found) {
        std::cout << "No events found.\n";
    }

    std::cout << "\nPress Enter to return to the menu...";
    std::cin.ignore();
    std::cin.get();
    system("cls");
}
