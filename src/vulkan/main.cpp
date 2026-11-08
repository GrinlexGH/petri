#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <fmt/format.h>

#include "sdl.hpp"

void Run() {
    sdl::Context sdlContext { SDL_INIT_VIDEO };
    sdl::Window window { "vulkan", 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN };

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
