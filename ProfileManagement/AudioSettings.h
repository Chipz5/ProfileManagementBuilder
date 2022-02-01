#pragma once
#include <cstdint>

namespace ProfileManagement {
	class AudioSettings {
		private:
			uint8_t masterVolume;
			uint8_t musicVolume;
			uint8_t dialogueVolume;
			uint8_t soundEffectsVolume;
			bool killStreakMusic; //either on or off
			uint8_t gameSoundDevice; //whether sound o/p should be sent to speakers or headphones

			//music options

			uint8_t mainMusicVolume;
			uint8_t mainMenuVolume;
			uint8_t roundStartVolume;
			uint8_t roundEndVolume;

		public:

			void setMasterVolume(uint8_t i_masterVolume) {
				masterVolume = i_masterVolume;
			}

			void setMusicVolume(uint8_t i_musicVolume) {
				musicVolume = i_musicVolume;
			}

			void setDialogueVolume(uint8_t i_dialogueVolume) {
				dialogueVolume = i_dialogueVolume;
			}

			void setIsKillStreakMusic(bool i_killStreakMusic) {
				killStreakMusic = i_killStreakMusic;
			}
			void setGameSoundDevice(bool i_gameSoundDevice) {
				gameSoundDevice = i_gameSoundDevice;
			}

			void setSoundEffectsVolume(uint8_t i_soundEffectsVolume) {
				soundEffectsVolume = i_soundEffectsVolume;
			}

			void setMainMusicVolume(uint8_t i_mainMusicVolume) {
				mainMusicVolume = i_mainMusicVolume;
			}

			void setMainMenuVolume(uint8_t i_mainMenuVolume) {
				mainMenuVolume = i_mainMenuVolume;
			}

			void setRoundStartVolume(uint8_t i_roundStartVolume) {
				roundStartVolume = i_roundStartVolume;
			}

			void setRoundEndVolume(uint8_t i_roundEndVolume) {
				roundEndVolume = i_roundEndVolume;
			}


			uint8_t getMasterVolume() const { return masterVolume; }

			uint8_t getMusicVolume() const { return musicVolume; }

			uint8_t getDialogueVolume() const { return dialogueVolume; }

			uint8_t getSoundEffectsVolume() const { return soundEffectsVolume; }

			bool getKillStreakMusic() const { return killStreakMusic; }

			uint8_t getGameSoundDevice() const { return gameSoundDevice; }

			uint8_t getMainMusicVolume() const { return mainMusicVolume; }

			uint8_t getMainMenuVolume() const { return mainMenuVolume; }

			uint8_t getRoundStartVolume() const { return roundStartVolume; }

			uint8_t getRoundEndVolume() const { return roundEndVolume; }

};
}

