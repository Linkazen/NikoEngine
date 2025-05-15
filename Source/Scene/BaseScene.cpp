#include "BaseScene.h"

void BaseScene::Update()
{
	if (input->IsMousePressed(GLFW_MOUSE_BUTTON_RIGHT)) {
		input->changeCursorInputMode(mRenderer->GetWindow(), Niko::CursorMode::DISABLED);
	}
	else if (input->IsMouseReleased(GLFW_MOUSE_BUTTON_RIGHT)) {
		input->changeCursorInputMode(mRenderer->GetWindow(), Niko::CursorMode::NORMAL);
	}
	else if (input->IsMouseHeld(GLFW_MOUSE_BUTTON_RIGHT)) {

		glm::dvec2 diff = input->cursorDeltaDistance();
		Camera& primCamera = mRenderer->getPrimaryCamera();

		primCamera.RotateEuler(glm::vec3(diff.y * (double)time->DeltaTime(), diff.x * (double)time->DeltaTime(), 0));

		// For freecam movement
		glm::vec3 trans = glm::vec3(0);
		if (input->IsKeyHeld(GLFW_KEY_W)) {
			trans += primCamera.forward;
		}
		if (input->IsKeyHeld(GLFW_KEY_S)) {
			trans -= primCamera.forward;
		}
		if (input->IsKeyHeld(GLFW_KEY_A)) {
			trans -= primCamera.left;
		}
		if (input->IsKeyHeld(GLFW_KEY_D)) {
			trans += primCamera.left;
		}
		if (input->IsKeyHeld(GLFW_KEY_SPACE)) {
			trans += primCamera.up;
		}
		if (input->IsKeyHeld(GLFW_KEY_LEFT_CONTROL)) {
			trans -= primCamera.up;
		}

		if (trans != glm::vec3(0)) {
			primCamera.mTranslation += glm::normalize(trans) * time->DeltaTime();
			primCamera.SetViewMatrix();
		}
	}
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
