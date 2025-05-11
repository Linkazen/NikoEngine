#include "Renderer/VulkanRenderer.h"
#include <imgui.h>
#include "Scene/BaseScene.h"



int main() {
    VulkanRenderer* app = new VulkanRenderer();
    TimeKeeper* time = new TimeKeeper();
    BaseScene* mainScene = new BaseScene(app);

    try {
        // Imgui init in vulkan app
        app->init();
        time->Begin();

        while (!glfwWindowShouldClose(app->GetWindow())) {
            glfwPollEvents();

            mainScene->Update();

            // Handles the new ImGui frame
            ImGui_ImplVulkan_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            mainScene->ImGuiRender();
            mainScene->Render();

            time->Tick();
        }
        app->cleanup(mainScene->getObjects());
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}