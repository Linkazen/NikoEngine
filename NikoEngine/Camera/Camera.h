#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/hash.hpp>
#include <gtx/quaternion.hpp>

struct UniformBufferObject {
	// Look into alignas https://docs.vulkan.org/tutorial/latest/05_Uniform_buffers/01_Descriptor_pool_and_sets.html
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

class Camera
{
public:
	Camera() {
		mTranslation = glm::vec3(0,0,0);
		mScale = glm::vec3(1);
		SetDirections();

		ubo.model = glm::rotate(glm::mat4(1), glm::radians(90.f), glm::vec3(-1, 0, 0));
		ubo.view = glm::lookAt(mTranslation, mTranslation + forward, glm::vec3(0,1,0));
		ubo.proj = glm::perspective(glm::radians(90.0f), 800.f / (float)600.f, 0.1f, 100.0f);

		ubo.proj[1][1] *= -1;

		fov = glm::radians(90.f);
	};

	/*void Rotate(float angle, glm::vec3 axis) {
		mQuatRotation = glm::normalize(glm::rotate(mQuatRotation, angle, axis * mQuatRotation));

		SetViewMatrix();
	}

	void Rotate(glm::quat qRot) {
		mQuatRotation *= qRot;

		SetViewMatrix();
	}*/

	// Rotates using euler angles in rotation
	void RotateEuler(glm::vec3 rotation) {
		mRotation += rotation;

		if (mRotation.x > glm::pi<float>()) {
			mRotation.x -= glm::pi<float>() * 2;
		}
		else if (mRotation.x < -glm::pi<float>()) {
			mRotation.x += glm::pi<float>() * 2;
		}

		if (mRotation.y > glm::pi<float>()) {
			mRotation.y -= glm::pi<float>() * 2;
		}
		else if (mRotation.y < -glm::pi<float>()) {
			mRotation.y += glm::pi<float>() * 2;

		}

		if (mRotation.z > glm::pi<float>()) {
			mRotation.z -= glm::pi<float>() * 2;
		}
		else if (mRotation.z < -glm::pi<float>()) {
			mRotation.z += glm::pi<float>() * 2;
		}

		SetDirections();
		SetViewMatrix();
	}

	void SetViewMatrix() {
		ubo.view = glm::lookAt(mTranslation, mTranslation + forward, glm::vec3(0, 1, 0));
	}

	void SetDirections() {
		forward.x = cos(mRotation.x) * sin(mRotation.y);
		forward.y = -sin(mRotation.x);
		forward.z = cos(mRotation.x) * cos(mRotation.y);
		forward = -forward;

		left.x = cos(mRotation.y);
		left.y = 0;
		left.z = -sin(mRotation.y);

		up = cross(left, forward);
	}

	UniformBufferObject ubo;

	glm::vec3 mTranslation;
	glm::vec3 mRotation;
	glm::vec3 mScale;
	float fov;

	glm::vec3 forward;
	glm::vec3 left;
	glm::vec3 up;

	//glm::quat mQuatRotation;
};

