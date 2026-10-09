#pragma once
#include "Primative.h"
#include <string>
#include <vector>

namespace Niko {
struct Transform {
  Transform() = default;

  void updateTransform() {
    mTransform = glm::identity<glm::mat4>();

    mTransform = glm::translate(mTransform, mTranslation);

    mTransform =
        glm::rotate(mTransform, glm::radians(mRotation.x), glm::vec3(1, 0, 0));
    mTransform =
        glm::rotate(mTransform, glm::radians(mRotation.y), glm::vec3(0, 1, 0));
    mTransform =
        glm::rotate(mTransform, glm::radians(mRotation.z), glm::vec3(0, 0, 1));

    mTransform = glm::scale(mTransform, mScale);
  }

  void setTranslation(glm::vec3 newTrans) {
    mTranslation = newTrans;
    updateTransform();
  }
  glm::vec3 getTranslation() { return mTranslation; }
  void setRotation(glm::vec3 newRot) {
    mRotation = newRot;
    updateTransform();
  }
  glm::vec3 getRotation() { return mRotation; }
  void setScale(glm::vec3 newScale) {
    mScale = newScale;
    updateTransform();
  }
  glm::vec3 getScale() { return mScale; }

  glm::mat4 getTransform() { return mTransform; }

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

  Mesh() {
    vertices = {};
    indices = {};
  }
  Mesh(std::string model_path) { loadObj(model_path); }

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
