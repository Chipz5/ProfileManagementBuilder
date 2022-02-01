#pragma once
#include <cstdint>
#include <string>
namespace ProfileManagement {
	enum SaveType {
		AutoSave,
		CheckPoint,
		QuickSave,

	};

	class GameSave {
		private:

			uint8_t saveType;
			uint8_t checkPointId;
			std::string timeOfSave;

		public:

			void setSaveType(uint8_t i_saveType) {
				saveType = i_saveType;
			}

			void setCheckPointId(uint8_t i_checkPointId) {
				checkPointId = i_checkPointId;
			}

			void setTimeOfSave(std::string i_timeOfSave) {
				timeOfSave = i_timeOfSave;
			}

			uint8_t getSaveType() const { return saveType; }

			uint8_t getCheckPointId() const { return checkPointId; }

			std::string getTimeOfSave() const { return timeOfSave; }

};
}
