#include "precompiler.h"

void listEvents() {
    for (const auto& event : events) {
        std::cout << event.date << " - " << event.name << "\n";
    }
}
