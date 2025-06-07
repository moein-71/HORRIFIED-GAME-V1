#include <format>
#include <iostream>

int main() {
    std::string message = std::format("Hello, {}!" , "world");
    std::cout << message << std::endl;  // Output: Hello, world!
    
    int x = 42;
    double pi = 3.14159;
    auto text = std::format("x = {}, π ≈ {:.2f}", x, pi);
    std::cout << text << std::endl;  // Output: x = 42, π ≈ 3.14
}