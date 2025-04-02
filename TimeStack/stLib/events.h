#pragma once

#include <list>
#include <string>

struct Event {
    std::string date;
    std::string name;
    std::string description; 
};

extern std::list<Event> events;  // Declaration of events list
extern const std::string filename;  // Declaration of filename