#include "Renderer/VulkanRenderer.h"
#include <imgui.h>
#include "Scene/BaseScene.h"



int main() {
    VulkanRenderer* app = new VulkanRenderer();
    BaseScene* mainScene = new BaseScene(app);

    try {
        // Imgui init in vulkan app
        app->init();

        while (!glfwWindowShouldClose(app->GetWindow())) {
            mainScene->HandleInput();
            mainScene->Update();
            mainScene->ImGuiRender();
            mainScene->Render();

            app->run();
        }
        app->cleanup(mainScene->getObjects());
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}