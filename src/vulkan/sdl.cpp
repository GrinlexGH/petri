#include <SDL3/SDL_vulkan.h>

#include "sdl.hpp"

namespace sdl {
Context::Context(const SDL_InitFlags flags) : m_flags(flags) {
    if (!SDL_Init(flags)) {
        std::string message = fmt::format("Failed to initialize SDL: {}", SDL_GetError());
        throw std::runtime_error { message };
    }
}

Context::~Context() { SDL_QuitSubSystem(m_flags); }

Window::Window(const char* title, int w, int h, SDL_WindowFlags flags)
    : m_handle(SDL_CreateWindow(title, w, h, flags)) {
    if (!m_handle) {
        std::string message = fmt::format("Failed to create SDL window: {}", SDL_GetError());
        throw std::runtime_error { message };
    }
}

Window::~Window() { SDL_DestroyWindow(m_handle); }

namespace vulkan {
PFN_vkGetInstanceProcAddr GetInstanceProcAddr() {
    return reinterpret_cast<PFN_vkGetInstanceProcAddr>(SDL_Vulkan_GetVkGetInstanceProcAddr());
}

std::span<const char* const> GetInstanceExtensions() {
    Uint32 cow = 0;
    SDL_Vulkan_GetInstanceExtensions(&cow);
    return { SDL_Vulkan_GetInstanceExtensions(nullptr), cow };
}
}
}
