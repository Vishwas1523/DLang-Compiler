#include <iostream>
#include <cstdlib>
#include <optional>
#include <sstream>
#include <vector>
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
                i--;                
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

int main(int argc, const char** argv) {
    if (argc != 2) {
        std::cerr << "Incorrect input......" << std::endl;
        std::cerr << "Correct usage: DLang input.dl" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Hello World" << std::endl;
    return EXIT_SUCCESS;
}
