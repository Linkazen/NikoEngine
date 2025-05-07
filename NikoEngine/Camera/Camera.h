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
		mRotation = glm::quat(glm::vec3(0));
		mScale = glm::vec3(1);

		ubo.model = glm::mat4(1);
		ubo.view = glm::lookAt(mTranslation, mTranslation + (glm::vec3(0, 0, 1) * mRotation), glm::vec3(0,1,0));
		ubo.proj = glm::perspective(glm::radians(90.0f), 800.f / (float)600.f, 0.1f, 100.0f);

		ubo.proj[1][1] *= -1;

		fov = glm::radians(90.f);
	};

	void Rotate(float angle, glm::vec3 axis) {
		mRotation = glm::normalize(glm::rotate(mRotation, angle, axis * mRotation));

		ubo.view = glm::lookAt(mTranslation, mTranslation + (glm::vec3(0, 0, 1) * mRotation), glm::vec3(0, 1, 0));
	}

	UniformBufferObject ubo;

	glm::vec3 mTranslation;
	glm::quat mRotation;
	glm::vec3 mScale;
	float fov;
};

