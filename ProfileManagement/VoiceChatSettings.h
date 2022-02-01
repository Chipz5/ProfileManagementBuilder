#pragma once
#include <cstdint>

namespace ProfileManagement {
	class VoiceChatSettings {
		private:
			bool isVoiceChatOn;
			uint8_t voiceChatDevice; // whether audio is to be sent to speakers or headphones
			uint8_t microphoneDevice; // the microphone of your choice
			uint8_t voiceChatVolume; 
			uint8_t microphoneVolume;
			bool playAudioWhenGameInBackground; //yes or no

		public:
			void setIsVoiceChatOn(bool i_isVoiceChatOn) {
				isVoiceChatOn = i_isVoiceChatOn;
			}

			void setVoiceChatDevice(uint8_t i_voiceChatDevice) {
				voiceChatDevice = i_voiceChatDevice;
			}

			void setMicrophoneDevice(uint8_t i_microphoneDevice) {
				microphoneDevice = i_microphoneDevice;
			}

			void setVoiceChatVolume(uint8_t i_voiceChatVolume) {
				voiceChatVolume = i_voiceChatVolume;
			}

			void setMicrophoneVolume(uint8_t i_microphoneVolume) {
				microphoneVolume = i_microphoneVolume;
			}

			void setIsPlayAudioWhenGameInBackground(bool i_playAudioWhenGameInBackground) {
				playAudioWhenGameInBackground = i_playAudioWhenGameInBackground;
			}

			bool getIsVoiceChatOn() const { return isVoiceChatOn; }

			uint8_t getVoiceChatDevice() const { return voiceChatDevice; }

			uint8_t getMicrophoneDevice() const { return microphoneDevice; }

			uint8_t getVoiceChatVolume() const { return voiceChatVolume; }

			uint8_t getMicrophoneVolume() const { return microphoneVolume; }

			bool getPlayAudioWhenGameInBackground() const { return playAudioWhenGameInBackground; }

};
}

