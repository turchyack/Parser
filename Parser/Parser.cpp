#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <winsock2.h>
#include <cstring>
#pragma comment(lib, "Ws2_32.lib")

enum class Identification : uint16_t {
    AN = 0,
    CO
};

const char* IdentifierToStr(const Identification& value) {
    static const char* names[] = { "AN", "CO" };
    return names[static_cast<size_t>(value)];
}

class Frame {
public:
    uint16_t Version;
    Identification Identifier;
    size_t ServiceInfo = 18;
    uint16_t Address;
    uint16_t Command;
    uint32_t DataLength;
    std::vector<uint8_t> Data;
    uint16_t Checksum;
    uint16_t EndMarker;

    int ReadFromStream(std::istream& stream);
};

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

void ReadValue(std::istream& stream, Identification& value) {
    const size_t n = 2;
    char temp[n];
    stream.read(temp, n);

    if (strncmp(temp, "AN", n)==0) {
        value = Identification::AN;
    }
    else if (strncmp(temp, "CO", n)==0) {
        value = Identification::CO;
    }
    else {
        throw std::runtime_error("invalid identifier");
    }
    return;
}

class FrameParser {
private:
    std::vector<Frame> Frames;
public:
    void LoadFromFile(const std::string& fileName);
    void SaveToText(const std::string& txtFileName);
};


int main() {
    try {
        FrameParser frameParser;
        frameParser.LoadFromFile("test.raw");
        frameParser.SaveToText("output.txt");
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}

//возвращает 0 - если прочитан кадр и -1 - достигнут конец потока
int Frame::ReadFromStream(std::istream& stream) {   
    if (stream.peek() == EOF) {
        return -1; 
    }
    ReadValue(stream, this->Version);
    ReadValue(stream, this->Identifier);
    SkipRead(stream, this->ServiceInfo);
    ReadValue(stream, this->Address);
    ReadValue(stream, this->Command);
    ReadValue(stream, this->DataLength);
    ReadValue(stream, this->Data, this->DataLength);
    ReadValue(stream, this->Checksum);
    ReadValue(stream, this->EndMarker);
}

void FrameParser::LoadFromFile(const std::string& fpath) {
    auto file = std::ifstream(fpath, std::ios::binary);
    while (true) {
        Frame frame;
        if (frame.ReadFromStream(file) == -1) {
            break;
        }
        Frames.push_back(frame);
    }
}

void FrameParser::SaveToText(const std::string& txtFileName) {
    std::ofstream outputFile(txtFileName);
    outputFile << "index\tid\taddress\tcommand\tdataLength\n";
    for (size_t i = 0; i < Frames.size(); ++i) {
        const Frame& frame = Frames[i];
        outputFile << i << "\t" << IdentifierToStr(frame.Identifier)
            << "\t" << std::hex << std::setw(4) << std::setfill('0') << frame.Address
            << "\t" << std::hex << std::setw(4) << std::setfill('0') << frame.Command
            << "\t" << std::dec << frame.DataLength << std::endl;
    }
    outputFile.close();
}