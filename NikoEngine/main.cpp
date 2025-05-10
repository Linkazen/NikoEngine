#include "Renderer/VulkanRenderer.h"
#include <imgui.h>



int main() {
    VulkanRenderer app;

    try {
        // Imgui init in vulkan app
        app.init();

        while (!glfwWindowShouldClose(app.GetWindow())) {
            app.run();
        }
        app.cleanup();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}