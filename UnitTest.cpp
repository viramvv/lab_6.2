#include <gtest/gtest.h>
#include "Fraction.h"
#include <vector>

// Тест конструктора з рядка та перетворення в string
TEST(FractionTest, StringConstructorAndToString) {
    Fraction f("-123.456");
    EXPECT_EQ(f.to_string(), "-123.456");
}

// Тест конструктора з ітераторів
TEST(FractionTest, IteratorConstructor) {
    std::vector<int> digits = {1, 0, 5};
    Fraction f(digits.begin(), digits.end());
    // Очікуємо 0.105 (integer_part = 0 за замовчуванням у цьому конструкторі)
    EXPECT_EQ(f.to_string(), "0.105");
}

// Тест оператора індексування та зміни значень
TEST(FractionTest, IndexingOperator) {
    Fraction f("0.123");
    EXPECT_EQ(f[1], 2);
    f[1] = 9;
    EXPECT_EQ(f.to_string(), "0.193");
}

// Тест виходу за межі індексу (обробка винятків)
TEST(FractionTest, IndexOutOfRange) {
    Fraction f("1.2");
    EXPECT_THROW(f[5], std::out_of_range);
}

// Тест додавання елементів (push_back)
TEST(FractionTest, PushBackTest) {
    Fraction f("1.2");
    f.push_back(3);
    f.push_back(4);
    EXPECT_EQ(f.to_string(), "1.234");
}

// Тест перетворення в double
TEST(FractionTest, DoubleConversion) {
    Fraction f("-1.5");
    double d = (double)f;
    EXPECT_NEAR(d, -1.5, 0.0001);
}

// Тест оператора присвоєння
TEST(FractionTest, AssignmentOperator) {
    Fraction f1("10.5");
    Fraction f2;
    f2 = f1;
    EXPECT_EQ(f2.to_string(), "10.5");
    f1[0] = 9; // Перевірка, що копія глибока (динамічна пам'ять)
    EXPECT_NE(f1.to_string(), f2.to_string());
}