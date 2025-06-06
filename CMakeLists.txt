cmake_minimum_required(VERSION 3.10.0)
project(NikoEngine VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# These are the CPP files that actually have code in them,
# it seems like CPP files without code do not need to be placed here.
set(SOURCE 
    "Source/main.cpp"
    "Source/Renderer/VulkanRenderer.cpp"
    "Source/Renderer/Transform.cpp"
    "Source/Scene/BaseScene.cpp"
)

add_executable(NikoEngine ${SOURCE})

target_include_directories(NikoEngine PUBLIC 
    "${PROJECT_SOURCE_DIR}/Source/Libraries" 
    "${PROJECT_SOURCE_DIR}/Source/Libraries/ImGui" 
    "${PROJECT_SOURCE_DIR}/Source/Libraries/ImGui/backends" 
    "${PROJECT_SOURCE_DIR}/Source/Libraries/stb" 
    "${PROJECT_SOURCE_DIR}/Source/Libraries/tol" 
)

# Handles compiling the ImGui Library
add_library(ImGui STATIC
    "Source/Libraries/ImGui/imgui.cpp"
    "Source/Libraries/ImGui/imgui_demo.cpp"
    "Source/Libraries/ImGui/imgui_draw.cpp"
    "Source/Libraries/ImGui/imgui_widgets.cpp"
    "Source/Libraries/ImGui/imgui_tables.cpp"
    "Source/Libraries/ImGui/backends/imgui_impl_glfw.cpp"
    "Source/Libraries/ImGui/backends/imgui_impl_vulkan.cpp"
)

# Compiles required packages
find_package(Vulkan REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})

find_package(glm CONFIG REQUIRED)

find_package(glfw3 CONFIG REQUIRED)

target_include_directories(ImGui PUBLIC 
    "${PROJECT_SOURCE_DIR}/Source/Libraries/ImGui" 
)
target_link_libraries(ImGui Vulkan::Vulkan glfw)

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan glm::glm glfw ImGui)

# Copies the assets into the build
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Source/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)

add_custom_target(copy_shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Source/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders
)

add_dependencies(NikoEngine copy_assets)
add_dependencies(NikoEngine copy_shaders)