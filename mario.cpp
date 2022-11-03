#include <iostream>

int main() {
    // Declare variable height as 'h'
    int h;

    // Ask user prompt. If user types < 1, > 8, or non-int, reprompt.

    do {
        std::cout << "Pyramid height: ";
        std::cin >> h;
        // std::cout << "Your pyramid is: " << h << std::endl;
    }
    while (h < 1 || h > 8);

    for (int hashr = 0; hashr < h; hashr++){
        // Create aligned dots/spaces..
        for (int dot = 0; dot < h - hashr - 1; dot++){
            printf(" ");
        }
        // For each column..
        for (int hashc = 0; hashc <= hashr; hashc++){
            // Print a brick..
            printf("#");
        }
        // Move to next row.
        printf("\n");
    }
}