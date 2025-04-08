#include "../HeaderFiles/precompiler.h"

void createTestForEvent() {
    std::string eventName;
    char addMoreQuestions;
    QuestionNode* head = nullptr;
    QuestionNode* tail = nullptr;

    std::cout << "Enter the name of the event: ";
    std::cin.ignore(); // Clear the input buffer
    std::getline(std::cin, eventName);

    do {
        QuestionNode* newQuestion = new QuestionNode;
        newQuestion->optionsHead = nullptr;
        newQuestion->next = nullptr;

        std::cout << "Enter the question: ";
        std::getline(std::cin, newQuestion->questionText);

        int numOptions;
        std::cout << "Enter the number of options: ";
        std::cin >> numOptions;
        std::cin.ignore(); // Clear newline

        OptionNode* optionTail = nullptr;

        for (int i = 0; i < numOptions; ++i) {
            OptionNode* newOption = new OptionNode;
            std::cout << "Enter option " << (i + 1) << ": ";
            std::getline(std::cin, newOption->text);
            newOption->next = nullptr;

            if (!newQuestion->optionsHead)
                newQuestion->optionsHead = newOption;
            else
                optionTail->next = newOption;

            optionTail = newOption;
        }

        std::cout << "Enter the number of the correct option: ";
        std::cin >> newQuestion->correctOption;
        std::cin.ignore(); // Clear newline

        if (!head)
            head = newQuestion;
        else
            tail->next = newQuestion;

        tail = newQuestion;

        std::cout << "Do you want to add another question? (y/n): ";
        std::cin >> addMoreQuestions;
        std::cin.ignore(); // Clear newline
    } while (addMoreQuestions == 'y' || addMoreQuestions == 'Y');

    // Ensure 'database/' directory exists
    _mkdir("database");

    // Save to file inside the database folder
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

    QuestionNode* q = head;
    int qIndex = 1;
    while (q) {
        file << "Q" << qIndex++ << ": " << q->questionText << "\n";

        int optionCount = 0;
        OptionNode* oCount = q->optionsHead;
        while (oCount) {
            optionCount++;
            oCount = oCount->next;
        }
        file << optionCount << "\n";

        OptionNode* o = q->optionsHead;
        int optIndex = 1;
        while (o) {
            file << "  Option " << optIndex++ << ": " << o->text << "\n";
            o = o->next;
        }

        file << q->correctOption << "\n\n";
        q = q->next;
    }

    file.close();
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

    QuestionNode* qHead = nullptr;
    QuestionNode* qTail = nullptr;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        QuestionNode* newNode = new QuestionNode;
        newNode->optionsHead = nullptr;
        newNode->next = nullptr;

        newNode->questionText = line.substr(line.find(":") + 2);

        int optionCount;
        file >> optionCount;
        file.ignore();

        OptionNode* optionTail = nullptr;
        for (int i = 0; i < optionCount; ++i) {
            std::getline(file, line);
            OptionNode* newOption = new OptionNode;
            newOption->text = line.substr(line.find(":") + 2);
            newOption->next = nullptr;

            if (!newNode->optionsHead)
                newNode->optionsHead = newOption;
            else
                optionTail->next = newOption;

            optionTail = newOption;
        }

        file >> newNode->correctOption;
        file.ignore();

        if (!qHead)
            qHead = qTail = newNode;
        else {
            qTail->next = newNode;
            qTail = newNode;
        }

        std::getline(file, line); // Consume possible empty line
    }

    file.close();

    std::cout << "\nTake the Test!\n";
    int score = 0, total = 0;

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

    std::cout << "\nTest complete! Your score: " << score << " / " << total << "\n";
    std::cout << "\nPress Enter to return to the menu...";
    std::cin.ignore();
    std::cin.get();
    system("cls");

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
