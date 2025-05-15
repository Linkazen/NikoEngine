#include "Renderer/VulkanRenderer.h"
#include <imgui.h>
#include "Scene/BaseScene.h"

int main() {
    VulkanRenderer* app = new VulkanRenderer();
    TimeKeeper* time = new TimeKeeper();
    Niko::InputHandler* Input = new Niko::InputHandler();
    BaseScene* mainScene = new BaseScene(app);

    try {
        // Imgui init in vulkan app
        app->init();
        app->setInputHandler(Input);

        time->Begin();

        mainScene->setTimeKeeper(time);
        mainScene->setInputHandler(Input);

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
            Input->update_states();
        }
        app->cleanup(mainScene->getObjects());
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}