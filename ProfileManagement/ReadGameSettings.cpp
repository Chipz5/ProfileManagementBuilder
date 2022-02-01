#include "ReadGameSettings.h"



namespace {
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