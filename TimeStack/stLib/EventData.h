#pragma once

#include <string>

struct Event {
    std::string date;
    std::string name;
    std::string description;
    Event* next = nullptr;
};

extern Event* head;
const std::string filename = "entries.txt";
