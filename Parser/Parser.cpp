#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

class Frame {
public:
    uint16_t Version;
    std::string Identifier;
    uint16_t Address;
    uint16_t Command;
    uint32_t DataLength;
    std::vector<uint8_t> Data;
    uint16_t Checksum;
    uint16_t EndMarker;
};

void read_value(std::istream& stream, uint16_t& value) {
    stream.read(reinterpret_cast<char*>(&value), sizeof(value));
    std::cout << value << std::endl;
   if (static_cast<size_t>(stream.gcount()) < sizeof(value)) {
        return;
    }
}

void read_file(const std::string& fpath) {
    printf("debug: read_file(%s)\n", fpath.c_str());

    auto file = std::ifstream(fpath, std::ios::binary);
   
    const size_t block_size = 100;
    while (true) {
        Frame frame;
        
        read_value(file, frame.Version);
      
    }
}

class FrameParser {
private:
    std::vector<Frame> Frames;
public:
    void LoadFromFile(const std::string& fileName) {
      // std::ifstream file(fileName, std::ios::binary);
        read_file(fileName);
       
    }

    void SaveToText(const std::string& txtFileName) {
    }

};




int main() {
    FrameParser frameParser;
    frameParser.LoadFromFile("test.raw");
  //  frameParser.SaveToText("output.txt");

    return 0;
}
