#include <iostream>

#define HEIGHT 10
#define S_HEIGHT 2
#define S_WIDTH 3


int main() {

    for (int i = 0; i <= HEIGHT - 1; i++) {
        for (int j = 0; j <= HEIGHT - i; j++) {
            std::cout << " ";
        }
        for (int j = 0; j <= i * 2; j++) {
            std::cout << "*";
        }
        std::cout << "\n";
    }

    for (int i = 0; i <= S_HEIGHT - 1; i++) {
        for (int j = 0; j <= HEIGHT - (S_WIDTH / 2); j++) {
            std::cout << " ";
        }
        for (int j = 0; j <= S_WIDTH - 1; j++) {
            std::cout << "I";
        }
        std::cout << "\n";
    }

    return 0;
}
