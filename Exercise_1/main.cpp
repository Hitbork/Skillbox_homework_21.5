#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct statement {
    std::string name,
                second_name,
                date;
    int summary;
};

std::vector<statement> statements;

bool is_date_right(std::string &date) {
    int dateNumbers[3];

    for (int i = 0; i < 2; i++) {
        dateNumbers[i] = std::stoi(date.substr(0, date.find('.')));
        date.erase(0, date.find('.') + 1);
    }

    dateNumbers[2] = std::stoi(date);

    // Check if month is validating
    if (dateNumbers[1] <= 12) {
        // Check if month is odd number
        if ((dateNumbers[1] % 2 == 1 && dateNumbers[1] <= 7)
            || (dateNumbers[1] % 2 == 0 && dateNumbers[1] >= 8)) {
            return dateNumbers[0] <= 31;
        } else {
            // Check if month isn't February
            if (dateNumbers[1] != 2) {
                return dateNumbers[0] <= 30;
            } else {
                // Check if year is leap
                if (dateNumbers[2] % 4 == 0) {
                    return dateNumbers[0] <= 29;
                } else {
                    return dateNumbers[0] <= 28;
                }
            }
        }
    }
}

void reading_statements() {
    // Opening the flow
    std::ifstream file("statements.txt");

    // Checking if file could be opened
    if (!file.is_open()) {
        std::cout << "Error!\n" <<
                  "\tFile can't be opened!";
        return;
    }

    // Deleting all previous information from vector
    statements.clear();

    // Creating var
    statement currentStatement;

    file >> currentStatement.name;

    // Reading strings until file is ended
    while (!file.eof()) {
        file >> currentStatement.second_name >>
                currentStatement.date >>
                currentStatement.summary;

        statements.push_back(currentStatement);

        file >> currentStatement.name;
    }

    file.close();
}

void output_statements() {
    int counter = 1;

    for (statement currentStatement : statements) {
        std::cout << "Statement #" << counter << std::endl <<
                        "  name: " << currentStatement.name << ";\n" <<
                        "  second name: " << currentStatement.second_name << ";\n" <<
                        "  date: " << currentStatement.date << ";\n" <<
                        "  summary: " << currentStatement.summary << ".\n\n";
        counter++;
    }

    if (counter == 1) {
        std::cout << "There are no statements in the file!";
    }
}

void writing_statement(statement& currentStatement) {
    // Opening the flow
    std::ofstream file;
    file.open("statements.txt",  std::ios::app);

    // Checking if file could be opened
    if (!file.is_open()) {
        std::cout << "Error!\n" <<
                  "\tFile can't be opened!";
        return;
    }

    file << currentStatement.name << " " <<
            currentStatement.second_name << " " <<
            currentStatement.date << " " <<
            currentStatement.summary << "\n";

    file.close();
}


int main() {
    // Greetings
    std::cout << "\tStatements!\n\n\n" << std::endl;

    // Creating cycle
    while (true) {
        // Requesting input
        std::cout << "Insert:\n" <<
                        "  'list' - to view all statements;\n" <<
                        "  'add' - to add new statement.\n\n";

        // Creating var and filling it
        std::string command;
        std::cin >> command;
        std::cout << "\n\n";

        // Checking the command
        if (command == "list") {
            reading_statements();
            output_statements();
        } else if (command == "add") {
            statement currentStatement;
            std::cout << "Insert new statement in this type of string:\n" <<
                        "<name> <second name> <date> <summary>\n";

            std::cin >> currentStatement.name >>
                        currentStatement.second_name >>
                        currentStatement.date >>
                        currentStatement.summary;

            if (is_date_right(currentStatement.date)) {
                writing_statement(currentStatement);
                std::cout << "\nStatement has been added!";
            } else {
                std::cout << "Error! Data is invalid, try again!";
            }
        } else {
            std::cout << "Error! Input is wrong";
        }

        std::cout << "\n\n\n";
    }

    return 0;
}