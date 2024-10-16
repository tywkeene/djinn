#pragma once

#include <SDL3/SDL.h>
#include <djinn/framebuffer.hpp>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace djinn {
    class Renderer {
        private:
            int win_width;
            int win_height;

            SDL_Renderer* renderer;
            SDL_Window* window;
            std::shared_ptr<spdlog::logger> log;

            void cleanup() {
                if (window) SDL_DestroyWindow(window);
                if (renderer) SDL_DestroyRenderer(renderer);
                SDL_Quit();
            }

        public:
            ~Renderer() { SDL_DestroyRenderer(renderer); };
            Renderer(int w, int h) : win_width(w), win_height(h), log(spdlog::stdout_color_mt("renderer")) {
                if (!SDL_CreateWindowAndRenderer("djinn", win_width, win_height, 0, &window, &renderer)) {
                    log->error("SDL_CreateWindowAndRenderer error: {}", SDL_GetError());
                    SDL_Quit();
                    cleanup();
                }
                log->info("initialized");
            }
            int drawFrame(Framebuffer* frame);
    };
}; // namespace djinn
