#pragma once
#include <cstdint>

namespace ProfileManagement {
	class PlayerStatistics {
		private:
			
			uint64_t health;
			uint64_t energy;
			uint64_t damage;
			uint8_t xp;
			uint16_t totalLosses;
			uint16_t totalWins;
			uint8_t points;

		public:
		
			void setHealth(uint64_t i_health) {
				health = i_health;
			}

			void setEnergy(uint64_t i_energy) {
				energy = i_energy;
			}

			void setDamage(uint64_t i_damage) {
				damage = i_damage;
			}

			void setXp(uint8_t i_xp) {
				xp = i_xp;
			}

			void setTotalLosses(uint16_t i_totalLosses) {
				totalLosses = i_totalLosses;
			}

			void setTotalWins(uint16_t i_totalWins) {
				totalWins = i_totalWins;
			}

			void setPoints(uint8_t i_points) {
				points = i_points;
			}


			uint64_t getHealth() const { return health; }

			uint64_t getEnergy() const { return energy; }

			uint64_t getDamage() const { return damage; }

			uint8_t getXp() const { return xp; }

			uint16_t getTotalLosses() const { return totalLosses; }

			uint16_t getTotalWins() const { return totalWins; }

			uint8_t getPoints() const { return points; }

};
}
 