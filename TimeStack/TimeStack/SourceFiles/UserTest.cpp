#include "../HeaderFiles/precompiler.h"

void createTestForEvent() {
    std::string eventName;
    char addMoreQuestions;
    QuestionNode* head = nullptr;  // Start of the linked list of questions
    QuestionNode* tail = nullptr;  // Points to the last node to ease appending

    std::cout << "Enter the name of the event: ";
    std::cin.ignore(); // Clears leftover input from previous input operations
    std::getline(std::cin, eventName);

    // Loop to allow the user to add multiple questions
    do {
        QuestionNode* newQuestion = new QuestionNode; // Allocate memory for new question
        newQuestion->optionsHead = nullptr;
        newQuestion->next = nullptr;

        std::cout << "Enter the question: ";
        std::getline(std::cin, newQuestion->questionText);

        int numOptions;
        std::cout << "Enter the number of options: ";
        std::cin >> numOptions;
        std::cin.ignore(); // Ignore the newline left in the input buffer

        OptionNode* optionTail = nullptr; // Pointer to build the linked list of options

        // Collect each option from the user
        for (int i = 0; i < numOptions; ++i) {
            OptionNode* newOption = new OptionNode; // Dynamically allocate option node
            std::cout << "Enter option " << (i + 1) << ": ";
            std::getline(std::cin, newOption->text);
            newOption->next = nullptr;

            // Link option node into the options list
            if (!newQuestion->optionsHead)
                newQuestion->optionsHead = newOption;
            else
                optionTail->next = newOption;

            optionTail = newOption;
        }

        std::cout << "Enter the number of the correct option: ";
        std::cin >> newQuestion->correctOption;
        std::cin.ignore(); // Clear input buffer after numeric input

        // Add the new question to the linked list
        if (!head)
            head = newQuestion;
        else
            tail->next = newQuestion;

        tail = newQuestion;

        std::cout << "Do you want to add another question? (y/n): ";
        std::cin >> addMoreQuestions;
        std::cin.ignore();
    } while (addMoreQuestions == 'y' || addMoreQuestions == 'Y');

    // Ensure the output directory exists before saving the file
    _mkdir("database");

    // Create the file path and open file for writing test data
    std::string filePath = "database/" + eventName + "test.txt";
    std::ofstream file(filePath);
    if (!file) {
        std::cout << "Failed to save the test.\n";
        std::cout << "\nPress Enter to return to the menu...";
        std::cin.ignore();
        std::cin.get();
        system("cls");
        return;
    }

    // Write all questions and their options to the file in a formatted way
    QuestionNode* q = head;
    int qIndex = 1;
    while (q) {
        file << "Q" << qIndex++ << ": " << q->questionText << "\n";

        // Count and write the number of options
        int optionCount = 0;
        OptionNode* oCount = q->optionsHead;
        while (oCount) {
            optionCount++;
            oCount = oCount->next;
        }
        file << optionCount << "\n";

        // Write each option to the file
        OptionNode* o = q->optionsHead;
        int optIndex = 1;
        while (o) {
            file << "  Option " << optIndex++ << ": " << o->text << "\n";
            o = o->next;
        }

        file << q->correctOption << "\n\n"; // Write the correct answer
        q = q->next;
    }

    file.close(); // Finalize file writing
    std::cout << "Test saved to '" << filePath << "'!\n";
    std::cout << "\nPress Enter to return to the menu...";
    std::cin.ignore();
    std::cin.get();
    system("cls");
}

void takeTest() {
    std::string testFileName;
    std::cout << "Enter the name of the test file to take (e.g. 'eventname_test.txt'): ";
    std::cin >> testFileName;

    std::ifstream file("database/" + testFileName);
    if (!file) {
        std::cout << "Could not open test file: " << testFileName << "\n";
        std::cout << "\nPress Enter to return to the menu...";
        std::cin.ignore();
        std::cin.get();
        system("cls");
        return;
    }

    QuestionNode* qHead = nullptr; // Head of the loaded questions
    QuestionNode* qTail = nullptr; // Tail to append new questions
    std::string line;

    // Parse the test file and load questions into memory
    while (std::getline(file, line)) {
        if (line.empty()) continue; // Skip empty lines

        QuestionNode* newNode = new QuestionNode;
        newNode->optionsHead = nullptr;
        newNode->next = nullptr;

        // Extract the question text after "Qn: "
        newNode->questionText = line.substr(line.find(":") + 2);

        int optionCount;
        file >> optionCount; // Read how many options to expect
        file.ignore();

        OptionNode* optionTail = nullptr;

        // Load each option and link it
        for (int i = 0; i < optionCount; ++i) {
            std::getline(file, line);
            OptionNode* newOption = new OptionNode;
            newOption->text = line.substr(line.find(":") + 2); // Extract actual option text
            newOption->next = nullptr;

            if (!newNode->optionsHead)
                newNode->optionsHead = newOption;
            else
                optionTail->next = newOption;

            optionTail = newOption;
        }

        // Load the correct option number for this question
        file >> newNode->correctOption;
        file.ignore();

        // Add the question node to the linked list
        if (!qHead)
            qHead = qTail = newNode;
        else {
            qTail->next = newNode;
            qTail = newNode;
        }

        std::getline(file, line); // Eat up any extra empty line
    }

    file.close();

    std::cout << "\nTake the Test!\n";
    int score = 0, total = 0;

    // Iterate over questions and present them to the user
    QuestionNode* current = qHead;
    while (current) {
        std::cout << "\n" << current->questionText << "\n";
        OptionNode* opt = current->optionsHead;
        int i = 1;
        while (opt) {
            std::cout << "  " << i++ << ". " << opt->text << "\n";
            opt = opt->next;
        }

        int userAnswer;
        std::cout << "Your answer: ";
        std::cin >> userAnswer;

        // Evaluate user's answer and update score
        if (userAnswer == current->correctOption) {
            std::cout << "Correct!\n";
            score++;
        }
        else {
            std::cout << "Incorrect. Correct answer was option " << current->correctOption << ".\n";
        }

        total++;
        current = current->next;
    }

    // Show final score to the user
    std::cout << "\nTest complete! Your score: " << score << " / " << total << "\n";
    std::cout << "\nPress Enter to return to the menu...";
    std::cin.ignore();
    std::cin.get();
    system("cls");

    // Cleanup: Deallocate all dynamically created memory for questions and options
    while (qHead) {
        QuestionNode* temp = qHead;
        qHead = qHead->next;

        OptionNode* opt = temp->optionsHead;
        while (opt) {
            OptionNode* tempOpt = opt;
            opt = opt->next;
            delete tempOpt;
        }

        delete temp;
    }
}
