#pragma once
#include <cstdint>

namespace ProfileManagement {

	struct rbgValues
	{
		float red;
		float blue;
		float green;
	};

	class PhysicalCharacteristics {
		private:
			uint8_t skin;
			uint8_t hair;
			uint8_t shirt;
			uint8_t pants;
			rbgValues eyeColor;
			rbgValues hairColor;

		public:

			void setSkin(uint8_t i_skin) {
				skin = i_skin;
			}

			void setHair(uint8_t i_hair) {
				hair = i_hair;
			}

			void setShirt(uint8_t i_shirt) {
				shirt = i_shirt;
			}

			void setPants(uint8_t i_pants) {
				pants = i_pants;
			}

			void setEyeColor(float red, float blue, float green) {
				eyeColor.red = red;
				eyeColor.blue = blue;
				eyeColor.green = green;
			}

			void setHairColor(float red, float blue, float green) {
				hairColor.red = red;
				hairColor.blue = blue;
				hairColor.green = green;
			}

			uint8_t getSkin() const { return skin; }

			uint8_t getHair() const { return hair; }

			uint8_t getShirt() const { return shirt; }

			uint8_t getPants() const { return pants; }

			rbgValues getEyeColor() const { return eyeColor; }

			rbgValues getHairColor() const { return hairColor; }

};
}
