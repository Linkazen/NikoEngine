#include "Camera.h"

Camera::Camera() {
  mTranslation = glm::vec3(0, 0, 0);
  mScale = glm::vec3(1);
  SetDirections();

  ubo.model = glm::identity<glm::mat4>();
  ubo.view =
      glm::lookAt(mTranslation, mTranslation + forward, glm::vec3(0, 1, 0));
  ubo.proj =
      glm::perspective(glm::radians(90.0f), 800.f / (float)600.f, 0.1f, 100.0f);

  ubo.proj[1][1] *= -1;

  fov = glm::radians(90.f);
}

void Camera::RotateEuler(glm::vec3 rotation) {
  mRotation += rotation;

  if (mRotation.x > glm::pi<float>()) {
    mRotation.x -= glm::pi<float>() * 2;
  } else if (mRotation.x < -glm::pi<float>()) {
    mRotation.x += glm::pi<float>() * 2;
  }

  if (mRotation.y > glm::pi<float>()) {
    mRotation.y -= glm::pi<float>() * 2;
  } else if (mRotation.y < -glm::pi<float>()) {
    mRotation.y += glm::pi<float>() * 2;
  }

  if (mRotation.z > glm::pi<float>()) {
    mRotation.z -= glm::pi<float>() * 2;
  } else if (mRotation.z < -glm::pi<float>()) {
    mRotation.z += glm::pi<float>() * 2;
  }

  SetDirections();
  SetViewMatrix();
}

void Camera::SetViewMatrix() {
  ubo.view =
      glm::lookAt(mTranslation, mTranslation + forward, glm::vec3(0, 1, 0));
}
void Camera::SetDirections() {
  forward.x = glm::cos(mRotation.x) * glm::sin(mRotation.y);
  forward.y = -glm::sin(mRotation.x);
  forward.z = glm::cos(mRotation.x) * glm::cos(mRotation.y);
  forward = -forward;

  left.x = glm::cos(mRotation.y);
  left.y = 0;
  left.z = -glm::sin(mRotation.y);

  up = glm::cross(left, forward);
};
