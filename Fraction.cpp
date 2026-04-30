#include "Fraction.h"
#include <cmath>
#include <algorithm>

Fraction::Fraction() noexcept(false)
    : integer_part(0), precision(0), sign(1) {
    fractional_digits = nullptr;
}

Fraction::Fraction(long long int_p, int prec, int s) noexcept(false)
    : integer_part(std::abs(int_p)), precision(prec), sign(s >= 0 ? 1 : -1) {
    if (precision < 0) precision = 0;
    if (precision > 0) {
        fractional_digits = new int[precision];
        for (int i = 0; i < precision; ++i) fractional_digits[i] = 0;
    } else {
        fractional_digits = nullptr;
    }
}

Fraction::Fraction(const char* str) noexcept(false) {
    std::string s(str);
    if (s.empty()) {
        integer_part = 0; precision = 0; sign = 1; fractional_digits = nullptr;
        return;
    }
    sign = (s[0] == '-') ? -1 : 1;
    size_t start = (s[0] == '-' || s[0] == '+') ? 1 : 0;
    size_t dot_pos = s.find('.');

    if (dot_pos == std::string::npos) {
        integer_part = std::stoll(s.substr(start));
        precision = 0;
        fractional_digits = nullptr;
    } else {
        integer_part = std::stoll(s.substr(start, dot_pos - start));
        std::string frac_str = s.substr(dot_pos + 1);
        precision = (int)frac_str.length();
        fractional_digits = new int[precision];
        for (int i = 0; i < precision; ++i) {
            fractional_digits[i] = frac_str[i] - '0';
        }
    }
}

Fraction::Fraction(const Fraction& other) noexcept(false)
    : integer_part(other.integer_part), precision(other.precision), sign(other.sign) {
    if (precision > 0) {
        fractional_digits = new int[precision];
        std::copy(other.fractional_digits, other.fractional_digits + precision, fractional_digits);
    } else {
        fractional_digits = nullptr;
    }
}

Fraction::~Fraction() {
    delete[] fractional_digits;
}

Fraction& Fraction::operator=(const Fraction& other) {
    if (this != &other) {
        int* new_digits = nullptr;
        if (other.precision > 0) {
            new_digits = new int[other.precision];
            std::copy(other.fractional_digits, other.fractional_digits + other.precision, new_digits);
        }
        delete[] fractional_digits;
        integer_part = other.integer_part;
        precision = other.precision;
        sign = other.sign;
        fractional_digits = new_digits;
    }
    return *this;
}

int& Fraction::operator[](int index) {
    if (index < 0 || index >= precision) {
        throw std::out_of_range("Index out of fractional bounds");
    }
    return fractional_digits[index];
}

void Fraction::push_back(int digit) noexcept(false) {
    int* new_arr = new int[precision + 1];
    if (precision > 0) {
        std::copy(fractional_digits, fractional_digits + precision, new_arr);
        delete[] fractional_digits;
    }
    new_arr[precision] = std::abs(digit) % 10;
    fractional_digits = new_arr;
    precision++;
}

void Fraction::pop_back() {
    if (precision <= 0) return;
    if (precision == 1) {
        delete[] fractional_digits;
        fractional_digits = nullptr;
        precision = 0;
    } else {
        int* new_arr = new int[precision - 1];
        std::copy(fractional_digits, fractional_digits + precision - 1, new_arr);
        delete[] fractional_digits;
        fractional_digits = new_arr;
        precision--;
    }
}

Fraction::operator double() const {
    double res = (double)integer_part;
    for (int i = 0; i < precision; ++i) {
        res += fractional_digits[i] / std::pow(10.0, i + 1);
    }
    return res * sign;
}

std::string Fraction::to_string() const {
    std::string s = (sign == -1 ? "-" : "");
    s += std::to_string(integer_part);
    if (precision > 0) {
        s += ".";
        for (int i = 0; i < precision; ++i) {
            s += std::to_string(fractional_digits[i]);
        }
    }
    return s;
}

std::ostream& operator<<(std::ostream& os, const Fraction& f) {
    os << f.to_string();
    return os;
}

std::istream& operator>>(std::istream& is, Fraction& f) {
    std::string temp;
    if (is >> temp) {
        try {
            f = Fraction(temp.c_str());
        } catch (...) {
            is.setstate(std::ios::failbit);
        }
    }
    return is;
}