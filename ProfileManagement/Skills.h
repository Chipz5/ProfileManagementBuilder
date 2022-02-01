#pragma once
#include <cstdint>

namespace ProfileManagement {
	class Skills {
		private:
			uint64_t id;
			uint8_t masteryLevel;

		public:
			
			void setId(uint64_t i_id) {
				id = i_id;
			}

			void setMasteryLevel(uint8_t i_masteryLevel) {
				masteryLevel = i_masteryLevel;
			}


			uint64_t getId() const { return id; }

			uint8_t getMasteryLevel() const { return masteryLevel; }

};
}