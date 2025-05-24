#include "Transform.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <unordered_map>

//#include "Transform.h"
//
//inline void Niko::Mesh::loadObj(std::string MODEL_PATH) {
//	
//}

void Niko::Mesh::loadObj(std::string MODEL_PATH)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.c_str())) {
		throw std::runtime_error(warn + err);
	}

	std::unordered_map<Vertex, uint32_t> uniqueVertices{};

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex vertex{};

			glm::mat4 rotMat = glm::identity<glm::mat4>();

			rotMat = glm::rotate(rotMat, glm::radians(90.f), glm::vec3(1,0,0));
			rotMat = glm::rotate(rotMat, glm::radians(180.f), glm::vec3(0,1,0));
			rotMat = glm::rotate(rotMat, glm::radians(-90.f), glm::vec3(0,0,1));

			vertex.pos = glm::vec4(
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2],
				1
			);

			vertex.pos = rotMat * vertex.pos;

			vertex.texCoord = {
				attrib.texcoords[2 * index.texcoord_index + 0],
				1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
			};

			vertex.color = { 1.0f, 1.0f, 1.0f };

			if (uniqueVertices.count(vertex) == 0) {
				uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
				vertices.push_back(vertex);
			}

			indices.push_back(uniqueVertices[vertex]);
		}
	}
}
