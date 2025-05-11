#include "BaseScene.h"

void BaseScene::Update()
{
	//if (Input->IsMousePressed(GLFW_MOUSE_BUTTON_RIGHT)) {
		//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		//	xpos = 0;
		//	oldxpos = 0;
		//	ypos = 0;
		//	oldypos = 0;

		//	if (glfwRawMouseMotionSupported()) {
		//		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		//	}
		//}
		//else if (Input->IsMouseReleased(GLFW_MOUSE_BUTTON_RIGHT)) {
		//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		//	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
		//	rotatedThisFrame = false;
		//}
		//else if (Input->IsMouseHeld(GLFW_MOUSE_BUTTON_RIGHT)) {

		//	glm::dvec2 diff(0);

		//	glfwGetCursorPos(window, &xpos, &ypos);

		//	if (oldxpos != 0 && oldypos != 0) {
		//		diff.y = -(xpos - oldxpos);
		//		diff.x = ypos - oldypos;

		//		primCamera.RotateEuler(glm::vec3(diff * (double)time.DeltaTime(), 0));
		//	}

		//	oldxpos = xpos;
		//	oldypos = ypos;

		//	// For freecam movement
		//	glm::vec3 trans = glm::vec3(0);
		//	if (Input->IsKeyHeld(GLFW_KEY_W)) {
		//		trans += primCamera.forward;
		//	}
		//	if (Input->IsKeyHeld(GLFW_KEY_S)) {
		//		trans -= primCamera.forward;
		//	}
		//	if (Input->IsKeyHeld(GLFW_KEY_A)) {
		//		trans += primCamera.right;
		//	}
		//	if (Input->IsKeyHeld(GLFW_KEY_D)) {
		//		trans -= primCamera.right;
		//	}

		//	if (trans != glm::vec3(0)) {
		//		primCamera.mTranslation += glm::normalize(trans) * time.DeltaTime();
		//		primCamera.SetViewMatrix();
		//	}
		//}
}

void BaseScene::ImGuiRender()
{
	ImGui::Begin("Inspector");

	uint16_t loop = 0;
	glm::vec3 tran;
	glm::vec3 rot;
	glm::vec3 scale;
	for (auto& obj : objects) {
		ImGui::PushID(loop);
		tran = obj.transform.getTranslation();
		rot = obj.transform.getRotation();
		scale = obj.transform.getScale();

		if (ImGui::DragFloat3("Translation", &tran.x)) {
			obj.transform.setTranslation(tran);
		};
		if (ImGui::DragFloat3("Rotation", &rot.x, 1.0f, -360, 360)) {
			obj.transform.setRotation(rot);
		};
		if (ImGui::DragFloat3("Scale", &scale.x)) {
			obj.transform.setScale(scale);
		};
		ImGui::PopID();
		ImGui::Separator();
		loop++;
	}

	ImGui::End();
}
