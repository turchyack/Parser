#include "Identifier.h"
#include <iostream>


static const char* CodeNames[] = { "AN", "CO" };

void Identifier::ReadFromStream(std::istream& stream) {
    const size_t n = 2;
    char temp[n];
    stream.read(temp, n);
    const size_t N = sizeof(CodeNames)/sizeof(CodeNames[0]);
    for (size_t i = 0; i < N; ++i) {
        if (strncmp(temp, CodeNames[i], n) == 0) {
            value = static_cast<Code>(i);
            return;
        }
    }
    throw std::runtime_error("invalid identifier");

}

std::string Identifier::ToStr() {
    return CodeNames[static_cast<size_t>(value)];
}
