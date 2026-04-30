#include <iostream>
#include <vector>
#include "Fraction.h"

int main() {
    try {
        Fraction f1("-123.456");
        std::cout << "f1: " << f1 << std::endl;

        f1.push_back(7);
        std::cout << "Після f1.push_back(7): " << f1 << std::endl;

        std::cout << "Цифра на позиції [1]: " << f1[1] << std::endl;

        double d = (double)f1;
        std::cout << "Як double: " << d << std::endl;

        std::vector<int> digits = {1, 2, 3};
        Fraction f2(digits.begin(), digits.end());
        std::cout << "f2 (з ітераторів): " << f2 << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Помилка: " << e.what() << std::endl;
    }
    return 0;
}