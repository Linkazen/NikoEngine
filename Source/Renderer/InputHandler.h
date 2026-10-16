#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <map>
#include <queue>

namespace Niko {
enum KeyState { RELEASED, PRESS, HOLD, JUSTRELEASED };

enum CursorMode { NORMAL, HIDDEN, CAPTURED, DISABLED };

class InputHandler {
public:
  // KEY INPUT
  bool IsKeyPressed(uint16_t glfwKey);

  bool IsKeyHeld(uint16_t glfwKey);

  bool IsKeyReleased(uint16_t glfwKey);

  void key_callback(GLFWwindow *window, int key, int scancode, int action,
                    int mods);

  // MOUSE INPUT
  bool IsMousePressed(uint16_t glfwKey);

  bool IsMouseHeld(uint16_t glfwKey);

  bool IsMouseReleased(uint16_t glfwKey);

  void mouse_callback(GLFWwindow *window, int button, int action, int mods);

  void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

  glm::dvec2 cursorDeltaDistance();

  void changeCursorInputMode(GLFWwindow *window, CursorMode mode);

  // Whatever is in the queues below is ran, this means that updates
  // to the key states can be done for each frame, JUSTRELEASED state
  // and PRESS state especially as these only happen for one frame. And these
  // states can now be polled.
  void update_states();

private:
  // Map for the state of keys
  std::map<uint16_t, KeyState> mKey_states;
  std::map<uint16_t, KeyState> mMouse_states;
  std::queue<uint16_t> keyStateUpdateQueue;
  std::queue<uint16_t> mouseStateUpdateQueue;

  glm::dvec2 oldCursorPos = {0, 0};
  glm::dvec2 cursorPos = {0, 0};
};
} // namespace Niko
