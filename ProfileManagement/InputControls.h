#pragma once
#include <cstdint>


namespace ProfileManagement {
	class InputControls {
		private:
			uint8_t inputType = 0; //whether keyboard (0) or controller (1)
			uint8_t up;
			uint8_t down;
			uint8_t left;
			uint8_t right;
			uint8_t primaryAttack;
			uint8_t secondaryAttack;
			uint8_t parry;
			uint8_t duck;
			uint8_t jump;
			uint8_t action;

		public:

			void setInputType(uint8_t i_inputType) {
				inputType = i_inputType;
			}

			void setUp(uint8_t i_up) {
				up = i_up;
			}

			void setDown(uint8_t i_down) {
				down = i_down;
			}

			void setLeft(uint8_t i_left) {
				left = i_left;
			}

			void setRight(uint8_t i_right) {
				right = i_right;
			}

			void setPrimaryAttack(uint8_t i_primaryAttack) {
				primaryAttack = i_primaryAttack;
			}

			void setSecondaryAttack(uint8_t i_secondaryAttack) {
				secondaryAttack = i_secondaryAttack;
			}

			void setParry(uint8_t i_parry) {
				parry = i_parry;
			}

			void setDuck(uint8_t i_duck) {
				duck = i_duck;
			}

			void setJump(uint8_t i_jump) {
				jump = i_jump;
			}

			void setAction(uint8_t i_action) {
				action = i_action;
			}
	

			uint8_t getInputType() const { return inputType; }

			uint8_t getUp() const { return up; }

			uint8_t getDown() const { return down; }

			uint8_t getLeft() const { return left; }

			uint8_t getRight() const { return right; }

			uint8_t getPrimaryAttack() const { return primaryAttack; }

			uint8_t getSecondaryAttack() const { return secondaryAttack; }

			uint8_t getParry() const { return parry; }

			uint8_t getDuck() const { return duck; }

			uint8_t getJump() const { return jump; }

			uint8_t getAction() const { return action; }

};
}