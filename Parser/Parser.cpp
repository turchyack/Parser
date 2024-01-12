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
    }                                                           */                                // переделать на енумы пока не работает
}












void read_file(const std::string& fpath) {
    printf("debug: read_file(%s)\n", fpath.c_str());

    auto file = std::ifstream(fpath, std::ios::binary);
   
    const size_t block_size = 100;
    while (true) {
        Frame frame;

        read_value(file, frame.Version);
        read_value(file, *frame.Identifier);
        skip_read(file, 18);
        read_value(file, frame.Address);
        read_value(file, frame.Command);
        read_value(file, frame.DataLength);
        std::cout << frame.DataLength << std::endl;
        read_value(file, frame.Data, frame.DataLength);
        
        read_value(file, frame.Checksum);
        read_value(file, frame.EndMarker);
        std::cout << file.tellg() << std::endl;
        int a;
        std::cin >> a;
       

       // read_value(file, frame.Version);
      ////  read_value(file, *frame.Identifier);
      //  read_value(file, frame.DataLength);
      ////  frame.DataLength = 32;
      //  read_value(file, frame.Data, frame.DataLength);




       /* for (uint8_t elem : frame.Data) {
            std::cout <<std::hex << elem << "-";
        }
        std::cout << std::hex << frame.Data.data() << std::endl;*/
      //  read_value(file, frame.Data, frame.DataLength);
               
      
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
