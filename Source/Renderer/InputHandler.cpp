#include "InputHandler.h"

bool Niko::InputHandler::IsKeyPressed(uint16_t glfwKey) {
  return mKey_states[glfwKey] == KeyState::PRESS;
}

bool Niko::InputHandler::IsKeyHeld(uint16_t glfwKey) {
  int keyState = mKey_states[glfwKey];
  return (keyState == KeyState::HOLD) || (keyState == KeyState::PRESS);
}

bool Niko::InputHandler::IsKeyReleased(uint16_t glfwKey) {
  return mKey_states[glfwKey] == KeyState::JUSTRELEASED;
}

void Niko::InputHandler::key_callback(GLFWwindow *window, int key, int scancode,
                                      int action, int mods) {
  if (action == GLFW_PRESS) {
    this->mKey_states[key] = KeyState::PRESS;
    keyStateUpdateQueue.push(key);
  } else if (action == GLFW_RELEASE) {
    this->mKey_states[key] = KeyState::JUSTRELEASED;

    keyStateUpdateQueue.push(key);
  }
}

bool Niko::InputHandler::IsMousePressed(uint16_t glfwKey) {
  return mMouse_states[glfwKey] == KeyState::PRESS;
}

bool Niko::InputHandler::IsMouseHeld(uint16_t glfwKey) {
  int keyState = mMouse_states[glfwKey];
  return (keyState == KeyState::HOLD) || (keyState == KeyState::PRESS);
}

bool Niko::InputHandler::IsMouseReleased(uint16_t glfwKey) {
  return mMouse_states[glfwKey] == KeyState::JUSTRELEASED;
}

void Niko::InputHandler::mouse_callback(GLFWwindow *window, int button,
                                        int action, int mods) {
  if (action == GLFW_PRESS) {
    this->mMouse_states[button] = KeyState::PRESS;
    mouseStateUpdateQueue.push(button);
  } else if (action == GLFW_RELEASE) {
    this->mMouse_states[button] = KeyState::JUSTRELEASED;

    mouseStateUpdateQueue.push(button);
  }
}

void Niko::InputHandler::cursor_position_callback(GLFWwindow *window,
                                                  double xpos, double ypos) {
  cursorPos = {xpos, ypos};
}

glm::dvec2 Niko::InputHandler::cursorDeltaDistance() {
  // Issue with the Delta distance, where seemingly when switching input
  // modes, the distance is much greater than it should be
  return oldCursorPos - cursorPos;
}

void Niko::InputHandler::changeCursorInputMode(GLFWwindow *window,
                                               CursorMode mode) {
  switch (mode) {
  case Niko::NORMAL:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    if (glfwRawMouseMotionSupported()) {
      glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
    }
    break;
  case Niko::HIDDEN:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    break;
  case Niko::CAPTURED:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
    break;
  case Niko::DISABLED:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (glfwRawMouseMotionSupported()) {
      glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    break;
  default:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    break;
  }
}

void Niko::InputHandler::update_states() {
  for (int i = 0; i < mouseStateUpdateQueue.size(); i++) {
    int mouseBut = mouseStateUpdateQueue.front();
    KeyState s = mMouse_states[mouseBut];

    if (s == KeyState::PRESS) {
      mMouse_states[mouseBut] = KeyState::HOLD;
    } else if (s == KeyState::JUSTRELEASED) {
      mMouse_states[mouseBut] = KeyState::RELEASED;
    }

    mouseStateUpdateQueue.pop();
  }

  for (int i = 0; i < keyStateUpdateQueue.size(); i++) {
    int mouseBut = keyStateUpdateQueue.front();
    KeyState s = mKey_states[mouseBut];

    if (s == KeyState::PRESS) {
      mKey_states[mouseBut] = KeyState::HOLD;
    } else if (s == KeyState::JUSTRELEASED) {
      mKey_states[mouseBut] = KeyState::RELEASED;
    }

    keyStateUpdateQueue.pop();
  }

  oldCursorPos = cursorPos;
}
