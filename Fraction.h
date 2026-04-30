#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <new>
#include <iterator>

class Fraction {
private:
    long long integer_part;
    int* fractional_digits;
    int precision;
    int sign;

public:
    Fraction() noexcept(false);
    Fraction(long long int_p, int prec, int s) noexcept(false);

    template <typename Iterator>
    Fraction(Iterator begin, Iterator end) noexcept(false) {
        precision = (int)std::distance(begin, end);
        integer_part = 0;
        sign = 1;
        if (precision > 0) {
            fractional_digits = new int[precision];
            int i = 0;
            for (auto it = begin; it != end; ++it) {
                fractional_digits[i++] = *it % 10;
            }
        } else {
            fractional_digits = nullptr;
        }
    }

    Fraction(const char* str) noexcept(false);
    Fraction(const Fraction& other) noexcept(false);

    ~Fraction();

    Fraction& operator=(const Fraction& other);
    int& operator[](int index);

    void push_back(int digit) noexcept(false);
    void pop_back();

    operator double() const;
    std::string to_string() const;

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
    friend std::istream& operator>>(std::istream& is, Fraction& f);
};

#endif