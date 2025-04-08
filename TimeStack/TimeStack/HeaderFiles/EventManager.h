#pragma once

void addEvent();
void editEvent();
void deleteEvent();
void listEvents();
void saveEvents();
void deleteFromList(const std::string& date, const std::string& name);
void createTestForEvent();
void searchEvents();
void exportEvents();
void addEventAtBeginning(Event* newEvent);
void addEventSorted(Event* newEvent);

int compareDates(const std::string& d1, const std::string& d2);
