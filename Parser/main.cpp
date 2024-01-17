#include "Parser.h"



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
