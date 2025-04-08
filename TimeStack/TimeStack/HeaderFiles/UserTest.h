#pragma once
#include <vector>
#include <string>
#include "../stLib/EventData.h"

struct OptionNode {
    std::string text;          // The text for the option
    OptionNode* next;          // Pointer to the next option
};

struct QuestionNode {
    std::string questionText;  // The question itself
    OptionNode* optionsHead;   // Head pointer to the list of options
    int correctOption;         // The index of the correct option
    QuestionNode* next;        // Pointer to the next question
};

void createTestForEvent();
void takeTest();