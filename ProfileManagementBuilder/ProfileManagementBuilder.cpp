
#include "ProfileManagementBuilder.h"

#include <Tools/AssetBuildLibrary/Functions.h>
#include <Engine/Platform/Platform.h>
#include <Engine/Results/cResult.h>
#include <fstream>
#include <string>
#include <Engine/Time/Time.h>
#include <iostream>
#include <Engine/ProfileManagement/Player.h>
#include <Engine/ProfileManagement/CustomDetails.h>
#include <Engine/ProfileManagement/Skills.h>
#include <Tools/ProfileManagementBuilder/ReadCustomDetails.h>
#include <Tools/ProfileManagementBuilder/ReadPlayerDetails.h>

// Inherited Implementation
//=========================

// Build
//------


void writePlayerDetailsToBinaryFile(const char* m_path_target, ProfileManagement::Player* player) {
	std::ofstream outfile(m_path_target, std::ofstream::binary);

	uint16_t hoursPlayed = player->getHoursPlayed();

	outfile.write(player->getUserName().c_str(), sizeof(std::string));
	outfile.write(player->getGroupName().c_str(), sizeof(std::string));
	outfile.write(player->getPlayerCreationTime().c_str(), sizeof(std::string));
	outfile.write((char*)&hoursPlayed, sizeof(uint16_t));
	outfile.write(player->getLastUpdatedTime().c_str(), sizeof(std::string));

	//player characteristics
	uint8_t skin = player->getPhysicalCharacteristics()->getSkin();
	uint8_t hair = player->getPhysicalCharacteristics()->getHair();
	uint8_t shirt = player->getPhysicalCharacteristics()->getShirt();
	uint8_t pants = player->getPhysicalCharacteristics()->getPants();
	float eyeColorRed = player->getPhysicalCharacteristics()->getEyeColor().red;
	float eyeColorBlue = player->getPhysicalCharacteristics()->getEyeColor().blue;
	float eyeColorGreen = player->getPhysicalCharacteristics()->getEyeColor().green;
	float hairColorRed = player->getPhysicalCharacteristics()->getHairColor().red;
	float hairColorBlue = player->getPhysicalCharacteristics()->getHairColor().blue;
	float hairColorGreen = player->getPhysicalCharacteristics()->getHairColor().green;
	outfile.write((char*)&skin, sizeof(uint8_t));
	outfile.write((char*)&hair, sizeof(uint8_t));
	outfile.write((char*)&shirt, sizeof(uint8_t));
	outfile.write((char*)&pants, sizeof(uint8_t));
	outfile.write((char*)&eyeColorRed, sizeof(float));
	outfile.write((char*)&eyeColorBlue, sizeof(float));
	outfile.write((char*)&eyeColorGreen, sizeof(float));
	outfile.write((char*)&hairColorRed, sizeof(float));
	outfile.write((char*)&hairColorBlue, sizeof(float));
	outfile.write((char*)&hairColorGreen, sizeof(float));
	//stats
	uint64_t health = player->getPlayerStatistics()->getHealth();
	uint64_t energy = player->getPlayerStatistics()->getEnergy();
	uint64_t damage = player->getPlayerStatistics()->getDamage();
	uint8_t xp = player->getPlayerStatistics()->getXp();
	uint16_t totalLosses = player->getPlayerStatistics()->getTotalLosses();
	uint16_t totalWins = player->getPlayerStatistics()->getTotalWins();
	uint8_t points = player->getPlayerStatistics()->getPoints();
	outfile.write((char*)&health, sizeof(uint64_t));
	outfile.write((char*)&energy, sizeof(uint64_t));
	outfile.write((char*)&damage, sizeof(uint64_t));
	outfile.write((char*)&xp, sizeof(uint8_t));
	outfile.write((char*)&totalLosses, sizeof(uint16_t));
	outfile.write((char*)&totalWins, sizeof(uint16_t));
	outfile.write((char*)&points, sizeof(uint8_t));
	//skills
	uint64_t skillsId;
	uint8_t masteryLevel;

	for (int i = 0; i < 100; i++) {
		skillsId = player->getSkillsList()[i].getId();
		masteryLevel = player->getSkillsList()[i].getMasteryLevel();
		outfile.write((char*)&skillsId, sizeof(uint64_t));
		outfile.write((char*)&masteryLevel, sizeof(uint8_t));
	}
	//achievements
	uint8_t achievementsId;
	for (int i = 0; i < 100; i++) {
		achievementsId = player->getAchievementsList()[i].getId();
		outfile.write((char*)&achievementsId, sizeof(uint8_t));
		outfile.write(player->getAchievementsList()[i].getTimeUnlocked().c_str(), sizeof(std::string));
	}
	//gameSave
	uint8_t saveType;
	uint8_t checkPointId;
	for (int i = 0; i < 10; i++) {
		saveType = player->getGameSaveList()[i].getSaveType();
		checkPointId = player->getGameSaveList()[i].getCheckPointId();

		outfile.write((char*)&saveType, sizeof(uint8_t));
		outfile.write((char*)&checkPointId, sizeof(uint8_t));
		outfile.write(player->getGameSaveList()[i].getTimeOfSave().c_str(), sizeof(std::string));
	}
	//inputcontrols
	uint8_t inputType = player->getGameSetting()->getInputControls()->getInputType(); //whether keyboard (0) or controller (1)
	uint8_t up = player->getGameSetting()->getInputControls()->getUp();
	uint8_t down = player->getGameSetting()->getInputControls()->getDown();
	uint8_t left = player->getGameSetting()->getInputControls()->getLeft();
	uint8_t right = player->getGameSetting()->getInputControls()->getRight();
	uint8_t primaryAttack = player->getGameSetting()->getInputControls()->getPrimaryAttack();
	uint8_t secondaryAttack = player->getGameSetting()->getInputControls()->getSecondaryAttack();
	uint8_t parry = player->getGameSetting()->getInputControls()->getParry();
	uint8_t duck = player->getGameSetting()->getInputControls()->getDuck();
	uint8_t jump = player->getGameSetting()->getInputControls()->getJump();
	uint8_t action = player->getGameSetting()->getInputControls()->getAction();

	outfile.write((char*)&inputType, sizeof(uint8_t));
	outfile.write((char*)&up, sizeof(uint8_t));
	outfile.write((char*)&down, sizeof(uint8_t));
	outfile.write((char*)&left, sizeof(uint8_t));
	outfile.write((char*)&right, sizeof(uint8_t));
	outfile.write((char*)&primaryAttack, sizeof(uint8_t));
	outfile.write((char*)&secondaryAttack, sizeof(uint8_t));
	outfile.write((char*)&parry, sizeof(uint8_t));
	outfile.write((char*)&duck, sizeof(uint8_t));
	outfile.write((char*)&jump, sizeof(uint8_t));
	outfile.write((char*)&action, sizeof(uint8_t));

	//audio
	uint8_t masterVolume = player->getGameSetting()->getAudioSettings()->getMasterVolume();
	uint8_t musicVolume = player->getGameSetting()->getAudioSettings()->getMusicVolume();
	uint8_t dialogueVolume = player->getGameSetting()->getAudioSettings()->getDialogueVolume();
	uint8_t soundEffectsVolume = player->getGameSetting()->getAudioSettings()->getSoundEffectsVolume();
	uint8_t killStreakMusic = player->getGameSetting()->getAudioSettings()->getKillStreakMusic(); //either on or off
	uint8_t gameSoundDevice = player->getGameSetting()->getAudioSettings()->getGameSoundDevice(); //whether sound o/p should be sent to speakers or headphones
	uint8_t mainMusicVolume = player->getGameSetting()->getAudioSettings()->getMainMusicVolume();
	uint8_t mainMenuVolume = player->getGameSetting()->getAudioSettings()->getMainMenuVolume();
	uint8_t roundStartVolume = player->getGameSetting()->getAudioSettings()->getRoundStartVolume();
	uint8_t roundEndVolume = player->getGameSetting()->getAudioSettings()->getRoundEndVolume();

	outfile.write((char*)&masterVolume, sizeof(uint8_t));
	outfile.write((char*)&musicVolume, sizeof(uint8_t));
	outfile.write((char*)&dialogueVolume, sizeof(uint8_t));
	outfile.write((char*)&soundEffectsVolume, sizeof(uint8_t));
	outfile.write((char*)&killStreakMusic, sizeof(uint8_t));
	outfile.write((char*)&gameSoundDevice, sizeof(uint8_t));
	outfile.write((char*)&mainMusicVolume, sizeof(uint8_t));
	outfile.write((char*)&mainMenuVolume, sizeof(uint8_t));
	outfile.write((char*)&roundStartVolume, sizeof(uint8_t));
	outfile.write((char*)&roundEndVolume, sizeof(uint8_t));

	//voice chat
	uint8_t isVoiceChatOn = player->getGameSetting()->getVoiceChatSettings()->getIsVoiceChatOn();
	uint8_t voiceChatDevice = player->getGameSetting()->getVoiceChatSettings()->getVoiceChatDevice();
	uint8_t microphoneDevice = player->getGameSetting()->getVoiceChatSettings()->getMicrophoneDevice();
	uint8_t voiceChatVolume = player->getGameSetting()->getVoiceChatSettings()->getVoiceChatVolume();
	uint8_t microphoneVolume = player->getGameSetting()->getVoiceChatSettings()->getMicrophoneVolume();
	uint8_t playAudioWhenGameInBackground = player->getGameSetting()->getVoiceChatSettings()->getPlayAudioWhenGameInBackground();
	outfile.write((char*)&isVoiceChatOn, sizeof(uint8_t));
	outfile.write((char*)&voiceChatDevice, sizeof(uint8_t));
	outfile.write((char*)&microphoneDevice, sizeof(uint8_t));
	outfile.write((char*)&voiceChatVolume, sizeof(uint8_t));
	outfile.write((char*)&microphoneVolume, sizeof(uint8_t));
	outfile.write((char*)&playAudioWhenGameInBackground, sizeof(uint8_t));

	//video
	float resolution = player->getGameSetting()->getVideoSettings()->getResolution();
	uint8_t textureQuality = player->getGameSetting()->getVideoSettings()->getTextureQuality();
	outfile.write((char*)&resolution, sizeof(float));
	outfile.write((char*)&textureQuality, sizeof(uint8_t));
	outfile.close();
}

