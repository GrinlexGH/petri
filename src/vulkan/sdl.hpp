#pragma once
#include <span>
#include <stdexcept>
#include <string>

#include <SDL3/SDL.h>
#include <fmt/format.h>
#include <vulkan/vulkan.h>

namespace sdl {
class Context {
public:
    Context(const SDL_InitFlags flags);
    Context(const Context&) = delete;
    Context(Context&&) = delete;
    Context& operator=(const Context&) = delete;
    Context& operator=(Context&&) = delete;
    ~Context();

private:
    SDL_InitFlags m_flags = 0;
};

class Window {
public:
    Window(const char* title, int w, int h, SDL_WindowFlags flags);
    Window(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) = delete;
    ~Window();

    [[nodiscard]] SDL_Window* operator*() noexcept { return m_handle; }

private:
    SDL_Window* m_handle = nullptr;
};

namespace vulkan {
[[nodiscard]] PFN_vkGetInstanceProcAddr GetInstanceProcAddr();
[[nodiscard]] std::span<const char* const> GetInstanceExtensions();
}
}
