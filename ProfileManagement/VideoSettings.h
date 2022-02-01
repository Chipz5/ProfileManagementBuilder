#pragma once
#include <cstdint>
#include <string>

namespace ProfileManagement {
	class VideoSettings {
		private:
			float resolution; // 0 - 1
			uint8_t textureQuality; //0 - low, 1- medium, 2 - high

		public:
			void setResolution(float i_resolution) {
				resolution = i_resolution;
			}

			void setTextureQuality(uint8_t i_textureQuality) {
				textureQuality = i_textureQuality;
			}


			float getResolution() const { return resolution; }

			uint8_t getTextureQuality() const { return textureQuality; }

};
}
