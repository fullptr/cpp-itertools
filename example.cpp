#include "cpp-itertools.h"

#include <iostream>
#include <vector>

#include <cppcoro/generator.hpp>

int main()
{
    std::vector<int> example{2, 4, 6, 8, 10, 12};
    std::vector<std::string> example2{"Man", "Woman", "Person", "Camera", "TV"};

    std::cout << "\nExample:\n";
    for (auto& x : example) {
        std::cout << x << "\n";
    }

    std::cout << "\nReversed:\n";
    for (auto& x : itertools::reversed(example)) {
        std::cout << x << "\n";
    }

    std::cout << "\nEnumerated:\n";
    for (auto& [i, x] : itertools::enumerate(example)) {
        std::cout << i << " -> " << x << "\n";
    }

    std::cout << "\nEnumerated from 10:\n";
    for (auto& [i, x] : itertools::enumerate(example, 10)) {
        std::cout << i << " -> " << x << "\n";
    }

    std::cout << "\nZipped with vector of strings:\n";
    for (auto& [left, right] : itertools::zip(example, example2)) {
        std::cout << left << ", " << right << "\n";
    }
}