#pragma once

#include <iostream>
#include <string>
#include <Engine/ProfileManagement/PhysicalCharacteristics.h>
#include <Engine/ProfileManagement/PlayerStatistics.h>
#include <Engine/ProfileManagement/Skills.h>
#include <Engine/ProfileManagement/Achievements.h>
#include <Engine/ProfileManagement/GameSave.h>
#include <vector>
#include <Engine/ProfileManagement/GameSettings.h>

namespace ProfileManagement {
	class Player {
		private:
			std::string userName;
			std::string groupName;
			std::string playerCreationTime;
			uint16_t hoursPlayed = 0;
			std::string lastUpdatedTime;
			PhysicalCharacteristics* physicalCharacteristics;
			PlayerStatistics* playerStatistics;
			Skills skillsList[100]{};
			Achievements achievementsList[100]{};
			GameSave gameSaveList[10]{};
			GameSettings* gameSetting;

		public:
			Player() {
				physicalCharacteristics = new PhysicalCharacteristics();
				playerStatistics = new PlayerStatistics();
				gameSetting = new GameSettings();
			}

			void setSkillsList(Skills i_skillsList) {
				*skillsList = i_skillsList;
			}

			void setUserName(std::string i_userName) {
				userName = i_userName;
			}

			void setGroupName(std::string i_groupName) {
				groupName = i_groupName;
			}

			void setPlayerCreationTime(std::string i_playerCreationTime) {
				playerCreationTime = i_playerCreationTime;
			}

			void setHoursPlayed(uint16_t i_hoursPlayed) {
				hoursPlayed = i_hoursPlayed;
			}

			void setLastUpdatedTime(std::string i_lastUpdatedTime) {
				lastUpdatedTime = i_lastUpdatedTime;
			}

			PhysicalCharacteristics* getPhysicalCharacteristics() {
				return physicalCharacteristics;
			}

			PlayerStatistics* getPlayerStatistics() {
				return playerStatistics;
			}

			Skills* getSkillsList() {
				return skillsList;
			}

			Achievements* getAchievementsList() {
				return achievementsList;
			}

			GameSave* getGameSaveList() {
				return gameSaveList;
			}

			GameSettings* getGameSetting() {
				return gameSetting;
			}

			std::string getUserName() const { return userName; }

			std::string getGroupName() const { return groupName; }

			std::string getPlayerCreationTime() const { return playerCreationTime; }

			uint16_t getHoursPlayed() const { return hoursPlayed; }

			std::string getLastUpdatedTime() const { return lastUpdatedTime; }


};
}