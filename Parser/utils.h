#pragma once
#include <fstream>
#include <vector>



namespace geodata {

	namespace parser {

		namespace utils {
			enum class ReadResult;

			void ReadValue(std::istream& stream, uint16_t& value);

			void ReadValue(std::istream& stream, uint32_t& value);

			void ReadValue(std::istream& stream, std::vector<uint8_t>& value, size_t length);

			void SkipRead(std::istream& stream, size_t length);
		}
	}
}
