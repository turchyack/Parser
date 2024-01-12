#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

class Frame {
public:
    uint16_t Version;
    char Identifier[2];
    uint16_t Address;
    uint16_t Command;
    uint32_t DataLength;
    std::vector<uint8_t> Data;
    uint16_t Checksum;
    uint16_t EndMarker;
    int read_from_stream(std::istream& stream);
};

void read_value(std::istream& stream, uint16_t& value) {
    stream.read(reinterpret_cast<char*>(&value), sizeof(value));
    value = htons(value);
    if (static_cast<size_t>(stream.gcount()) < sizeof(value)) {
        return;
    }
}
void read_value(std::istream& stream, uint32_t& value) {

    stream.read(reinterpret_cast<char*>(&value), sizeof(value));  
    value = htonl(value);
    if (static_cast<size_t>(stream.gcount()) < sizeof(value)) {
        return;
    }
}
void read_value(std::istream& stream, std::vector<uint8_t>& value, size_t length) {
    value.resize(length);
    stream.read(reinterpret_cast<char*>(value.data()), length);
    if (static_cast<size_t>(stream.gcount()) < length) {
        return;
    }
}
void skip_read(std::istream& stream, size_t value) {

    stream.seekg(value, stream.cur);


}
void read_value(std::istream& stream, char& value) {

    skip_read(stream, 2);
   /* stream.read(&value, sizeof(value));
    std::cout << sizeof(value) <<"DEBUG   gogoo  " << value << std::dec << std::endl;
    
    std::cout << value << std::dec << std::endl;
   
    if (static_cast<size_t>(stream.gcount()) < sizeof(value)) {
        return;
    }                                                           */                                // переделать на енумы пока не работает (костыль)
}




class FrameParser {
private:
    std::vector<Frame> Frames;
public:
    void read_file(const std::string& fpath);

    void LoadFromFile(const std::string& fileName) {
        read_file(fileName);
        
    }

    void SaveToText(const std::string& txtFileName);

};




int main() {
    FrameParser frameParser;
    frameParser.LoadFromFile("test.raw");
  //  frameParser.SaveToText("output.txt");

    return 0;
}

int Frame::read_from_stream(std::istream& stream)
{
    read_value(stream, this->Version);
    read_value(stream, *this->Identifier);
    skip_read(stream, 18);
    read_value(stream, this->Address);
    read_value(stream, this->Command);
    read_value(stream, this->DataLength);
    std::cout << this->DataLength << std::endl;
    read_value(stream, this->Data, this->DataLength);

    read_value(stream, this->Checksum);
    read_value(stream, this->EndMarker);
    std::cout << stream.tellg() << std::endl;
    if (stream.tellg() <=0) {
        return -1;
    }
}

void FrameParser::read_file(const std::string& fpath) {
    printf("debug: read_file(%s)\n", fpath.c_str());

    auto file = std::ifstream(fpath, std::ios::binary);

    while (true) {
        Frame frame;
        if (frame.read_from_stream(file) == -1) {
            break;
        }
        Frames.push_back(frame);

    }
    std::cout << "File is readed" << std::endl;
}

