#include "../TimeStack/HeaderFiles/precompiler.h"

// Sorts the linked list of events based on the specified criteria
void bubbleSort(int sortBy) {
    if (head == nullptr || head->next == nullptr) return;

    bool swapped;
    Event* current;
    Event* lastSorted = nullptr;

    do {
        swapped = false;
        current = head;

        // Traverse the list until the last sorted node
        while (current->next != lastSorted) {
            bool shouldSwap = false;

            switch (sortBy) {
            case 1: // Sort by Year
                if (current->date.substr(6, 4) > current->next->date.substr(6, 4))
                    shouldSwap = true;
                break;
            case 2: // Sort by Month
                if (current->date.substr(3, 2) > current->next->date.substr(3, 2))
                    shouldSwap = true;
                break;
            case 3: // Sort by Day
                if (current->date.substr(0, 2) > current->next->date.substr(0, 2))
                    shouldSwap = true;
                break;
            case 4: // Sort by Name alphabetically
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

            // If a swap is needed, exchange all fields of the two Event nodes
            if (shouldSwap) {
                std::swap(current->date, current->next->date);
                std::swap(current->name, current->next->name);
                std::swap(current->description, current->next->description);
                swapped = true;  // Set flag to true so the loop runs again
            }

            current = current->next;  // Move to the next pair of nodes
        }

        
        lastSorted = current;
    } while (swapped);
}

// Handles user interaction for sorting and integrates sorting functionality
void sortEvents() {
    loadEvents();

    int option;
    std::cout << "Sort events by:\n";
    std::cout << "1. Year\n";
    std::cout << "2. Month\n";
    std::cout << "3. Day\n";
    std::cout << "4. Name (Alphabetically)\n";
    std::cout << "Enter your choice: ";
    std::cin >> option;
    std::cin.ignore(); // Clear newline character to avoid input issues later

    bubbleSort(option); // Call sorting logic based on user's selection
    saveEvents();

    std::cout << "\nEvents sorted successfully.\n\n";
    listEvents(); 

    std::cout << "\nPress Enter to return to the menu...";
    std::cin.get();
    system("cls");
}
