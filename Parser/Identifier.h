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

public:
    Identifier() : value(Code::AN) {}
    Identifier(const Code& code) : value(code) {}
    std::string ToStr();

    void ReadFromStream(std::istream& stream);
};
