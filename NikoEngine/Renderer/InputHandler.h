#pragma once
#include "GLFW/glfw3.h"
#include <map>
#include <iostream>
#include <queue>
#include <functional>

namespace Niko {
	enum KeyState {
		RELEASED,
		PRESS,
		HOLD,
		JUSTRELEASED
	};

	class InputHandler {
	public:
		// KEY INPUT
		bool IsKeyPressed(uint16_t glfwKey) {
			return mKey_states[glfwKey] == KeyState::PRESS;
		}

		bool IsKeyHeld(uint16_t glfwKey) {
			int keyState = mKey_states[glfwKey];
			return (keyState == KeyState::HOLD) || (keyState == KeyState::PRESS);
		}

		bool IsKeyReleased(uint16_t glfwKey) {
			return mKey_states[glfwKey] == KeyState::JUSTRELEASED;
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			if (action == GLFW_PRESS) {
				this->mKey_states[key] = KeyState::PRESS;
				keyStateUpdateQueue.push(key);
			}
			else if (action == GLFW_RELEASE) {
				this->mKey_states[key] = KeyState::JUSTRELEASED;

				keyStateUpdateQueue.push(key);
			}
		}

		// MOUSE INPUT
		bool IsMousePressed(uint16_t glfwKey) {
			return mMouse_states[glfwKey] == KeyState::PRESS;
		}

		bool IsMouseHeld(uint16_t glfwKey) {
			int keyState = mMouse_states[glfwKey];
			return (keyState == KeyState::HOLD) || (keyState == KeyState::PRESS);
		}

		bool IsMouseReleased(uint16_t glfwKey) {
			return mMouse_states[glfwKey] == KeyState::JUSTRELEASED;
		}

		void mouse_callback(GLFWwindow* window, int button, int action, int mods) {
			if (action == GLFW_PRESS) {
				this->mMouse_states[button] = KeyState::PRESS;
				mouseStateUpdateQueue.push(button);
			}
			else if (action == GLFW_RELEASE) {
				this->mMouse_states[button] = KeyState::JUSTRELEASED;

				mouseStateUpdateQueue.push(button);
			}
		}

		void update_states() {
			for (int i = 0; i < mouseStateUpdateQueue.size(); i++) {
				int mouseBut = mouseStateUpdateQueue.front();
				KeyState s = mMouse_states[mouseBut];

				if (s == KeyState::PRESS) {
					mMouse_states[mouseBut] = KeyState::HOLD;
				}
				else if (s == KeyState::JUSTRELEASED) {
					mMouse_states[mouseBut] = KeyState::RELEASED;
				}

				mouseStateUpdateQueue.pop();
			}

			for (int i = 0; i < keyStateUpdateQueue.size(); i++) {
				int mouseBut = keyStateUpdateQueue.front();
				KeyState s = mKey_states[mouseBut];

				if (s == KeyState::PRESS) {
					mKey_states[mouseBut] = KeyState::HOLD;
				}
				else if (s == KeyState::JUSTRELEASED) {
					mKey_states[mouseBut] = KeyState::RELEASED;
				}

				keyStateUpdateQueue.pop();
			}
		}

	private:
		// Map for the state of keys
		std::map<uint16_t, KeyState> mKey_states;
		std::map<uint16_t, KeyState> mMouse_states;
		std::queue<uint16_t> keyStateUpdateQueue;
		std::queue<uint16_t> mouseStateUpdateQueue;
	};
}

