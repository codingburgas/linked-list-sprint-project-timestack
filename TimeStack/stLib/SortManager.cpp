#include "../TimeStack/precompiler.h"

void bubbleSort(int sortBy) {
    if (head == nullptr || head->next == nullptr) return;

    bool swapped;
    Event* temp;
    Event* last = nullptr;

    do {
        swapped = false;
        temp = head;

        while (temp->next != last) {
            bool condition = false;

            switch (sortBy) {
            case 1: // Year
                if (temp->date.substr(6, 4) > temp->next->date.substr(6, 4)) condition = true;
                break;
            case 2: // Month
                if (temp->date.substr(3, 2) > temp->next->date.substr(3, 2)) condition = true;
                break;
            case 3: // Day
                if (temp->date.substr(0, 2) > temp->next->date.substr(0, 2)) condition = true;
                break;
            case 4: // Name
                if (temp->name > temp->next->name) condition = true;
                break;
            default:
                std::cout << "Invalid sort option!\n";
                std::cout << "\nPress Enter to return to the menu...";
                std::cin.ignore();
                std::cin.get();
                system("cls");
                return;
            }

            if (condition) {
                std::swap(temp->date, temp->next->date);
                std::swap(temp->name, temp->next->name);
                std::swap(temp->description, temp->next->description);
                swapped = true;
            }

            temp = temp->next;
        }

        last = temp;
    } while (swapped);
}

void sortEvents() {
    loadEvents();  // Always load events before sorting

    if (head == nullptr || head->next == nullptr) {
        std::cout << "No events found to sort.\n";
        std::cout << "\nPress Enter to return to the menu...";
        std::cin.ignore();
        std::cin.get();
        system("cls");
        return;
    }

    int option;
    std::cout << "Sort events by:\n";
    std::cout << "1. Year\n";
    std::cout << "2. Month\n";
    std::cout << "3. Day\n";
    std::cout << "4. Name (Alphabetically)\n";
    std::cout << "Enter your choice: ";
    std::cin >> option;
    std::cin.ignore(); // Clear newline

    bubbleSort(option);
    saveEvents();

    std::cout << "\nEvents sorted successfully.\n\n";
    listEvents();

    std::cout << "\nPress Enter to return to the menu...";
    std::cin.get();
    system("cls");
}
