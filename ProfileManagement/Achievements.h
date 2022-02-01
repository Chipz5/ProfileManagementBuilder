#pragma once
#include <cstdint>
#include <string>

namespace ProfileManagement {
	class Achievements {
		private:
			uint8_t id;
			std::string timeUnlocked;

		public:
			
			void setId(uint8_t i_id) {
				id = i_id;
			}

			void setTimeUnlocked(std::string i_timeUnlocked) {
				timeUnlocked = i_timeUnlocked;
			}

			uint8_t getId() const { return id; }

			std::string getTimeUnlocked() const { return timeUnlocked; }

};
}