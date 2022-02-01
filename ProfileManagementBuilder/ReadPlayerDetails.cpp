#include "ReadPlayerDetails.h"
#include <External/Lua/Includes.h>
#include <Engine/ScopeGuard/cScopeGuard.h>
#include <Engine/Asserts/Asserts.h>
#include <iostream>
#include <Engine/ProfileManagement/Skills.h>

namespace {
	eae6320::cResult LoadAsset(const char* const i_path, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_player(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_player_values(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_physicalCharacteristics(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_physicalCharacteristics_values(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_physicalCharacteristics_eyeColor_subvalues(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_physicalCharacteristics_hairColor_subvalues(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_playerStatistics(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_playerStatistics_values(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_skills(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_skills_values(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_achievements(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_achievements_values(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_gameSave(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_gameSave_values(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_inputControls(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_inputControls_values(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_audioSettings(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_audioSettings_values(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_voiceChatSettings(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_voiceChatSettings_values(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_videoSettings(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_videoSettings_values(lua_State& io_luaState, ProfileManagement::Player* player);
}

eae6320::cResult ReadPlayerDetails(std::string playerFile, ProfileManagement::Player* player) {
	auto result = eae6320::Results::Success;

	const char* const path = playerFile.c_str();
	if (!(result = LoadAsset(path, player)))
	{
		return result;
	}

	return result;
}

namespace {

	eae6320::cResult LoadTableValues(lua_State& io_luaState, ProfileManagement::Player* player)
	{
		auto result = eae6320::Results::Success;

		if (!(result = LoadTableValues_player(io_luaState, player)))
		{
			return result;
		}

		if (!(result = LoadTableValues_physicalCharacteristics(io_luaState, player)))
		{
			return result;
		}

		if (!(result = LoadTableValues_playerStatistics(io_luaState, player)))
		{
			return result;
		}

		if (!(result = LoadTableValues_skills(io_luaState, player)))
		{
			return result;
		}

		if (!(result = LoadTableValues_achievements(io_luaState, player)))
		{
			return result;
		}

		if (!(result = LoadTableValues_achievements(io_luaState, player)))
		{
			return result;
		}

		if (!(result = LoadTableValues_gameSave(io_luaState, player)))
		{
			return result;
		}

		if (!(result = LoadTableValues_inputControls(io_luaState, player)))
		{
			return result;
		}

		if (!(result = LoadTableValues_audioSettings(io_luaState, player)))
		{
			return result;
		}

		if (!(result = LoadTableValues_voiceChatSettings(io_luaState, player)))
		{
			return result;
		}

		if (!(result = LoadTableValues_videoSettings(io_luaState, player)))
		{
			return result;
		}

		return result;
	}

	// game save

	eae6320::cResult LoadTableValues_gameSave(lua_State& io_luaState, ProfileManagement::Player* player)
	{
		auto result = eae6320::Results::Success;

		constexpr auto* const key = "gameSave";
		lua_pushstring(&io_luaState, key);
		lua_gettable(&io_luaState, -2);

		eae6320::cScopeGuard scopeGuard_popTextures([&io_luaState]
			{
				lua_pop(&io_luaState, 1);
			});

		if (lua_istable(&io_luaState, -1))
		{
			if (!(result = LoadTableValues_gameSave_values(io_luaState, player)))
			{
				return result;
			}
		}
		else
		{
			result = eae6320::Results::InvalidFile;
			std::cerr << "The value at \"" << key << "\" must be a table "
				"(instead of a " << luaL_typename(&io_luaState, -1) << ")" << std::endl;
			return result;
		}

		return result;
	}

	eae6320::cResult LoadTableValues_gameSave_values(lua_State& io_luaState, ProfileManagement::Player* player) {

		auto result = eae6320::Results::Success;
		int gameSaveCount = (int)luaL_len(&io_luaState, -1);
		if (gameSaveCount > 10) {
			result = eae6320::Results::InvalidFile;
			std::cerr << "The number of gameSaves is too high " << std::endl;
			return result;
		}
		ProfileManagement::GameSave* gameSave;
		for (int i = 1; i <= gameSaveCount; ++i)
		{
			gameSave = new ProfileManagement::GameSave();
			lua_pushinteger(&io_luaState, i);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popTexturePath([&io_luaState]
				{
					lua_pop(&io_luaState, 1);
				});
			//saveType
			{
				constexpr auto* const key = "saveType";
				lua_pushstring(&io_luaState, key);
				lua_gettable(&io_luaState, -2);
				eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
				uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
				gameSave->setSaveType(value);
			}

			//checkPointId
			{
				constexpr auto* const key = "checkPointId";
				lua_pushstring(&io_luaState, key);
				lua_gettable(&io_luaState, -2);
				eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
				uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
				gameSave->setCheckPointId(value);
			}

			//timeOfSave
			{
				constexpr auto* const key = "timeOfSave";
				lua_pushstring(&io_luaState, key);
				lua_gettable(&io_luaState, -2);
				eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
				std::string value = lua_tostring(&io_luaState, -1);
				gameSave->setTimeOfSave(value);
			}
			player->getGameSaveList()[i - 1] = *gameSave;
		}


		return result;
	}



	// achievements

	eae6320::cResult LoadTableValues_achievements(lua_State& io_luaState, ProfileManagement::Player* player)
	{
		auto result = eae6320::Results::Success;

		constexpr auto* const key = "achievements";
		lua_pushstring(&io_luaState, key);
		lua_gettable(&io_luaState, -2);

		eae6320::cScopeGuard scopeGuard_popTextures([&io_luaState]
			{
				lua_pop(&io_luaState, 1);
			});

		if (lua_istable(&io_luaState, -1))
		{
			if (!(result = LoadTableValues_achievements_values(io_luaState, player)))
			{
				return result;
			}
		}
		else
		{
			result = eae6320::Results::InvalidFile;
			std::cerr << "The value at \"" << key << "\" must be a table "
				"(instead of a " << luaL_typename(&io_luaState, -1) << ")" << std::endl;
			return result;
		}

		return result;
	}

	eae6320::cResult LoadTableValues_achievements_values(lua_State& io_luaState, ProfileManagement::Player* player) {

		auto result = eae6320::Results::Success;
		int achievementsCount = (int)luaL_len(&io_luaState, -1);
		if (achievementsCount > 100) {
			result = eae6320::Results::InvalidFile;
			std::cerr << "The number of achievements is too high " << std::endl;
			return result;
		}
		ProfileManagement::Achievements* achievements;
		for (int i = 1; i <= achievementsCount; ++i)
		{
			achievements = new ProfileManagement::Achievements();
			lua_pushinteger(&io_luaState, i);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popTexturePath([&io_luaState]
				{
					lua_pop(&io_luaState, 1);
				});
			//id
			{
				constexpr auto* const key = "id";
				lua_pushstring(&io_luaState, key);
				lua_gettable(&io_luaState, -2);
				eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
				uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
				achievements->setId(value);
			}

			//time unlocked
			{
				constexpr auto* const key = "timeUnlocked";
				lua_pushstring(&io_luaState, key);
				lua_gettable(&io_luaState, -2);
				eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
				std::string value = lua_tostring(&io_luaState, -1);
				achievements->setTimeUnlocked(value);
			}

			player->getAchievementsList()[i - 1] = *achievements;
		}

		return result;
	}


	// skills

	eae6320::cResult LoadTableValues_skills(lua_State& io_luaState, ProfileManagement::Player* player)
	{
		auto result = eae6320::Results::Success;

		constexpr auto* const key = "skills";
		lua_pushstring(&io_luaState, key);
		lua_gettable(&io_luaState, -2);

		eae6320::cScopeGuard scopeGuard_popTextures([&io_luaState]
			{
				lua_pop(&io_luaState, 1);
			});

		if (lua_istable(&io_luaState, -1))
		{
			if (!(result = LoadTableValues_skills_values(io_luaState, player)))
			{
				return result;
			}
		}
		else
		{
			result = eae6320::Results::InvalidFile;
			std::cerr << "The value at \"" << key << "\" must be a table "
				"(instead of a " << luaL_typename(&io_luaState, -1) << ")" << std::endl;
			return result;
		}

		return result;
	}

	eae6320::cResult LoadTableValues_skills_values(lua_State& io_luaState, ProfileManagement::Player* player) {

		auto result = eae6320::Results::Success;
		int skillsCount = (int)luaL_len(&io_luaState, -1);
		if (skillsCount > 100) {
			result = eae6320::Results::InvalidFile;
			std::cerr << "The number of skills is too high " << std::endl;
			return result;
		}

		ProfileManagement::Skills* skills;
		for (int i = 1; i <= skillsCount; ++i)
		{
			skills = new ProfileManagement::Skills();
			lua_pushinteger(&io_luaState, i);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popTexturePath([&io_luaState]
				{
					lua_pop(&io_luaState, 1);
				});

			//id
			{
				constexpr auto* const key = "id";
				lua_pushstring(&io_luaState, key);
				lua_gettable(&io_luaState, -2);
				eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
				uint64_t value = (uint64_t)lua_tonumber(&io_luaState, -1);
				skills->setId(value);

				//player->getSkills()->setId(value);
			}

			//mastery level
			{
				constexpr auto* const key = "masteryLevel";
				lua_pushstring(&io_luaState, key);
				lua_gettable(&io_luaState, -2);
				eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
				uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
				skills->setMasteryLevel(value);
				//player->getSkills()->setMasteryLevel(value);
			}
			player->getSkillsList()[i - 1] = *skills;

		}

		return result;
	}

	// player statistics

	eae6320::cResult LoadTableValues_playerStatistics(lua_State& io_luaState, ProfileManagement::Player* player)
	{
		auto result = eae6320::Results::Success;

		constexpr auto* const key = "playerStatistics";
		lua_pushstring(&io_luaState, key);
		lua_gettable(&io_luaState, -2);

		eae6320::cScopeGuard scopeGuard_popTextures([&io_luaState]
			{
				lua_pop(&io_luaState, 1);
			});

		if (lua_istable(&io_luaState, -1))
		{
			if (!(result = LoadTableValues_playerStatistics_values(io_luaState, player)))
			{
				return result;
			}
		}
		else
		{
			result = eae6320::Results::InvalidFile;
			std::cerr << "The value at \"" << key << "\" must be a table "
				"(instead of a " << luaL_typename(&io_luaState, -1) << ")" << std::endl;
			return result;
		}

		return result;
	}

	eae6320::cResult LoadTableValues_playerStatistics_values(lua_State& io_luaState, ProfileManagement::Player* player) {

		auto result = eae6320::Results::Success;

		//health
		{
			constexpr auto* const key = "health";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint64_t value = (uint64_t)lua_tonumber(&io_luaState, -1);
			player->getPlayerStatistics()->setHealth(value);
		}

		//energy
		{
			constexpr auto* const key = "energy";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint64_t value = (uint64_t)lua_tonumber(&io_luaState, -1);
			player->getPlayerStatistics()->setEnergy(value);
		}

		//damage
		{
			constexpr auto* const key = "damage";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint64_t value = (uint64_t)lua_tonumber(&io_luaState, -1);
			player->getPlayerStatistics()->setDamage(value);
		}

		//xp
		{
			constexpr auto* const key = "xp";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getPlayerStatistics()->setXp(value);
		}

		//totalLosses
		{
			constexpr auto* const key = "totalLosses";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint16_t value = (uint16_t)lua_tonumber(&io_luaState, -1);
			player->getPlayerStatistics()->setTotalLosses(value);
		}

		//totalWins
		{
			constexpr auto* const key = "totalWins";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint16_t value = (uint16_t)lua_tonumber(&io_luaState, -1);
			player->getPlayerStatistics()->setTotalWins(value);
		}

		//points
		{
			constexpr auto* const key = "points";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getPlayerStatistics()->setPoints(value);
		}
		return result;
	}

	//player characteristics

	eae6320::cResult LoadTableValues_physicalCharacteristics(lua_State& io_luaState, ProfileManagement::Player* player)
	{
		auto result = eae6320::Results::Success;

		constexpr auto* const key = "physicalCharacteristics";
		lua_pushstring(&io_luaState, key);
		lua_gettable(&io_luaState, -2);

		eae6320::cScopeGuard scopeGuard_popTextures([&io_luaState]
			{
				lua_pop(&io_luaState, 1);
			});

		if (lua_istable(&io_luaState, -1))
		{
			if (!(result = LoadTableValues_physicalCharacteristics_values(io_luaState, player)))
			{
				return result;
			}
		}
		else
		{
			result = eae6320::Results::InvalidFile;
			std::cerr << "The value at \"" << key << "\" must be a table "
				"(instead of a " << luaL_typename(&io_luaState, -1) << ")" << std::endl;
			return result;
		}

		return result;
	}

	eae6320::cResult LoadTableValues_physicalCharacteristics_values(lua_State& io_luaState, ProfileManagement::Player* player) {

		auto result = eae6320::Results::Success;

		//skin
		{
			constexpr auto* const key = "skin";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getPhysicalCharacteristics()->setSkin(value);
		}

		//hair
		{
			constexpr auto* const key = "hair";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getPhysicalCharacteristics()->setHair(value);
		}

		//shirt
		{
			constexpr auto* const key = "shirt";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getPhysicalCharacteristics()->setShirt(value);
		}

		//pants
		{
			constexpr auto* const key = "pants";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getPhysicalCharacteristics()->setPants(value);
		}

		//eyeColor
		{
			constexpr auto* const key = "eyeColor";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			if (lua_istable(&io_luaState, -1))
			{
				if (!(result = LoadTableValues_physicalCharacteristics_eyeColor_subvalues(io_luaState, player)))
				{
					return result;
				}
			}
			else
			{
				result = eae6320::Results::InvalidFile;
				std::cerr << "The value at  must be a table "
					"(instead of a " << luaL_typename(&io_luaState, -1) << ")" << std::endl;
				return result;
			}

		}

		//hairColor
		{
			constexpr auto* const key = "hairColor";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			if (lua_istable(&io_luaState, -1))
			{
				if (!(result = LoadTableValues_physicalCharacteristics_hairColor_subvalues(io_luaState, player)))
				{
					return result;
				}
			}
			else
			{
				result = eae6320::Results::InvalidFile;
				std::cerr << "The value at  must be a table "
					"(instead of a " << luaL_typename(&io_luaState, -1) << ")" << std::endl;
				return result;
			}

		}
		return result;
	}

	eae6320::cResult LoadTableValues_physicalCharacteristics_eyeColor_subvalues(lua_State& io_luaState, ProfileManagement::Player* player) {
		auto result = eae6320::Results::Success;
		int i = 0;
		std::cout << "Iterating through the indices:" << std::endl;
		lua_pushnil(&io_luaState);
		float val[3]{};
		while (lua_next(&io_luaState, -2) && i < 3)
		{
			val[i] = (float)lua_tonumber(&io_luaState, -1);
			i++;
			lua_pop(&io_luaState, 1);
		}
		player->getPhysicalCharacteristics()->setEyeColor(val[0], val[1], val[2]);

		return result;
	}

	eae6320::cResult LoadTableValues_physicalCharacteristics_hairColor_subvalues(lua_State& io_luaState, ProfileManagement::Player* player) {
		auto result = eae6320::Results::Success;
		int i = 0;
		std::cout << "Iterating through the indices:" << std::endl;
		lua_pushnil(&io_luaState);
		float val[3]{};
		while (lua_next(&io_luaState, -2) && i < 3)
		{
			val[i] = (float)lua_tonumber(&io_luaState, -1);
			i++;
			lua_pop(&io_luaState, 1);
		}
		player->getPhysicalCharacteristics()->setHairColor(val[0], val[1], val[2]);

		return result;
	}

	//player
	eae6320::cResult LoadTableValues_player(lua_State& io_luaState, ProfileManagement::Player* player)
	{
		auto result = eae6320::Results::Success;

		constexpr auto* const key = "player";
		lua_pushstring(&io_luaState, key);
		lua_gettable(&io_luaState, -2);

		eae6320::cScopeGuard scopeGuard_popTextures([&io_luaState]
			{
				lua_pop(&io_luaState, 1);
			});

		if (lua_istable(&io_luaState, -1))
		{
			if (!(result = LoadTableValues_player_values(io_luaState, player)))
			{
				return result;
			}
		}
		else
		{
			result = eae6320::Results::InvalidFile;
			std::cerr << "The value at \"" << key << "\" must be a table "
				"(instead of a " << luaL_typename(&io_luaState, -1) << ")" << std::endl;
			return result;
		}

		return result;
	}

	eae6320::cResult LoadTableValues_player_values(lua_State& io_luaState, ProfileManagement::Player* player) {

		auto result = eae6320::Results::Success;

		//userName
		{
			constexpr auto* const key = "userName";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			std::string value = lua_tostring(&io_luaState, -1);
			player->setUserName(value);
		}

		//group name
		{
			constexpr auto* const key = "groupName";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			std::string value = lua_tostring(&io_luaState, -1);
			player->setGroupName(value);
		}

		//player creation time
		{
			constexpr auto* const key = "playerCreationTime";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			std::string value = lua_tostring(&io_luaState, -1);
			player->setPlayerCreationTime(value);
		}

		//hours played
		{
			constexpr auto* const key = "hoursPlayed";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint16_t value = (uint16_t)lua_tonumber(&io_luaState, -1);
			player->setHoursPlayed(value);
		}

		//last updated time
		{
			constexpr auto* const key = "lastUpdatedTime";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			std::string value = lua_tostring(&io_luaState, -1);
			player->setLastUpdatedTime(value);
		}
		return result;
	}

	eae6320::cResult LoadAsset(const char* const i_path, ProfileManagement::Player* player)
	{
		auto result = eae6320::Results::Success;

		// Create a new Lua state
		lua_State* luaState = nullptr;
		eae6320::cScopeGuard scopeGuard_onExit([&luaState]
			{
				if (luaState)
				{
					// If I haven't made any mistakes
					// there shouldn't be anything on the stack
					// regardless of any errors
					EAE6320_ASSERT(lua_gettop(luaState) == 0);

					lua_close(luaState);
					luaState = nullptr;
				}
			});
		{
			luaState = luaL_newstate();
			if (!luaState)
			{
				result = eae6320::Results::OutOfMemory;
				std::cerr << "Failed to create a new Lua state" << std::endl;
				return result;
			}
		}

		// Load the asset file as a "chunk",
		// meaning there will be a callable function at the top of the stack
		const auto stackTopBeforeLoad = lua_gettop(luaState);
		{
			const auto luaResult = luaL_loadfile(luaState, i_path);
			if (luaResult != LUA_OK)
			{
				result = eae6320::Results::Failure;
				std::cerr << lua_tostring(luaState, -1) << std::endl;
				// Pop the error message
				lua_pop(luaState, 1);
				return result;
			}
		}
		// Execute the "chunk", which should load the asset
		// into a table at the top of the stack
		{
			constexpr int argumentCount = 0;
			constexpr int returnValueCount = LUA_MULTRET;	// Return _everything_ that the file returns
			constexpr int noMessageHandler = 0;
			const auto luaResult = lua_pcall(luaState, argumentCount, returnValueCount, noMessageHandler);
			if (luaResult == LUA_OK)
			{
				// A well-behaved asset file will only return a single value
				const auto returnedValueCount = lua_gettop(luaState) - stackTopBeforeLoad;
				if (returnedValueCount == 1)
				{
					// A correct asset file _must_ return a table
					if (!lua_istable(luaState, -1))
					{
						result = eae6320::Results::InvalidFile;
						std::cerr << "Asset files must return a table (instead of a " <<
							luaL_typename(luaState, -1) << ")" << std::endl;
						// Pop the returned non-table value
						lua_pop(luaState, 1);
						return result;
					}
				}
				else
				{
					result = eae6320::Results::InvalidFile;
					std::cerr << "Asset files must return a single table (instead of " <<
						returnedValueCount << " values)" << std::endl;
					// Pop every value that was returned
					lua_pop(luaState, returnedValueCount);
					return result;
				}
			}
			else
			{
				result = eae6320::Results::InvalidFile;
				std::cerr << lua_tostring(luaState, -1) << std::endl;
				// Pop the error message
				lua_pop(luaState, 1);
				return result;
			}
		}

		// If this code is reached the asset file was loaded successfully,
		// and its table is now at index -1
		eae6320::cScopeGuard scopeGuard_popAssetTable([luaState]
			{
				lua_pop(luaState, 1);
			});
		result = LoadTableValues(*luaState, player);

		return result;
	}

	// input control

	eae6320::cResult LoadTableValues_inputControls(lua_State& io_luaState, ProfileManagement::Player* player)
	{
		auto result = eae6320::Results::Success;

		constexpr auto* const key = "inputControls";
		lua_pushstring(&io_luaState, key);
		lua_gettable(&io_luaState, -2);

		eae6320::cScopeGuard scopeGuard_popTextures([&io_luaState]
			{
				lua_pop(&io_luaState, 1);
			});

		if (lua_istable(&io_luaState, -1))
		{
			if (!(result = LoadTableValues_inputControls_values(io_luaState, player)))
			{
				return result;
			}
		}
		else
		{
			result = eae6320::Results::InvalidFile;
			std::cerr << "The value at \"" << key << "\" must be a table "
				"(instead of a " << luaL_typename(&io_luaState, -1) << ")" << std::endl;
			return result;
		}

		return result;
	}

	eae6320::cResult LoadTableValues_inputControls_values(lua_State& io_luaState, ProfileManagement::Player* player) {

		auto result = eae6320::Results::Success;

		//inputType
		{
			constexpr auto* const key = "inputType";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getInputControls()->setInputType(value);
		}

		//up
		{
			constexpr auto* const key = "up";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getInputControls()->setUp(value);
		}

		//down
		{
			constexpr auto* const key = "down";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getInputControls()->setDown(value);
		}

		//left
		{
			constexpr auto* const key = "left";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getInputControls()->setLeft(value);
		}

		//right
		{
			constexpr auto* const key = "right";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getInputControls()->setRight(value);
		}

		//primaryAttack
		{
			constexpr auto* const key = "primaryAttack";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getInputControls()->setPrimaryAttack(value);
		}

		//secondaryAttack
		{
			constexpr auto* const key = "secondaryAttack";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getInputControls()->setSecondaryAttack(value);
		}

		//parry
		{
			constexpr auto* const key = "parry";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getInputControls()->setParry(value);
		}

		//duck
		{
			constexpr auto* const key = "duck";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getInputControls()->setDuck(value);
		}

		//jump
		{
			constexpr auto* const key = "jump";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getInputControls()->setJump(value);
		}

		//action
		{
			constexpr auto* const key = "action";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getInputControls()->setAction(value);
		}
		return result;
	}

	// audio settings

	eae6320::cResult LoadTableValues_audioSettings(lua_State& io_luaState, ProfileManagement::Player* player)
	{
		auto result = eae6320::Results::Success;

		constexpr auto* const key = "audioSettings";
		lua_pushstring(&io_luaState, key);
		lua_gettable(&io_luaState, -2);

		eae6320::cScopeGuard scopeGuard_popTextures([&io_luaState]
			{
				lua_pop(&io_luaState, 1);
			});

		if (lua_istable(&io_luaState, -1))
		{
			if (!(result = LoadTableValues_audioSettings_values(io_luaState, player)))
			{
				return result;
			}
		}
		else
		{
			result = eae6320::Results::InvalidFile;
			std::cerr << "The value at \"" << key << "\" must be a table "
				"(instead of a " << luaL_typename(&io_luaState, -1) << ")" << std::endl;
			return result;
		}

		return result;
	}

	eae6320::cResult LoadTableValues_audioSettings_values(lua_State& io_luaState, ProfileManagement::Player* player) {

		auto result = eae6320::Results::Success;


		//masterVolume
		{
			constexpr auto* const key = "masterVolume";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getAudioSettings()->setMasterVolume(value);
		}

		//musicVolume
		{
			constexpr auto* const key = "musicVolume";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getAudioSettings()->setMusicVolume(value);
		}

		//dialogueVolume
		{
			constexpr auto* const key = "dialogueVolume";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getAudioSettings()->setDialogueVolume(value);
		}

		//soundEffectsVolume
		{
			constexpr auto* const key = "soundEffectsVolume";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getAudioSettings()->setSoundEffectsVolume(value);
		}

		//killStreakMusic
		{
			constexpr auto* const key = "killStreakMusic";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			bool value = lua_toboolean(&io_luaState, -1);
			player->getGameSetting()->getAudioSettings()->setIsKillStreakMusic(value);
		}

		//gameSoundDevice
		{
			constexpr auto* const key = "gameSoundDevice";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getAudioSettings()->setGameSoundDevice(value);
		}

		//mainMusicVolume
		{
			constexpr auto* const key = "mainMusicVolume";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getAudioSettings()->setMainMusicVolume(value);
		}

		//mainMenuVolume
		{
			constexpr auto* const key = "mainMenuVolume";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getAudioSettings()->setMainMenuVolume(value);
		}

		//roundStartVolume
		{
			constexpr auto* const key = "roundStartVolume";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getAudioSettings()->setRoundStartVolume(value);
		}

		//roundEndVolume
		{
			constexpr auto* const key = "roundEndVolume";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getAudioSettings()->setRoundEndVolume(value);
		}


		return result;
	}

	//voice setting

	eae6320::cResult LoadTableValues_voiceChatSettings(lua_State& io_luaState, ProfileManagement::Player* player)
	{
		auto result = eae6320::Results::Success;

		constexpr auto* const key = "voiceChatSettings";
		lua_pushstring(&io_luaState, key);
		lua_gettable(&io_luaState, -2);

		eae6320::cScopeGuard scopeGuard_popTextures([&io_luaState]
			{
				lua_pop(&io_luaState, 1);
			});

		if (lua_istable(&io_luaState, -1))
		{
			if (!(result = LoadTableValues_voiceChatSettings_values(io_luaState, player)))
			{
				return result;
			}
		}
		else
		{
			result = eae6320::Results::InvalidFile;
			std::cerr << "The value at \"" << key << "\" must be a table "
				"(instead of a " << luaL_typename(&io_luaState, -1) << ")" << std::endl;
			return result;
		}

		return result;
	}

	eae6320::cResult LoadTableValues_voiceChatSettings_values(lua_State& io_luaState, ProfileManagement::Player* player) {

		auto result = eae6320::Results::Success;

		//isVoiceChatOn
		{
			constexpr auto* const key = "isVoiceChatOn";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			bool value = lua_toboolean(&io_luaState, -1);
			player->getGameSetting()->getVoiceChatSettings()->setIsVoiceChatOn(value);
		}

		//voiceChatDevice
		{
			constexpr auto* const key = "voiceChatDevice";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getVoiceChatSettings()->setVoiceChatDevice(value);
		}

		//microphoneDevice
		{
			constexpr auto* const key = "microphoneDevice";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getVoiceChatSettings()->setMicrophoneDevice(value);
		}

		//voiceChatVolume
		{
			constexpr auto* const key = "voiceChatVolume";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getVoiceChatSettings()->setVoiceChatVolume(value);
		}

		//microphoneVolume
		{
			constexpr auto* const key = "microphoneVolume";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getVoiceChatSettings()->setMicrophoneVolume(value);
		}

		//killStreakMusic
		{
			constexpr auto* const key = "killStreakMusic";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			bool value = lua_toboolean(&io_luaState, -1);
			player->getGameSetting()->getVoiceChatSettings()->setIsPlayAudioWhenGameInBackground(value);
		}


		return result;
	}


	//video setting

	eae6320::cResult LoadTableValues_videoSettings(lua_State& io_luaState, ProfileManagement::Player* player)
	{
		auto result = eae6320::Results::Success;

		constexpr auto* const key = "videoSettings";
		lua_pushstring(&io_luaState, key);
		lua_gettable(&io_luaState, -2);

		eae6320::cScopeGuard scopeGuard_popTextures([&io_luaState]
			{
				lua_pop(&io_luaState, 1);
			});

		if (lua_istable(&io_luaState, -1))
		{
			if (!(result = LoadTableValues_videoSettings_values(io_luaState, player)))
			{
				return result;
			}
		}
		else
		{
			result = eae6320::Results::InvalidFile;
			std::cerr << "The value at \"" << key << "\" must be a table "
				"(instead of a " << luaL_typename(&io_luaState, -1) << ")" << std::endl;
			return result;
		}

		return result;
	}

	eae6320::cResult LoadTableValues_videoSettings_values(lua_State& io_luaState, ProfileManagement::Player* player) {

		auto result = eae6320::Results::Success;
		//resolution
		{
			constexpr auto* const key = "resolution";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			float value = (float)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getVideoSettings()->setResolution(value);
		}
		//textureQuality
		{
			constexpr auto* const key = "textureQuality";
			lua_pushstring(&io_luaState, key);
			lua_gettable(&io_luaState, -2);
			eae6320::cScopeGuard scopeGuard_popAge([&io_luaState] { lua_pop(&io_luaState, 1); });
			uint8_t value = (uint8_t)lua_tonumber(&io_luaState, -1);
			player->getGameSetting()->getVideoSettings()->setTextureQuality(value);
		}


		return result;
	}
}