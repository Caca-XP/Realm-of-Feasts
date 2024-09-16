#include <iostream>

int main() {
    // Regular colors
    std::cout << "\033[31m" << "This text is red!" << "\033[0m" << std::endl;  // Red text
    std::cout << "\033[32m" << "This text is green!" << "\033[0m" << std::endl;  // Green text
    std::cout << "\033[33m" << "This text is yellow!" << "\033[0m" << std::endl;  // Yellow text
    std::cout << "\033[34m" << "This text is blue!" << "\033[0m" << std::endl;  // Blue text
    std::cout << "\033[35m" << "This text is magenta!" << "\033[0m" << std::endl;  // Magenta text
    std::cout << "\033[36m" << "This text is cyan!" << "\033[0m" << std::endl;  // Cyan text
    std::cout << "\033[37m" << "This text is white!" << "\033[0m" << std::endl;  // White text
    
    // Bright colors
    std::cout << "\033[91m" << "This text is bright red!" << "\033[0m" << std::endl;
    std::cout << "\033[92m" << "This text is bright green!" << "\033[0m" << std::endl;
    std::cout << "\033[93m" << "This text is bright yellow!" << "\033[0m" << std::endl;
    std::cout << "\033[94m" << "This text is bright blue!" << "\033[0m" << std::endl;
    std::cout << "\033[95m" << "This text is bright magenta!" << "\033[0m" << std::endl;
    std::cout << "\033[96m" << "This text is bright cyan!" << "\033[0m" << std::endl;
    std::cout << "\033[97m" << "This text is bright white!" << "\033[0m" << std::endl;

    return 0;
}
