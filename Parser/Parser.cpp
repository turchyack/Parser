﻿#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "utils.h"
#include "Identifier.h"

class Frame {

public:
    uint16_t Version;
    Identifier Ident;
    size_t ServiceInfo = 18;
    uint16_t Address;
    uint16_t Command;
    uint32_t DataLength;
    std::vector<uint8_t> Data;
    uint16_t Checksum;
    uint16_t EndMarker;

    int ReadFromStream(std::istream& stream);
};

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
    utils::ReadValue(stream, this->Version);
    Ident.ReadFromStream(stream);
    utils::SkipRead(stream, this->ServiceInfo);
    utils::ReadValue(stream, this->Address);
    utils::ReadValue(stream, this->Command);
    utils::ReadValue(stream, this->DataLength);
    utils::ReadValue(stream, this->Data, this->DataLength);
    utils::ReadValue(stream, this->Checksum);
    utils::ReadValue(stream, this->EndMarker);
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
         Frame& frame = Frames[i];
         outputFile << i << "\t" << frame.Ident.ToStr()
            << "\t" << std::hex << std::setw(4) << std::setfill('0') << frame.Address
            << "\t" << std::hex << std::setw(4) << std::setfill('0') << frame.Command
            << "\t" << std::dec << frame.DataLength << std::endl;
    }
    outputFile.close();
}