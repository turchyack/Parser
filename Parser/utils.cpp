#include <fstream>
#include <vector>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")


namespace utils {

    void ReadValue(std::istream& stream, uint16_t& value) {
        uint16_t temp = 0;
        stream.read(reinterpret_cast<char*>(&temp), sizeof(temp));
        if (static_cast<size_t>(stream.gcount()) < sizeof(temp)) {
            throw std::runtime_error("Wrong format: unexpected EOF");
        }
        value = htons(temp);
    }

    void ReadValue(std::istream& stream, uint32_t& value) {
        uint32_t temp = 0;
        stream.read(reinterpret_cast<char*>(&temp), sizeof(temp));
        if (static_cast<size_t>(stream.gcount()) < sizeof(temp)) {
            throw std::runtime_error("Wrong format: unexpected EOF");
        }
        value = htonl(temp);
    }

    void ReadValue(std::istream& stream, std::vector<uint8_t>& value, size_t length) {
        value.resize(length);
        stream.read(reinterpret_cast<char*>(value.data()), length);
        if (static_cast<size_t>(stream.gcount()) < length) {
            throw std::runtime_error("Wrong format: unexpected EOF");
        }
    }

    void SkipRead(std::istream& stream, size_t length) {
        const size_t n = 1;
        char temp[n];
        for (size_t i = 0; i < length; ++i) {
            stream.read(temp, n);
            if (static_cast<size_t>(stream.gcount()) < n) {
                throw std::runtime_error("Wrong format: unexpected EOF");
            }
        }
    }

}