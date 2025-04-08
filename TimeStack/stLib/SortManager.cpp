#include "../TimeStack/HeaderFiles/precompiler.h"

void bubbleSort(int sortBy) {
    if (head == nullptr || head->next == nullptr) return;

    bool swapped;
    Event* current;
    Event* lastSorted = nullptr;

    do {
        swapped = false;
        current = head;

        while (current->next != lastSorted) {
            bool shouldSwap = false;

            switch (sortBy) {
            case 1: // Year
                if (current->date.substr(6, 4) > current->next->date.substr(6, 4))
                    shouldSwap = true;
                break;
            case 2: // Month
                if (current->date.substr(3, 2) > current->next->date.substr(3, 2))
                    shouldSwap = true;
                break;
            case 3: // Day
                if (current->date.substr(0, 2) > current->next->date.substr(0, 2))
                    shouldSwap = true;
                break;
            case 4: // Name
                if (current->name > current->next->name)
                    shouldSwap = true;
                break;
            default:
                std::cout << "Invalid sort option!\n";
                std::cout << "\nPress Enter to return to the menu...";
                std::cin.ignore();
                std::cin.get();
                system("cls");
                return;
            }

            if (shouldSwap) {
                std::swap(current->date, current->next->date);
                std::swap(current->name, current->next->name);
                std::swap(current->description, current->next->description);
                swapped = true;
            }

            current = current->next;
        }

        lastSorted = current;
    } while (swapped);
}


void sortEvents() {
    loadEvents();  // <-- Make sure this is here

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
