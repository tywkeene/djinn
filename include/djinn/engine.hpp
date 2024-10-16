#pragma once

#include <SDL3/SDL.h>
#include <djinn/renderer.hpp>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace djinn {

    class Engine {
        private:
            Renderer renderer;

            std::shared_ptr<spdlog::logger> log;

            void cleanup() {
                SDL_Quit();
            }

        public:
            ~Engine() {
                cleanup();
            };
            Engine(int w, int h) : renderer(Renderer(w, h)), log(spdlog::stdout_color_mt("djinn")) {
                    SDL_SetHintWithPriority(SDL_HINT_RENDER_DRIVER, "software",
                            SDL_HintPriority::SDL_HINT_OVERRIDE);

                    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
                        log->error("failed to initialize SDL: '{}'", SDL_GetError());
                        cleanup();
                    }
                }

            int mainLoop(void);
            void checkSDLVersion(void);
    };
};
