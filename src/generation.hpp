#pragma once
#include <sstream>
#include "parse.hpp"

class Generator {
public:
    inline explicit Generator(NodeReturn srcRoot)
        : root(std::move(srcRoot))
    {
    }

    [[nodiscard]] std::string generate() const
    {
        std::stringstream output;
        output << "global _start\n_start:\n";
        output << "    mov rax, 60\n";
        output << "    mov rdi, " << root.expr.int_lit.value.value() << "\n";
        output << "    syscall";
        return output.str();
    }

private:
    const NodeReturn root;
};