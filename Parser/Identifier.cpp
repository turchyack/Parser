#include "Identifier.h"





//static const char* names[] = { "AN", "CO" };



void Identifier::ReadFromStream(std::istream& stream) {
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
std::string Identifier::ToStr() {
     static const char* names[] = { "AN", "CO" };




    return names[static_cast<size_t>(value)];
}
