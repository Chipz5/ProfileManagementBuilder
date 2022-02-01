#include <Engine/ProfileManagement/ProfileManager.h>
#include <Engine/ProfileManagement/ReadPlayerDetails.h>
#include <Engine/Platform/Platform.h>
#include <fstream>

eae6320::cResult ProfileManagement::ProfileManager::LoadPlayerDetails(std::string playerDetails, ProfileManagement::Player* player)
{
	//ReadPlayerDetails(playerDetails, player);

	std::string* o_errorMessage = nullptr;
	eae6320::Platform::sDataFromFile o_data;

	eae6320::Platform::LoadBinaryFile(playerDetails.c_str(), o_data, o_errorMessage);

	auto currentOffset = reinterpret_cast<uintptr_t>(o_data.data);
	const auto finalOffset = currentOffset + o_data.size;
	//player
	player->setUserName(reinterpret_cast<char*>(currentOffset));
	currentOffset += sizeof(std::string);
	player->setGroupName(reinterpret_cast<char*>(currentOffset));
	currentOffset += sizeof(std::string);
	player->setPlayerCreationTime(reinterpret_cast<char*>(currentOffset));
	currentOffset += sizeof(std::string);
	player->setHoursPlayed(*reinterpret_cast<uint16_t*>(currentOffset));
	currentOffset += (sizeof(uint16_t));
	player->setLastUpdatedTime(reinterpret_cast<char*>(currentOffset));
	currentOffset += sizeof(std::string);
	//physical characteristics
	player->getPhysicalCharacteristics()->setSkin(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += sizeof(uint8_t);
	player->getPhysicalCharacteristics()->setHair(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += sizeof(uint8_t);
	player->getPhysicalCharacteristics()->setShirt(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += sizeof(uint8_t);
	player->getPhysicalCharacteristics()->setPants(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += sizeof(uint8_t);
	float eyeColorRed = *reinterpret_cast<float*>(currentOffset);
	currentOffset += sizeof(float);
	float eyeColorBlue = *reinterpret_cast<float*>(currentOffset);
	currentOffset += sizeof(float);
	float eyeColorGreen = *reinterpret_cast<float*>(currentOffset);
	currentOffset += sizeof(float);
	player->getPhysicalCharacteristics()->setEyeColor(eyeColorRed, eyeColorBlue, eyeColorGreen);
	float hairColorRed = *reinterpret_cast<float*>(currentOffset);
	currentOffset += sizeof(float);
	float hairColorBlue = *reinterpret_cast<float*>(currentOffset);
	currentOffset += sizeof(float);
	float hairColorGreen = *reinterpret_cast<float*>(currentOffset);
	currentOffset += sizeof(float);
	player->getPhysicalCharacteristics()->setHairColor(hairColorRed, hairColorBlue, hairColorGreen);
	//stats
	player->getPlayerStatistics()->setHealth(*reinterpret_cast<uint64_t*>(currentOffset));
	currentOffset += sizeof(uint64_t);
	player->getPlayerStatistics()->setEnergy(*reinterpret_cast<uint64_t*>(currentOffset));
	currentOffset += sizeof(uint64_t);
	player->getPlayerStatistics()->setDamage(*reinterpret_cast<uint64_t*>(currentOffset));
	currentOffset += sizeof(uint64_t);
	player->getPlayerStatistics()->setXp(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += sizeof(uint8_t);
	player->getPlayerStatistics()->setTotalLosses(*reinterpret_cast<uint16_t*>(currentOffset));
	currentOffset += sizeof(uint16_t);
	player->getPlayerStatistics()->setTotalWins(*reinterpret_cast<uint16_t*>(currentOffset));
	currentOffset += sizeof(uint16_t);
	player->getPlayerStatistics()->setPoints(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += sizeof(uint8_t);
	//skills
	for (int i = 0; i < 100;i++) {
		player->getSkillsList()[i].setId(*reinterpret_cast<uint64_t*>(currentOffset));
		currentOffset += (sizeof(uint64_t));
		player->getSkillsList()[i].setMasteryLevel(*reinterpret_cast<uint8_t*>(currentOffset));
		currentOffset += (sizeof(uint8_t));
	}
	//achievements
	for (int i = 0; i < 100; i++) {
		player->getAchievementsList()[i].setId(*reinterpret_cast<uint8_t*>(currentOffset));
		currentOffset += (sizeof(uint8_t));
		player->getAchievementsList()[i].setTimeUnlocked(reinterpret_cast<char*>(currentOffset));
		currentOffset += sizeof(std::string);
	}
	//game save
	for (int i = 0; i < 10; i++) {
		player->getGameSaveList()[i].setSaveType(*reinterpret_cast<uint8_t*>(currentOffset));
		currentOffset += (sizeof(uint8_t));
		player->getGameSaveList()[i].setCheckPointId(*reinterpret_cast<uint8_t*>(currentOffset));
		currentOffset += (sizeof(uint8_t));
		player->getGameSaveList()[i].setTimeOfSave(reinterpret_cast<char*>(currentOffset));
		currentOffset += sizeof(std::string);
	}
	//input controls
	player->getGameSetting()->getInputControls()->setInputType(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getInputControls()->setUp(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getInputControls()->setDown(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getInputControls()->setLeft(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getInputControls()->setRight(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getInputControls()->setPrimaryAttack(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getInputControls()->setSecondaryAttack(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getInputControls()->setParry(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getInputControls()->setDuck(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getInputControls()->setJump(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getInputControls()->setAction(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	//audio
	player->getGameSetting()->getAudioSettings()->setMasterVolume(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getAudioSettings()->setMusicVolume(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getAudioSettings()->setDialogueVolume(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getAudioSettings()->setSoundEffectsVolume(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getAudioSettings()->setIsKillStreakMusic(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getAudioSettings()->setGameSoundDevice(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getAudioSettings()->setMainMusicVolume(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getAudioSettings()->setMainMenuVolume(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getAudioSettings()->setRoundStartVolume(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getAudioSettings()->setRoundEndVolume(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	//voice chat
	player->getGameSetting()->getVoiceChatSettings()->setIsVoiceChatOn(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getVoiceChatSettings()->setVoiceChatDevice(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getVoiceChatSettings()->setMicrophoneDevice(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getVoiceChatSettings()->setVoiceChatVolume(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getVoiceChatSettings()->setMicrophoneVolume(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	player->getGameSetting()->getVoiceChatSettings()->setIsPlayAudioWhenGameInBackground(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	//video
	player->getGameSetting()->getVideoSettings()->setResolution(*reinterpret_cast<float*>(currentOffset));
	currentOffset += (sizeof(float));
	player->getGameSetting()->getVideoSettings()->setTextureQuality(*reinterpret_cast<uint8_t*>(currentOffset));
	currentOffset += (sizeof(uint8_t));
	return eae6320::cResult();
}

eae6320::cResult ProfileManagement::ProfileManager::WritePlayerDetails(std::string playerDetails, ProfileManagement::Player* player)
{
	std::string pathContent = PROJPATH;
	std::string path = pathContent.append(playerDetails);
	std::ofstream outfile(path, std::ofstream::out);

	outfile << "return {"<<std::endl;
	//player

	outfile << "player = {" << std::endl;
	outfile << "userName = \"" << player->getUserName() << "\"," << std::endl;
	outfile << "groupName = \"" << player->getGroupName() << "\"," << std::endl;
	outfile << "playerCreationTime = \"" << player->getPlayerCreationTime() << "\"," << std::endl;
	outfile << "hoursPlayed = " << (int)player->getHoursPlayed() <<"," << std::endl;
	outfile << "lastUpdatedTime = \"" << player->getLastUpdatedTime() << "\"," << std::endl;
	outfile << "}," << std::endl;

	//physical characteristics

	float eyeColorRed = player->getPhysicalCharacteristics()->getEyeColor().red;
	float eyeColorBlue = player->getPhysicalCharacteristics()->getEyeColor().blue;
	float eyeColorGreen = player->getPhysicalCharacteristics()->getEyeColor().green;
	float hairColorRed = player->getPhysicalCharacteristics()->getHairColor().red;
	float hairColorBlue = player->getPhysicalCharacteristics()->getHairColor().blue;
	float hairColorGreen = player->getPhysicalCharacteristics()->getHairColor().green;
	outfile << "physicalCharacteristics = {" << std::endl;
	outfile << "skin = " << (int)player->getPhysicalCharacteristics()->getSkin() << "," << std::endl;
	outfile << "hair = " << (int)player->getPhysicalCharacteristics()->getHair() << "," << std::endl;
	outfile << "shirt = " << (int)player->getPhysicalCharacteristics()->getShirt() << "," << std::endl;
	outfile << "pants = " << (int)player->getPhysicalCharacteristics()->getPants() << "," << std::endl;
	outfile << "eyeColor = {" << eyeColorRed <<","<<eyeColorBlue<<","<<eyeColorGreen << "}," << std::endl;
	outfile << "hairColor = {" << hairColorRed << "," << hairColorBlue << "," << hairColorGreen << "}," << std::endl;
	outfile << "}," << std::endl;

	//player stats

	outfile << "playerStatistics = {" << std::endl;
	outfile << "health = " << (int)player->getPlayerStatistics()->getHealth() << "," << std::endl;
	outfile << "energy = " << (int)player->getPlayerStatistics()->getEnergy() << "," << std::endl;
	outfile << "damage = " << (int)player->getPlayerStatistics()->getDamage() << "," << std::endl;
	outfile << "xp = " << (int)player->getPlayerStatistics()->getXp() << "," << std::endl;
	outfile << "totalLosses = " << (int)player->getPlayerStatistics()->getTotalLosses() << "," << std::endl;
	outfile << "totalWins = " << (int)player->getPlayerStatistics()->getTotalWins() << "," << std::endl;
	outfile << "points = " << (int)player->getPlayerStatistics()->getPoints() << "," << std::endl;
	outfile << "}," << std::endl;

	//skills

	outfile << "skills = {" << std::endl;
	for (int i = 0; i < 100;++i) {
		if (player->getSkillsList()[i].getId() == 0) {
			continue;
		}
		outfile << "{" << std::endl;
		outfile << "id = " << (int)player->getSkillsList()[i].getId() << "," << std::endl;
		outfile << "masteryLevel = " << (int)player->getSkillsList()[i].getMasteryLevel() << "," << std::endl;
		outfile << "}," << std::endl;
	}
	outfile << "}," << std::endl;

	//achievements

	outfile << "achievements = {" << std::endl;
	for (int i = 0; i < 100; ++i) {
		if (player->getAchievementsList()[i].getId() == 0) {
			continue;
		}
		outfile << "{" << std::endl;
		outfile << "id = " << (int)player->getAchievementsList()[i].getId() << "," << std::endl;
		outfile << "timeUnlocked = \"" << player->getAchievementsList()[i].getTimeUnlocked() << "\"," << std::endl;
		outfile << "}," << std::endl;
	}
	outfile << "}," << std::endl;

	//game save
	
	outfile << "gameSave = {" << std::endl;
	for (int i = 0; i < 10; ++i) {
		if (player->getGameSaveList()[i].getSaveType() == 0) {
			continue;
		}
		outfile << "{" << std::endl;
		outfile << "saveType = " << (int)player->getGameSaveList()[i].getSaveType() << "," << std::endl;
		outfile << "checkPointId = " << (int)player->getGameSaveList()[i].getCheckPointId() << "," << std::endl;
		outfile << "timeOfSave = \"" << player->getGameSaveList()[i].getTimeOfSave() << "\"," << std::endl;
		outfile << "}," << std::endl;
	}
	outfile << "}," << std::endl;

	//input controls

	outfile << "inputControls = {" << std::endl;
	outfile << "inputType = " << (int)player->getGameSetting()->getInputControls()->getInputType() << "," << std::endl;
	outfile << "up = " << (int)player->getGameSetting()->getInputControls()->getUp() << "," << std::endl;
	outfile << "down = " << (int)player->getGameSetting()->getInputControls()->getDown() << "," << std::endl;
	outfile << "left = " << (int)player->getGameSetting()->getInputControls()->getLeft() << "," << std::endl;
	outfile << "right = " << (int)player->getGameSetting()->getInputControls()->getRight() << "," << std::endl;
	outfile << "primaryAttack = " << (int)player->getGameSetting()->getInputControls()->getPrimaryAttack() << "," << std::endl;
	outfile << "secondaryAttack = " << (int)player->getGameSetting()->getInputControls()->getSecondaryAttack() << "," << std::endl;
	outfile << "parry = " << (int)player->getGameSetting()->getInputControls()->getParry() << "," << std::endl;
	outfile << "duck = " << (int)player->getGameSetting()->getInputControls()->getDuck() << "," << std::endl;
	outfile << "jump = " << (int)player->getGameSetting()->getInputControls()->getJump() << "," << std::endl;
	outfile << "action = " << (int)player->getGameSetting()->getInputControls()->getAction() << "," << std::endl;
	outfile << "}," << std::endl;

	//audio

	outfile << "audioSettings = {" << std::endl;
	outfile << "masterVolume = " << (int)player->getGameSetting()->getAudioSettings()->getMasterVolume() << "," << std::endl;
	outfile << "musicVolume = " << (int)player->getGameSetting()->getAudioSettings()->getMusicVolume() << "," << std::endl;
	outfile << "dialogueVolume = " << (int)player->getGameSetting()->getAudioSettings()->getDialogueVolume() << "," << std::endl;
	outfile << "soundEffectsVolume = " << (int)player->getGameSetting()->getAudioSettings()->getSoundEffectsVolume() << "," << std::endl;
	outfile << "killStreakMusic = " << (int)player->getGameSetting()->getAudioSettings()->getKillStreakMusic() << "," << std::endl;
	outfile << "gameSoundDevice = " << (int)player->getGameSetting()->getAudioSettings()->getGameSoundDevice() << "," << std::endl;
	outfile << "mainMusicVolume = " << (int)player->getGameSetting()->getAudioSettings()->getMainMusicVolume() << "," << std::endl;
	outfile << "mainMenuVolume = " << (int)player->getGameSetting()->getAudioSettings()->getMainMenuVolume() << "," << std::endl;
	outfile << "roundStartVolume = " << (int)player->getGameSetting()->getAudioSettings()->getRoundStartVolume() << "," << std::endl;
	outfile << "roundEndVolume = " << (int)player->getGameSetting()->getAudioSettings()->getRoundEndVolume() << "," << std::endl;
	outfile << "}," << std::endl;

	//voice

	outfile << "voiceChatSettings = {" << std::endl;
	outfile << "isVoiceChatOn = " << (int)player->getGameSetting()->getVoiceChatSettings()->getIsVoiceChatOn() << "," << std::endl;
	outfile << "voiceChatDevice = " << (int)player->getGameSetting()->getVoiceChatSettings()->getVoiceChatDevice() << "," << std::endl;
	outfile << "microphoneDevice = " << (int)player->getGameSetting()->getVoiceChatSettings()->getMicrophoneDevice() << "," << std::endl;
	outfile << "voiceChatVolume = " << (int)player->getGameSetting()->getVoiceChatSettings()->getVoiceChatVolume() << "," << std::endl;
	outfile << "microphoneVolume = " << (int)player->getGameSetting()->getVoiceChatSettings()->getMicrophoneVolume() << "," << std::endl;
	outfile << "playAudioWhenGameInBackground = " << (int)player->getGameSetting()->getVoiceChatSettings()->getPlayAudioWhenGameInBackground() << "," << std::endl;
	outfile << "}," << std::endl;


	//video

	outfile << "videoSettings = {" << std::endl;
	outfile << "resolution = " << player->getGameSetting()->getVideoSettings()->getResolution() << "," << std::endl;
	outfile << "textureQuality = " << (int)player->getGameSetting()->getVideoSettings()->getTextureQuality() << "," << std::endl;
	outfile << "}," << std::endl;

	outfile << "}";
	outfile.close();
	return eae6320::cResult();
}

eae6320::cResult ProfileManagement::ProfileManager::LoadCustomDetails(std::string customDetailsFile, ProfileManagement::CustomDetails* customDetails)
{
	std::string* o_errorMessage = nullptr;
	eae6320::Platform::sDataFromFile o_data;

	eae6320::Platform::LoadBinaryFile(customDetailsFile.c_str(), o_data, o_errorMessage);

	auto currentOffset = reinterpret_cast<uintptr_t>(o_data.data);
	const auto finalOffset = currentOffset + o_data.size;
	std::map<std::string, std::string> stringElements;
	std::map<std::string, uint16_t> numbers;
	int i = 0;
	while (1) {
		i++;
		std::string a = reinterpret_cast<char*>(currentOffset);
		if (a == "ENDSTRING" || i > 100)
			break;
		currentOffset += sizeof(std::string);

		std::string b = reinterpret_cast<char*>(currentOffset);
		currentOffset += sizeof(std::string);
		stringElements.insert(std::pair<std::string, std::string>(a, b));

	}
	currentOffset += sizeof(std::string);
	i = 0;
	while (1) {
		i++;
		std::string c = reinterpret_cast<char*>(currentOffset);
		if (c == "ENDNUMBER" || i > 100)
			break;
		currentOffset += sizeof(std::string);

		auto d = *reinterpret_cast<uint16_t*>(currentOffset);
		currentOffset += sizeof(uint16_t);
		numbers.insert(std::pair<std::string, uint16_t>(c, d));
	}
	
	customDetails->setStringElements(stringElements);
	customDetails->setNumberElements(numbers);
	
	return eae6320::cResult();
}
