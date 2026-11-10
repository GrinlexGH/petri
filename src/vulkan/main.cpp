#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <VkBootstrap.h>
#include <fmt/format.h>
#include <vulkan/vulkan_raii.hpp>

#include "petri/logging.hpp"
#include "sdl.hpp"

namespace {
VKAPI_ATTR vk::Bool32 VKAPI_CALL DebugCallback(
    const vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    vk::DebugUtilsMessageTypeFlagsEXT /*messageTypes*/,
    const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData, void* /*pUserData*/
) {
    switch (messageSeverity) {
        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose:
        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo:
            pt::log::Info(pt::log::Category::eVulkan, "{}", pCallbackData->pMessage);
            break;
        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning:
            pt::log::Warning(pt::log::Category::eVulkan, "{}", pCallbackData->pMessage);
            break;
        case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError:
            pt::log::Error(pt::log::Category::eVulkan, "{}\n", pCallbackData->pMessage);
            break;
    }

    return vk::False;
}
}

void Run() {
    sdl::Context sdlContext { SDL_INIT_VIDEO };
    sdl::Window window { "vulkan", 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN };

    PFN_vkGetInstanceProcAddr gipa = sdl::vulkan::GetInstanceProcAddr();

    auto systemInfoResult = vkb::SystemInfo::get_system_info(gipa);
    if (!systemInfoResult) {
        const std::string message =
            fmt::format("Failed to query vulkan system info: {}", systemInfoResult.error().message());
        throw std::runtime_error { message };
    }
    const vkb::SystemInfo& systemInfo = systemInfoResult.value();

    vkb::InstanceBuilder instanceBuilder;
    instanceBuilder.require_api_version(1, 3)
        .set_engine_version(2026, 0)
        .set_app_version(2026, 0)
        .set_engine_name("petri")
        .set_app_name("vulkan");

    for (const auto ext : sdl::vulkan::GetInstanceExtensions()) {
        instanceBuilder.enable_extension(ext);
    }

    if (systemInfo.debug_utils_available) {
        instanceBuilder
#ifndef ARCH_32
            .request_validation_layers()
#endif
            .enable_extension(vk::EXTDebugUtilsExtensionName)
            .set_debug_callback(reinterpret_cast<PFN_vkDebugUtilsMessengerCallbackEXT>(
                reinterpret_cast<std::uintptr_t>(DebugCallback)))
            .set_debug_messenger_severity(static_cast<VkDebugUtilsMessageSeverityFlagsEXT>(
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eError))
            .set_debug_messenger_type(static_cast<VkDebugUtilsMessageTypeFlagsEXT>(
                vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
                vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance));
    }

    auto instanceResult = instanceBuilder.build();
    if (!instanceResult) {
        const std::string message =
            fmt::format("Failed to query vulkan system info: {}", instanceResult.error().message());
        throw std::runtime_error { message };
    }
    const vkb::Instance& instance = instanceResult.value();

    bool quit = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_EVENT_QUIT:
                    quit = true;
            }
        }
    }
}

int main() {
    try {
        Run();
    } catch (const std::exception& e) {
        fmt::println("{}", e.what());
        return 1;
    }
}
