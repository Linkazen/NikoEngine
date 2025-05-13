#pragma once
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include <map>
#include <iostream>
#include <queue>
#include <functional>
#include <imgui.h>

namespace Niko {
	enum KeyState {
		RELEASED,
		PRESS,
		HOLD,
		JUSTRELEASED
	};

	enum CursorMode {
		NORMAL,
		HIDDEN,
		CAPTURED,
		DISABLED
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

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			cursorPos = { xpos, ypos };
		}

		glm::dvec2 cursorDeltaDistance() {
			return oldCursorPos - cursorPos;
		}

		void changeCursorInputMode(GLFWwindow* window, CursorMode mode) {
			switch (mode)
			{
			case Niko::NORMAL:
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				oldCursorPos = { 0,0 };
				cursorPos = { 0,0 };
				if (glfwRawMouseMotionSupported()) {
					glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
				}
				break;
			case Niko::HIDDEN:
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				oldCursorPos = { 0,0 };
				cursorPos = { 0,0 };
				break;
			case Niko::CAPTURED:
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
				oldCursorPos = { 0,0 };
				cursorPos = { 0,0 };
				break;
			case Niko::DISABLED:
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				oldCursorPos = { 0,0 };
				cursorPos = { 0,0 };
				if (glfwRawMouseMotionSupported()) {
					glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
				}
				break;
			default:
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				oldCursorPos = { 0,0 };
				cursorPos = { 0,0 };
				break;
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

			oldCursorPos = cursorPos;
		}

	private:
		// Map for the state of keys
		std::map<uint16_t, KeyState> mKey_states;
		std::map<uint16_t, KeyState> mMouse_states;
		std::queue<uint16_t> keyStateUpdateQueue;
		std::queue<uint16_t> mouseStateUpdateQueue;

		glm::dvec2 oldCursorPos = { 0,0 };
		glm::dvec2 cursorPos = { 0,0 };
	};
}

