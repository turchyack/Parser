#pragma once
#include <cstring>
#include <cstdint>
#include "Identifier.h"
#include <vector>
#include <iostream>

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