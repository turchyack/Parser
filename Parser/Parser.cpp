#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")


using namespace std;

class Frame {
public:
    uint16_t Version;
    string Identifier;
    uint16_t Address;
    uint16_t Command;
    uint32_t DataLength;
    vector<uint8_t> Data;
    uint16_t Checksum;
    uint16_t EndMarker;
};

class FrameParser {
private:
    std::vector<Frame> Frames;
public:
    void LoadFromFile(const string& fileName) {
        ifstream file(fileName, ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << fileName << std::endl;
            return;
        }
        while (file.peek() != EOF) {
            Frame frame;

            file.read(reinterpret_cast<char*>(&frame.Version), sizeof(uint16_t));
            char identifier[2];
            file.read(identifier, 2);
            frame.Identifier = string(identifier, 2);
            file.seekg(22);
            file.read(reinterpret_cast<char*>(&frame.Address), sizeof(uint16_t));

            frame.Address = htons(frame.Address);

            file.read(reinterpret_cast<char*>(&frame.Command), sizeof(uint16_t));

            file.read(reinterpret_cast<char*>(&frame.DataLength), sizeof(uint32_t));
   
            frame.DataLength = htonl(frame.DataLength);

            frame.Data.resize(frame.DataLength);

            file.read(reinterpret_cast<char*>(&frame.Data[0]), frame.DataLength);
          
            file.read(reinterpret_cast<char*>(&frame.Checksum), sizeof(uint16_t));


            file.read(reinterpret_cast<char*>(&frame.EndMarker), sizeof(uint16_t));

            Frames.push_back(frame);
        }

        file.close();
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
