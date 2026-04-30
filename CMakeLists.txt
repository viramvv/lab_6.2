cmake_minimum_required(VERSION 3.14)
project(FractionLab)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Додаємо вихідні файли класу
set(FRACTION_SOURCES Fraction.cpp Fraction.h)

# Створюємо бібліотеку з нашого класу, щоб використовувати її і в main, і в тестах
add_library(FractionLib ${FRACTION_SOURCES})

# Головна програма
add_executable(lab_6_2 main.cpp)
target_link_libraries(lab_6_2 FractionLib)

# --- Налаштування Google Test ---
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# Для Windows: Force gtest to link to the main.cpp as a library
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Створення виконуваного файлу для тестів
add_executable(FractionTests UnitTest.cpp)
target_link_libraries(FractionTests FractionLib gtest_main)

# Дозволяємо виявлення тестів у IDE (CLion)
include(GoogleTest)
gtest_discover_tests(FractionTests)