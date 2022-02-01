#include "ReadCustomDetails.h"
#include <External/Lua/Includes.h>
#include <Engine/ScopeGuard/cScopeGuard.h>
#include <Engine/Asserts/Asserts.h>
#include <iostream>

namespace {
	eae6320::cResult LoadAsset(const char* const i_path, ProfileManagement::CustomDetails* customDetails);
	eae6320::cResult LoadTableValues(lua_State& io_luaState, ProfileManagement::CustomDetails* customDetails);
	eae6320::cResult LoadTableValues_custom(lua_State& io_luaState, ProfileManagement::CustomDetails* customDetails);
}

eae6320::cResult ReadCustomDetails(std::string playerFile, ProfileManagement::CustomDetails* customDetails)
{
	auto result = eae6320::Results::Success;

	const char* const path = playerFile.c_str();
	if (!(result = LoadAsset(path, customDetails)))
	{
		return result;
	}

	return result;
}


namespace {

	eae6320::cResult LoadTableValues(lua_State& io_luaState, ProfileManagement::CustomDetails* customDetails)
	{
		auto result = eae6320::Results::Success;

		if (!(result = LoadTableValues_custom(io_luaState, customDetails)))
		{
			return result;
		}

		return result;
	}

	eae6320::cResult LoadTableValues_custom(lua_State& io_luaState, ProfileManagement::CustomDetails* customDetails)
	{
		auto result = eae6320::Results::Success;
		std::map<std::string, std::string> stringElements;
		std::map<std::string, uint16_t> numbers;
		lua_pushnil(&io_luaState);
		while (lua_next(&io_luaState, -2) != 0)
		{
			std::map<std::string, std::string> numberElements;
			std::string type = luaL_typename(&io_luaState, -1);
			numberElements.insert(std::pair<std::string, std::string>(lua_tostring(&io_luaState, -2), lua_tostring(&io_luaState, -1)));
			if (type == "string") {
				stringElements.insert(std::pair<std::string, std::string>(lua_tostring(&io_luaState, -2), lua_tostring(&io_luaState, -1)));
			}
			else if (type == "number") {
				numbers.insert(std::pair<std::string, uint16_t>(lua_tostring(&io_luaState, -2), (uint16_t)lua_tonumber(&io_luaState, -1)));
			}

			lua_pop(&io_luaState, 1);
		}
		
		customDetails->setStringElements(stringElements);
		customDetails->setNumberElements(numbers);

		return result;
	}

	eae6320::cResult LoadAsset(const char* const i_path, ProfileManagement::CustomDetails* customDetails)
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
		result = LoadTableValues(*luaState, customDetails);

		return result;
	}
}