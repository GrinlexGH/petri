#pragma once
#include <stdexcept>
#include <string>

#include <SDL3/SDL.h>
#include <fmt/format.h>

namespace sdl {
class Context {
public:
    Context(const SDL_InitFlags flags) : m_flags(flags) {
        if (!SDL_Init(flags)) {
            std::string message = fmt::format("Failed to initialize SDL: {}", SDL_GetError());
            throw std::runtime_error { message };
        }
    }

    Context(const Context&) = delete;
    Context(Context&&) = delete;
    Context& operator=(const Context&) = delete;
    Context& operator=(Context&&) = delete;
    ~Context() { SDL_QuitSubSystem(m_flags); }

private:
    SDL_InitFlags m_flags = 0;
};

class Window {
public:
    Window(const char* title, int w, int h, SDL_WindowFlags flags)
        : m_handle(SDL_CreateWindow(title, w, h, flags)) {
        if (!m_handle) {
            std::string message = fmt::format("Failed to create SDL window: {}", SDL_GetError());
            throw std::runtime_error { message };
        }
    }

    Window(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) = delete;
    ~Window() { SDL_DestroyWindow(m_handle); }

    [[nodiscard]] SDL_Window* operator*() noexcept { return m_handle; }

private:
    SDL_Window* m_handle = nullptr;
};
}
