#pragma once
#include <Engine/ProfileManagement/Player.h>
#include <Engine/ProfileManagement/PhysicalCharacteristics.h>
#include <Engine/ProfileManagement/PlayerStatistics.h>
#include <Engine/ProfileManagement/Skills.h>
#include <Engine/ProfileManagement/Achievements.h>

namespace ProfileManagement {
	class GameObject {
	public:
		Player* player;
		PhysicalCharacteristics* physicalCharacteristics;
		PlayerStatistics* playerStatistics;
		Skills* skills;
		Achievements* achievements;
	};
}

