#pragma once
#include "Primative.h"
#include <string>

#include <stdexcept>

namespace Niko {
	struct Transform {
		glm::vec3 translation = glm::vec3(0);
		glm::vec3 rotation = glm::vec3(0);
		glm::vec3 scale = glm::vec3(1);

		glm::mat4 mTransform = glm::identity<glm::mat4>();

		void updateTransform() {
			mTransform = glm::identity<glm::mat4>();

			mTransform = glm::translate(mTransform, translation);
			mTransform = glm::rotate(mTransform, glm::radians(rotation.x), glm::vec3(1, 0, 0));
			mTransform = glm::rotate(mTransform, glm::radians(rotation.y), glm::vec3(0, 1, 0));
			mTransform = glm::rotate(mTransform, glm::radians(rotation.z), glm::vec3(0, 0, 1));


			mTransform = glm::scale(mTransform, scale);
		}

		Transform() = default;
	};

	struct Mesh {
	public:
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		Mesh() {
			vertices = {};
			indices = {};
		}
		Mesh(std::string model_path) {
			loadObj(model_path);
		}

		static void LoadCube(Mesh& m) {
			m.indices = {
				//Top
				7, 6, 2,
				2, 3, 7,

				//Bottom
				5, 4, 0,
				0, 1, 5,

				//Left
				6, 2, 0,
				0, 4, 6,

				//Right
				7, 3, 1,
				1, 5, 7,

				//Front
				3, 2, 0,
				0, 1, 3,

				//Back
				7, 6, 4,
				4, 5, 7
			};

			m.vertices = {
				Vertex{glm::vec3(-1, -1,  0.5), glm::vec3(1), glm::vec2(0)}, //0
				Vertex{glm::vec3( 1, -1,  0.5), glm::vec3(1), glm::vec2(0)}, //1
				Vertex{glm::vec3(-1,  1,  0.5), glm::vec3(1), glm::vec2(0)}, //2
				Vertex{glm::vec3( 1,  1,  0.5), glm::vec3(1), glm::vec2(0)}, //3
				Vertex{glm::vec3(-1, -1, -0.5), glm::vec3(1), glm::vec2(0)}, //4
				Vertex{glm::vec3( 1, -1, -0.5), glm::vec3(1), glm::vec2(0)}, //5
				Vertex{glm::vec3(-1,  1, -0.5), glm::vec3(1), glm::vec2(0)}, //6
				Vertex{glm::vec3( 1,  1, -0.5), glm::vec3(1), glm::vec2(0)} //7
			};
		}

		void loadObj(std::string MODEL_PATH);

		VkBuffer vertexBuffer = {};
		VkDeviceMemory vertexBufferMemory = {};

		VkBuffer indexBuffer = {};
		VkDeviceMemory indexBufferMemory = {};
	};

	struct Object {
		Object() = default;

		Transform transform;
		Mesh mesh;
	};
}