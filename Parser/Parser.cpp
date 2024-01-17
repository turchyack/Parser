#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "utils.h"
#include "Identifier.h"
#include "Parser.h"

using namespace geodata::parser::utils;

//возвращает 0 - если прочитан кадр и -1 - достигнут конец потока
int Frame::ReadFromStream(std::istream& stream) {   
    if (stream.peek() == EOF) {
        return -1; 
    }
    ReadValue(stream, this->Version);
    Ident.ReadFromStream(stream);
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
         Frame& frame = Frames[i];
         outputFile << i << "\t" << frame.Ident.ToStr()
            << "\t" << std::hex << std::setw(4) << std::setfill('0') << frame.Address
            << "\t" << std::hex << std::setw(4) << std::setfill('0') << frame.Command
            << "\t" << std::dec << frame.DataLength << std::endl;
    }
    outputFile.close();
}