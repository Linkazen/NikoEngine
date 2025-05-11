#pragma once
#include "../Renderer/VulkanRenderer.h"

class BaseScene
{
public:
	BaseScene(VulkanRenderer* renderer) {
		mRenderer = renderer;

		//loadModel();
		// Load an object method

		Niko::Object obj1;
		obj1.mesh.loadObj("./assets/models/viking_room.obj");
		//obj1.mesh.LoadCube(obj1.mesh);
		obj1.transform.setTranslation(glm::vec3(1, 0, 0));
		objects.push_back(obj1);
		obj1.transform.setTranslation(glm::vec3(0, 1, 0));
		objects.push_back(obj1);
		obj1.transform.setTranslation(glm::vec3(0, 0, 1));
		objects.push_back(obj1);
	};

	virtual void Update();
	virtual void ImGuiRender();
	virtual void Render() {
		mRenderer->render(objects);
	};

	std::vector<Niko::Object>& getObjects() {
		return objects;
	}
private:
	std::vector<Niko::Object> objects = {};
	VulkanRenderer* mRenderer = nullptr;
};

