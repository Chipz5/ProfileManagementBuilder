#pragma once
#include <Engine/Results/Results.h>
#include <string>
#include <Engine/ProfileManagement/Player.h>

#include <External/Lua/Includes.h>
#include <Engine/ScopeGuard/cScopeGuard.h>
#include <Engine/Asserts/Asserts.h>
#include <iostream>
#include <Engine/ProfileManagement/Skills.h>
namespace {
	eae6320::cResult LoadTableValues_inputControls(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_inputControls_values(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_audioSettings(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_audioSettings_values(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_voiceChatSettings(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_voiceChatSettings_values(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_videoSettings(lua_State& io_luaState, ProfileManagement::Player* player);
	eae6320::cResult LoadTableValues_videoSettings_values(lua_State& io_luaState, ProfileManagement::Player* player);
}