#pragma once
#include <map>
#include <string>

namespace ProfileManagement {
	class CustomDetails {
		private:
			std::map<std::string, uint16_t> numberElements;
			std::map<std::string, std::string> stringElements;
	public:
        std::map<std::string, uint16_t> getNumberElements() const { return numberElements; }
        void setNumberElements(std::map<std::string, uint16_t> numberElements) { this->numberElements = numberElements; }

        std::map<std::string,std::string> getStringElements() const { return stringElements; }
        void setStringElements(std::map<std::string,std::string> stringElements) { this->stringElements = stringElements; }

};
}