#pragma once
#include "tokenization.hpp"
#include <iostream>
struct NodeExpr {
    Token int_lit;
};

struct NodeReturn {
    NodeExpr expr;
};

class Parser {
public:
    explicit Parser(std::vector<Token> srcTokens)
        : tokens(std::move(srcTokens))
    {
    }

    std::optional<NodeExpr> parse_expr()
    {
        if (peek().has_value() && peek().value().type == tokenType::int_lit) {
            return NodeExpr { .int_lit = consume() };
        }
        else {
            return {};
        }
    }

    std::optional<NodeReturn> parse()
    {
        std::optional<NodeReturn> exit_node;
        while (peek().has_value()) {
            if (peek().value().type == tokenType::_return) {
                consume();
                if (auto node_expr = parse_expr()) {
                    exit_node = NodeReturn { .expr = node_expr.value() };
                }
                else {
                    std::cerr << "Invalid expression" << std::endl;
                    exit(EXIT_FAILURE);
                }
                if (peek().has_value() && peek().value().type == tokenType::semi) {
                    consume();
                }
                else {
                    std::cerr << "Invalid expression" << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
        index = 0;
        return exit_node;
    }

private:
    [[nodiscard]] inline std::optional<Token> peek(int ahead = 1) const
    {
        if (index + ahead > tokens.size()) {
            return {};
        }
        else {
            return tokens.at(index);
        }
    }

    inline Token consume()
    {
        return tokens.at(index++);
    }

    const std::vector<Token> tokens;
    size_t index = 0;
};