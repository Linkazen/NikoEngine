#pragma once
#include "Primative.h"
#include <string>

#include <stdexcept>

namespace Niko {
	struct Transform {
		glm::vec3 translation;
		glm::vec3 rotation;
		glm::vec3 scale;

		Transform() = default;
	};

	struct Mesh {
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		Mesh() {
			vertices = {};
			indices = {};
		}
		Mesh(std::string model_path) {
			loadObj(model_path);
		}

		void loadObj(std::string MODEL_PATH);
	};

	struct Object {
		Object() = default;

		Transform transform;
		Mesh mesh;

		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory = {};

		VkBuffer indexBuffer = {};
		VkDeviceMemory indexBufferMemory = {};

	};
}