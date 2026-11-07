#include <iostream>
#include <cstdlib>
#include <optional>
#include <sstream>
#include <vector>
#include <fstream>
enum class tokenType {
    _return,
    int_lit,
    semi
};

struct Token {
    tokenType type;
    std::optional<std::string> value{};
};

std::vector<Token> tokenize(const std::string& str){
    std::vector<Token> tokens;
    std::string buff;
    for(int i = 0; i < str.length(); i++){
        char temp = str.at(i);
        if(std::isalpha(temp)){
            buff.push_back(temp);
            i++;
            while(std::isalnum(str.at(i))){
                buff.push_back(str.at(i));
                i++;
            }
            i--;
            if(buff == "return"){
                tokens.push_back({.type = tokenType::_return});
                buff.clear();
                continue;                
            } else{
                std::cerr<<"Wrong spelling...!"<<std::endl;
                exit(EXIT_FAILURE);
            }
        } else if(std::isdigit(temp)){
            buff.push_back(temp);
            i++;
            while(std::isdigit(str.at(i))){
                buff.push_back(str.at(i));
                i++;
            }
            i--;
            tokens.push_back({.type = tokenType::int_lit, .value = buff});
            buff.clear();
        } else if(temp == ';'){
            tokens.push_back({.type = tokenType :: semi});
        } else if(std::isspace(temp)){
            continue;
        } else{
            std::cerr<<"Your code is wrong......"<<std::endl;
            exit(EXIT_FAILURE);
        }

    }
    return tokens;
}

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
