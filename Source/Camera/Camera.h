#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtx/quaternion.hpp>

struct UniformBufferObject {
  // Look into alignas
  // https://docs.vulkan.org/tutorial/latest/05_Uniform_buffers/01_Descriptor_pool_and_sets.html
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 proj;
};

class Camera {
public:
  Camera();

  /*void Rotate(float angle, glm::vec3 axis) {
          mQuatRotation = glm::normalize(glm::rotate(mQuatRotation, angle, axis
  * mQuatRotation));

          SetViewMatrix();
  }

  void Rotate(glm::quat qRot) {
          mQuatRotation *= qRot;

          SetViewMatrix();
  }*/

  // Rotates using euler angles in rotation
  void RotateEuler(glm::vec3 rotation);

  void SetViewMatrix();

  void SetDirections();

  UniformBufferObject ubo;

  glm::vec3 mTranslation;
  glm::vec3 mRotation;
  glm::vec3 mScale;
  float fov;

  glm::vec3 forward;
  glm::vec3 left;
  glm::vec3 up;

  // glm::quat mQuatRotation;
};
