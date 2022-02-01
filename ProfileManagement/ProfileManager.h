#pragma once
#include <Engine/Results/cResult.h>
#include <string>
#include <Engine/ProfileManagement/Player.h>
#include <Engine/ProfileManagement/CustomDetails.h>

#ifndef EAE6320_PROFILEMANAGER_H
#define EAE6320_PROFILEMANAGER_H


namespace ProfileManagement
{
	class ProfileManager
	{
		public:
			static eae6320::cResult LoadPlayerDetails(std::string playerDetails, ProfileManagement::Player* player);
			static eae6320::cResult WritePlayerDetails(std::string playerDetails, ProfileManagement::Player* player);
			static eae6320::cResult LoadCustomDetails(std::string customDetailsFile, ProfileManagement::CustomDetails* customDetails);
	};
}

#endif	// EAE6320_PROFILEMANAGER_H