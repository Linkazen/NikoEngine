NikoEngine is a little project that I'm doing in my spare time, built from the ground up using Vulkan.

# Dependancies
- [VulkanSDK 1.4.309.0](https://vulkan.lunarg.com/sdk/home)
- [GLM 1.0.1](https://github.com/g-truc/glm)
- [glfw-3.4](https://www.glfw.org/download.html) - 64 bit windows binaries

### Preinstalled

- [stb](https://github.com/nothings/stb) - single-file public domain (or MIT licensed) libraries for C/C (only stb_image.h required)
- [tiny-obj-loader](https://github.com/tinyobjloader/tinyobjloader/blob/release/tiny_obj_loader.h)
- [Dear ImGui](https://github.com/ocornut/imgui/tree/docking) - Docking version

# Setup
## Windows
Install the [VulkanSDK using the official installer](https://vulkan.lunarg.com/sdk/home), this should allow CMake to see the Vulkan install.

Install the [vcpkg package manager](https://learn.microsoft.com/en-gb/vcpkg/get_started/get-started?pivots=shell-powershell) (Only cloning and running the bootstrap is needed), then proceed to install two dependancies using vcpkg;
- [glm](https://vcpkg.link/ports/glm)
- [glfw3](https://vcpkg.link/ports/glfw3)

Build the files using a CMake compiler (I use VSCode personally).

