#pragma once

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>
#include <set>
#include <algorithm> // Necessary for std::clamp
#include <fstream>
#include <unordered_map>

// ImGui Includes
#include <backends/imgui_impl_vulkan.h>
#include <backends/imgui_impl_glfw.h>
#include <misc/cpp/imgui_stdlib.h>

#include "variables.h"
#include "Transform.h"
#include "../Camera/Camera.h"
#include "TimeKeeper.h"
#include "InputHandler.h"

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	};
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities = {};
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class VulkanRenderer
{
public:
	void init();
	void cleanup(std::vector<Niko::Object>& objv);
	void render(std::vector<Niko::Object>& objVector);

	GLFWwindow* GetWindow() {
		return window;
	}

	Niko::InputHandler* Input = nullptr;

	void setInputHandler(Niko::InputHandler* ih) {
		Input = ih;

		auto KeysInputCallback = [](GLFWwindow* w, int k, int sc, int a, int m) {
			static_cast<VulkanRenderer*>(glfwGetWindowUserPointer(w))->Input->key_callback(w, k, sc, a, m);
			};

		auto MouseInputCallback = [](GLFWwindow* w, int k, int a, int m) {
			static_cast<VulkanRenderer*>(glfwGetWindowUserPointer(w))->Input->mouse_callback(w, k, a, m);
			};

		auto CursorInputCallback = [](GLFWwindow* w, double x, double y) {
			static_cast<VulkanRenderer*>(glfwGetWindowUserPointer(w))->Input->cursor_position_callback(w, x, y);
			};

		glfwSetKeyCallback(window, KeysInputCallback);
		glfwSetMouseButtonCallback(window, MouseInputCallback);
		glfwSetCursorPosCallback(window, CursorInputCallback);
		ImGui_ImplGlfw_InitForVulkan(window, true);
	}

	Camera& getPrimaryCamera() {
		return primCamera;
	}

private:
	GLFWwindow* window = nullptr;
	VkInstance instance = {};
	VkDebugUtilsMessengerEXT debugMessenger = {};
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkQueue graphicsQueue = {};
	VkDevice device = {};
	VkSurfaceKHR surface = {};
	VkQueue presentQueue = {};
	VkSwapchainKHR swapChain = {};
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat = {};
	VkExtent2D swapChainExtent = {};
	std::vector<VkImageView> swapChainImageViews;
	VkRenderPass renderPass = {};
	VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

	VkDescriptorSetLayout descriptorSetLayout = {};
	VkPipelineLayout pipelineLayout = {};
	VkPipeline graphicsPipeline = {};

	VkPipelineLayout gridPipelineLayout = {};
	VkPipeline gridPipeline = {};

	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkCommandPool commandPool = {};
	std::vector<VkCommandBuffer> commandBuffers;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void*> uniformBuffersMapped;
	VkDescriptorPool descriptorPool = {};
	VkDescriptorPool descriptorPoolImGui = {};
	std::vector<VkDescriptorSet> descriptorSets;

	VkImageView textureImageView = {};
	VkSampler textureSampler = {};
	uint32_t mipLevels = 0;
	VkImage textureImage = {};
	VkDeviceMemory textureImageMemory = {};

	VkImage depthImage = {};
	VkDeviceMemory depthImageMemory = {};
	VkImageView depthImageView = {};

	VkImage colorImage = {};
	VkDeviceMemory colorImageMemory = {};
	VkImageView colorImageView = {};

	uint32_t currentFrame = 0;
	bool framebufferResized = false;

	VkPipelineCache pipelineCache = VK_NULL_HANDLE;

	Camera primCamera;

	// * Runtime changeable bools for how the engine should work
	bool renderGrid = true;
	//

	VkShaderModule createShaderModule(const std::vector<char>& code);

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

	bool checkValidationLayerSupport();

	// Swap chain stuff
	void cleanupSwapChain();

	void recreateSwapChain();

	std::vector<const char*> getRequiredExtensions();

	// Creates a vulkan instance
	void createInstance();

	void initWindow();

	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	void initVulkan();

	void initImGui();

	bool hasStencilComponent(VkFormat format);

	VkFormat findDepthFormat();

	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

	void createDepthResources();

	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

	VkCommandBuffer beginSingleTimeCommands();

	void endSingleTimeCommands(VkCommandBuffer commandBuffer);

	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);

	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

	//// INIT VULKAN FUNCTIONS
	void createTextureSampler();

	void createTextureImageView();

	void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

	void createTextureImage();

	void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

	void createDescriptorSets();

	void createDescriptorPool();

	void createUniformBuffers();

	void createDescriptorSetLayout();

	void createIndexBuffer(Niko::Object& obj);

	void createVertexBuffer(Niko::Object& obj);

	void updateVertexBuffer(Niko::Object& obj);

	void createSyncObjects();

	void createCommandBuffers();

	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, std::vector<Niko::Object>& objVector);

	void createCommandPool();

	void createFramebuffers();

	void createRenderPass();

	void createGridGraphicsPipeline();

	void createGraphicsPipeline();

	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);

	void createImageViews();

	void createSwapChain();

	void createSurface();

	VkSampleCountFlagBits getMaxUsableSampleCount();

	void createColorResources();

	void createLogicalDevice();

	void pickPhysicalDevice();

	bool isDeviceSuitable(VkPhysicalDevice device);

	bool checkDeviceExtensionSupport(VkPhysicalDevice device);

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	void setupDebugMessenger();

	void updateUnformBuffer(uint32_t currentImage);

	void drawFrame(std::vector<Niko::Object>& objVector);

};

