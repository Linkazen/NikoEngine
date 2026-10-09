NikoEngine is a little project that I'm doing in my spare time, built from the ground up using Vulkan.

# Dependencies

## Libraries Included

- [stb](https://github.com/nothings/stb) - single-file public domain (or MIT licensed) libraries for C/C (only stb_image.h required)
- [tiny-obj-loader](https://github.com/tinyobjloader/tinyobjloader/blob/release/tiny_obj_loader.h)
- [Dear ImGui](https://github.com/ocornut/imgui/tree/docking) - Docking version

## Not Included

- [VulkanSDK 1.4.309.0](https://vulkan.lunarg.com/sdk/home)
- [GLM 1.0.1](https://github.com/g-truc/glm)
- [glfw-3.4](https://www.glfw.org/download.html) - 64 bit windows binaries


# How to Run

## Installing Dependencies

### Fedora Linux

`sudo dnf install glfw-devel vulkan-loader-devel vulkan-validation-layers glm-devel`

## Build and Run

For Zed, you can simply run the built in `Build NikoEngine (Ninja)` debug task using `F4`. (You must have Ninja installed)
