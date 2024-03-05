#include <iostream>
#include <cmath>

// Struct of vector
struct vector {
    double x = 0, y = 0;

    vector(int number) {
        // Defining the number of vector
        std::cout << "Data of " << number << " vector:\n\n";

        // Requesting coordinates of vector
        std::cout << "Insert x:\n";
        std::cin >> this->x;
        std::cout << "\n";

        std::cout << "Insert y:\n";
        std::cin >> this->y;
        std::cout << "\n\n";
    };

    void output() const {
        std::cout << "X: " << this->x <<
                    "\nY: " << this->y <<
                    "\n\n";
    }
};

// Functions for operations of vectors
void add() {
    // Creating vars
    vector vec1(1), vec2(2);

    // Adding second vector to first
    vec1.x += vec2.x;
    vec1.y += vec2.y;

    // Outputting results
    std::cout << "Summary of 2 vectors:\n";
    vec1.output();
}

void subtract() {
    // Creating vars
    vector vec1(1), vec2(2);

    // Subtracting 2nd vector from first
    vec1.x -= vec2.y;
    vec1.y -= vec2.y;

    // Outputting results
    std::cout << "Subtraction result is:\n";
    vec1.output();
}

void scale() {
    // Creating vars
    vector vec1(1);
    double scalar;

    // Requesting scalar
    std::cout << "Insert scalar:\n";
    std::cin >> scalar;
    std::cout << "\n\n";

    // Counting multiplication
    vec1.x *= scalar;
    vec1.y *= scalar;

    // Outputting results
    std::cout << "Result of multiplication:\n";
    vec1.output();
}

void length() {
    // Creating vars
    vector vec(1);
    double result = 0;

    // Counting result
    result = sqrt(pow(vec.x, 2) + pow(vec.y, 2));

    // Outputting results
    std::cout << "Length of vector is " << result << "\n\n";
}

void normalize() {
    // Creating vars
    vector vec(1);
    double len = 0;

    // Counting result
    len = sqrt(pow(vec.x, 2) + pow(vec.y, 2));
    vec.x /= len;
    vec.y /= len;

    // Outputting results
    std::cout << "Result of normalizing vector:\n";
    vec.output();
}


int main() {
    // Greetings
    std::cout << "\tVector operations\n\n\n";

    std::string input;
    do {
        std::cout << "Insert the command from below:\n" <<
                        " 'add' - to count summary of two vectors,\n" <<
                        " 'subtract' - to subtract 2nd vector from 1st,\n" <<
                        " 'scale' - to multiply vector on scalar,\n" <<
                        " 'length' - to define vectors length,\n" <<
                        " 'normalize' - to normalize vector,\n" <<
                        " 'exit' - to stop program.\n\n";

        std::cin >> input;
        std::cout << "\n\n";

        if (input == "add")
            add();
        else if (input == "subtract")
            subtract();
        else if (input == "scale")
            scale();
        else if (input == "length")
            length();
        else if (input == "normalize")
            normalize();
        else if (input == "exit")
            std::cout << "Exiting program...\n";
        else {
            std::cout << "Wrong input!\n";
            std::cout << "Try to insert command again!\n\n\n";
        }
    } while (input != "exit");

    return 0;
}