void writeCustomDetailsToBinaryFile(const char* m_path_target, ProfileManagement::CustomDetails* customDetails) {
	std::ofstream outfile(m_path_target, std::ofstream::binary);

	auto c = customDetails->getStringElements();
	for (std::map<std::string, std::string>::iterator it = c.begin(); it != c.end(); it++)
	{
		outfile.write(it->first.c_str(), sizeof(std::string));
		outfile.write(it->second.c_str(), sizeof(std::string));
	}

	std::string end = "ENDSTRING";
	outfile.write(end.c_str(), sizeof(std::string));
	auto d = customDetails->getNumberElements();
	for (std::map<std::string, uint16_t>::iterator it = d.begin(); it != d.end(); it++)
	{
		outfile.write(it->first.c_str(), sizeof(std::string));
		outfile.write((char*)&it->second, sizeof(uint16_t));
	}
	std::string end1 = "ENDNUMBER";
	outfile.write(end1.c_str(), sizeof(std::string));
	outfile.close();
}

eae6320::cResult eae6320::Assets::ProfileManagementBuilder::Build(const std::vector<std::string>& i_arguments)
{
	std::string* o_errorMessage = nullptr;
	eae6320::cResult result = eae6320::Platform::CopyFile(m_path_source, m_path_target, false, true, o_errorMessage);
	if (o_errorMessage != nullptr)
	{
		OutputErrorMessageWithFileInfo(m_path_source, o_errorMessage->c_str());
	}

	std::string path = m_path_source;
	ProfileManagement::CustomDetails* customDetails = new ProfileManagement::CustomDetails();
	if (path.find("custom") != std::string::npos) {
		ReadCustomDetails(path, customDetails);
		writeCustomDetailsToBinaryFile(m_path_target, customDetails);
	} 
	else {
		ProfileManagement::Player* player = new ProfileManagement::Player();
		ReadPlayerDetails(m_path_source, player);
		writePlayerDetailsToBinaryFile(m_path_target, player);
	}
	
	return result;
}
