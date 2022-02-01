#pragma once
#include <cstdint>
#include <Engine/ProfileManagement/InputControls.h>
#include <Engine/ProfileManagement/AudioSettings.h>
#include <Engine/ProfileManagement/VoiceChatSettings.h>
#include <Engine/ProfileManagement/VideoSettings.h>

namespace ProfileManagement {
	class GameSettings {
		private:
			InputControls* inputControls;
			AudioSettings* audioSettings;
			VoiceChatSettings* voiceChatSettings;
			VideoSettings* videoSettings;

		public:
			GameSettings() {
				inputControls = new InputControls();
				audioSettings = new AudioSettings();
				voiceChatSettings = new VoiceChatSettings();
				videoSettings = new VideoSettings();
			}

			InputControls* getInputControls() {
				return inputControls;
			}

			AudioSettings* getAudioSettings() {
				return audioSettings;
			}

			VoiceChatSettings* getVoiceChatSettings() {
				return voiceChatSettings;
			}

			VideoSettings* getVideoSettings() {
				return videoSettings;
			}
	};
}