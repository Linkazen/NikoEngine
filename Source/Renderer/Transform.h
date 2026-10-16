#pragma once
#include "Primative.h"
#include <string>
#include <vector>

namespace Niko {
struct Transform {
  Transform() = default;

  void updateTransform();

  void setTranslation(glm::vec3 newTrans);
  glm::vec3 getTranslation();
  void setRotation(glm::vec3 newRot);
  glm::vec3 getRotation();
  void setScale(glm::vec3 newScale);
  glm::vec3 getScale();

  glm::mat4 getTransform();

private:
  glm::vec3 mTranslation = glm::vec3(0);
  glm::vec3 mRotation = glm::vec3(0);
  glm::vec3 mScale = glm::vec3(1);

  glm::mat4 mTransform = glm::identity<glm::mat4>();
};

struct Mesh {
public:
  std::vector<Vertex> vertices;
  std::vector<uint32_t> indices;

  Mesh();
  Mesh(std::string model_path);

  static void LoadCube(Mesh &m);

  void loadObj(std::string MODEL_PATH);

  VkBuffer vertexBuffer = {};
  VkDeviceMemory vertexBufferMemory = {};

  VkBuffer indexBuffer = {};
  VkDeviceMemory indexBufferMemory = {};

  bool bufCreated = false;
};

struct Object {
  Object() = default;

  Transform transform;
  Mesh mesh;
};
} // namespace Niko
