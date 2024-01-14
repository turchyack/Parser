#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstring>
#include "utils.h"
#include "Identifier.h"
#include "Parser.h"


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