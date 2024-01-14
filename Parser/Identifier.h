#pragma once
#include <fstream>
#include <string>

class Identifier {
    
public:
    enum class Code {
        AN = 0,
        CO
    };

    Code value;
    Identifier() : value(Code::AN) {}
    Identifier(const Code& code) : value(code) {}
    std::string ToStr() {
        static const char* names[] = { "AN", "CO" };
        return names[static_cast<size_t>(value)]; 
    }

    void ReadFromStream(std::istream& stream) {
        const size_t n = 2;
        char temp[n];
        stream.read(temp, n);

        if (strncmp(temp, "AN", n) == 0) {
            value = Code::AN;
        }
        else if (strncmp(temp, "CO", n) == 0) {
            value = Code::CO;
        }
        else {
            throw std::runtime_error("invalid identifier");
        }
        return;
    }
};
