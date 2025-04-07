#include "../TimeStack/precompiler.h"

void bubbleSort(int sortBy) {
    if (head == nullptr || head->next == nullptr) return; // No need to sort if there's 1 or 0 events

    bool swapped;
    Event* temp;
    Event* prev = nullptr;
    Event* last = nullptr;

    do {
        swapped = false;
        temp = head;

        while (temp->next != last) {
            bool condition = false;

            // Sorting based on user's choice (year, month, day or name)
            switch (sortBy) {
            case 1:  // Sort by Year (ascending)
                if (temp->date.substr(6, 4) > temp->next->date.substr(6, 4)) condition = true;
                break;
            case 2:  // Sort by Month (ascending)
                if (temp->date.substr(3, 2) > temp->next->date.substr(3, 2)) condition = true;
                break;
            case 3:  // Sort by Day (ascending)
                if (temp->date.substr(0, 2) > temp->next->date.substr(0, 2)) condition = true;
                break;
            case 4:  // Sort by Event Name (alphabetical)
                if (temp->name > temp->next->name) condition = true;
                break;
            default:
                std::cout << "Invalid sort option!\n";
                return;
            }

            if (condition) {
                // Swap the nodes if they are in the wrong order
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