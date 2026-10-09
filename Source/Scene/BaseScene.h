#pragma once
#include "../Renderer/TimeKeeper.h"
#include "../Renderer/VulkanRenderer.h"

class BaseScene {
public:
  BaseScene(VulkanRenderer *renderer);

  virtual void Update();
  virtual void ImGuiRender();
  virtual void Render();

  std::vector<Niko::Object> &getObjects();

  void setTimeKeeper(TimeKeeper *tk);
  void setInputHandler(Niko::InputHandler *ih);

private:
  std::vector<Niko::Object> objects = {};
  VulkanRenderer *mRenderer = nullptr;

  TimeKeeper *time = nullptr;
  Niko::InputHandler *input = nullptr;
};
