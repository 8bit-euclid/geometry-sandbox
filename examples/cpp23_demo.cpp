#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <format>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // C++23 ranges and views
    auto even_doubled = numbers 
        | std::views::filter([](int n) { return n % 2 == 0; })
        | std::views::transform([](int n) { return n * 2; });
    
    std::cout << "Even numbers doubled: ";
    for (auto n : even_doubled) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // C++20 format (available in C++23)
    std::cout << std::format("Total numbers processed: {}\n", numbers.size());
    
    return 0;
}
