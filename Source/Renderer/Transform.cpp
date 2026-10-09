#include "Transform.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include <unordered_map>

void Niko::Mesh::LoadCube(Mesh &m) {
  m.indices = {// Top
               7, 6, 2, 2, 3, 7,

               // Bottom
               5, 4, 0, 0, 1, 5,

               // Left
               6, 2, 0, 0, 4, 6,

               // Right
               7, 3, 1, 1, 5, 7,

               // Front
               3, 2, 0, 0, 1, 3,

               // Back
               7, 6, 4, 4, 5, 7};

  m.vertices = {
      Vertex{glm::vec3(-1, -1, 0.5), glm::vec3(1), glm::vec2(0)},  // 0
      Vertex{glm::vec3(1, -1, 0.5), glm::vec3(1), glm::vec2(0)},   // 1
      Vertex{glm::vec3(-1, 1, 0.5), glm::vec3(1), glm::vec2(0)},   // 2
      Vertex{glm::vec3(1, 1, 0.5), glm::vec3(1), glm::vec2(0)},    // 3
      Vertex{glm::vec3(-1, -1, -0.5), glm::vec3(1), glm::vec2(0)}, // 4
      Vertex{glm::vec3(1, -1, -0.5), glm::vec3(1), glm::vec2(0)},  // 5
      Vertex{glm::vec3(-1, 1, -0.5), glm::vec3(1), glm::vec2(0)},  // 6
      Vertex{glm::vec3(1, 1, -0.5), glm::vec3(1), glm::vec2(0)}    // 7
  };
}

void Niko::Mesh::loadObj(std::string modelPath) {
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn, err;

  if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err,
                        modelPath.c_str())) {
    throw std::runtime_error(warn + err);
  }

  std::unordered_map<Vertex, uint32_t> uniqueVertices{};

  for (const auto &shape : shapes) {
    for (const auto &index : shape.mesh.indices) {
      Vertex vertex{};

      glm::mat4 rotMat = glm::identity<glm::mat4>();

      // Rotates models so they are the correct orientation
      // ? Could possibly simplify this? Or maybe even make this redundant by
      // doing it engine side, instead of model loading side
      rotMat = glm::rotate(rotMat, glm::radians(90.f), glm::vec3(1, 0, 0));
      rotMat = glm::rotate(rotMat, glm::radians(180.f), glm::vec3(0, 1, 0));
      rotMat = glm::rotate(rotMat, glm::radians(-90.f), glm::vec3(0, 0, 1));

      vertex.pos = glm::vec4(attrib.vertices[3 * index.vertex_index + 0],
                             attrib.vertices[3 * index.vertex_index + 1],
                             attrib.vertices[3 * index.vertex_index + 2], 1);

      vertex.pos = rotMat * vertex.pos;

      vertex.texCoord = {attrib.texcoords[2 * index.texcoord_index + 0],
                         1.0f - attrib.texcoords[2 * index.texcoord_index + 1]};

      vertex.color = {1.0f, 1.0f, 1.0f};

      if (uniqueVertices.count(vertex) == 0) {
        uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
        vertices.push_back(vertex);
      }

      indices.push_back(uniqueVertices[vertex]);
    }
  }
}
