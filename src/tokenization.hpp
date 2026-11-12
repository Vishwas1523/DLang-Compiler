#pragma once
#include <optional>
#include <vector>
#include <string>
enum class tokenType {
    _return,
    int_lit,
    semi
};

struct Token {
    tokenType type;
    std::optional<std::string> value{};
};

class Tokenizer{
public:

explicit Tokenizer(std::string sourceCode): src(std::move(sourceCode)){}

std::vector<Token> tokenize(){
    std::vector<Token> tokens;
    std::string buff;
    while(peek().has_value()){
          if (std::isalpha(peek().value())) {
                buff.push_back(consume());
                while (peek().has_value() && std::isalnum(peek().value())) {
                    buff.push_back(consume());
                }
                if (buff == "return") {
                    tokens.push_back({ .type = tokenType::_return });
                    buff.clear();
                    continue;
                }
                else {
                    std::cerr << "Wrong spelling of return........" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if (std::isdigit(peek().value())) {
                buff.push_back(consume());
                while (peek().has_value() && std::isdigit(peek().value())) {
                    buff.push_back(consume());
                }
                tokens.push_back({ .type = tokenType::int_lit, .value = buff });
                buff.clear();
                continue;
            }
            else if (peek().value() == ';') {
                consume();
                tokens.push_back({ .type = tokenType::semi });
                continue;
            }
            else if (std::isspace(peek().value())) {
                consume();
                continue;
            }
            else {
                std::cerr << "Wrong Code............" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        index = 0;
        return tokens;
}
private:
[[nodiscard]]std::optional<char>peek(int look_ahead = 1) const{
    if(index + look_ahead > src.length()) return{};
    else   return src.at(index);
}
char consume(){
    return src.at(index++);
}
std::string src;
size_t index = 0;
};

