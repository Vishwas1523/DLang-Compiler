#include <iostream>
#include <cstdlib>
#include <optional>
#include <sstream>
#include <vector>
#include <fstream>
#include "tokenization.hpp"

std::string token_to_asm(const std::vector<Token>& tokens){
    std::stringstream temp;
    temp << "global _start\n_start:\n";
    for(int i = 0; i < tokens.size(); i++){
        const Token& token = tokens.at(i);
        if(token.type == tokenType::_return){
            if((i + 1) < tokens.size() && tokens.at(i + 1).type == tokenType::int_lit){
                if((i + 2) < tokens.size() && tokens.at(i + 2).type == tokenType::int_lit){
                    temp << "   move rax, 60\n";
                    temp << "   move rdi, " <<  tokens.at(i+1).value.value() << "\n";
                    temp << "   syscall"; 
                }
            }
        }
    }
    return temp.str();
}

int main(int argc, const char** argv) {
    if (argc != 2) {
        std::cerr << "Incorrect input......" << std::endl;
        std::cerr << "Correct usage: DLang input.dl" << std::endl;
        return EXIT_FAILURE;
    }
    std::string inputFile;
    {   
        std::stringstream input_stream;
        std::fstream input(argv[1], std::ios::in);
        input_stream << input.rdbuf();
        inputFile = input_stream.str();
    }
    std::vector<Token> tokens = tokenize(inputFile);
    {
        std::fstream file("output.asm", std::ios::out);
        file << token_to_asm(tokens);
    }

    system("nasm -felf64 output.asm");
    system("ld -o output output.o");

    return EXIT_SUCCESS;
}
