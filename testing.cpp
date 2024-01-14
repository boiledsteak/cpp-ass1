#include <iostream>

void detectEnterKey() {
    std::cout << "Press Enter to continue..." << std::endl;

    // Loop until the Enter key is pressed
    while (true) {
        char ch = std::cin.get(); // Get a character from input

        if (ch == '\n') {
            // Enter key pressed, break out of the loop
            break;
        }
    }

    std::cout << "You pressed Enter! Program continues..." << std::endl;
}

int main() {
    detectEnterKey();

    return 0;
}
