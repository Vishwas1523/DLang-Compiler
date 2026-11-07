#include <iostream>
#include <cstdlib>
#include <optional>
#include <sstream>

enum class tokenType {
    _return,
    int_lit,
    semi
};

struct Token {
    tokenType type;
    std::optional<std::string> value{};
};

int main(int argc, const char** argv) {
    if (argc != 2) {
        std::cerr << "Incorrect input......" << std::endl;
        std::cerr << "Correct usage: DLang input.dl" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Hello World" << std::endl;
    return EXIT_SUCCESS;
}
