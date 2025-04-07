#pragma once

#include <string>

struct Event {
    std::string date;
    std::string name;
    std::string description;
    Event* next;
};

extern Event* head;
const std::string filename = "entries.txt";
