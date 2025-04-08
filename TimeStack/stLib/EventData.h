#pragma once

#include <string>

// Represents a single event in the linked list
struct Event {
    std::string date;
    std::string name;
    std::string description;
    Event* next = nullptr;
};

extern Event* head;

// File where events are stored
const std::string filename = "database/entries.txt";
