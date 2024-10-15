#pragma once

#include <SDL3/SDL.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace djinn {
    const int DJINN_OK = 0;
    const int DJINN_ERR = 1;
    const int DJINN_EXIT = 2;

    class Engine{
        private:
            int win_width;
            int win_height;

            SDL_Renderer *renderer;
            SDL_Window *window;
            SDL_Surface *surface;
            std::shared_ptr<spdlog::logger> log;

            void cleanup(){
                if (window) SDL_DestroyWindow(window);
                if (renderer) SDL_DestroyRenderer(renderer);
                if (surface) SDL_DestroySurface(surface);
                SDL_Quit();
            }
        public:
            ~Engine(){
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
            };
            Engine(int w, int h) :
                win_width(w),
                win_height(h),
                log(spdlog::stdout_color_mt("djinn")){
                    SDL_SetHintWithPriority(SDL_HINT_RENDER_DRIVER, "software", SDL_HintPriority::SDL_HINT_OVERRIDE);

                    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS) != true){
                        log->error("failed to initialize SDL: '{}'", SDL_GetError());
                        cleanup();
                    }
                    window = SDL_CreateWindow("djinn", win_width, win_height, 0);
                    if (window == nullptr) {
                        log->error("SDL_CreateWindow error: {}",  SDL_GetError());
                        SDL_Quit();
                        cleanup();
                    }
                    renderer = SDL_CreateRenderer(window, nullptr);
                    if (renderer == nullptr) {
                        log->error("SDL_CreateRenderer error: {}", SDL_GetError());
                        cleanup();
                    }
                    surface = SDL_CreateSurface(win_width, win_height, SDL_PixelFormat::SDL_PIXELFORMAT_RGBA32);
                    if (renderer == nullptr) {
                        log->error("SDL_CreateSurface error: {}", SDL_GetError());
                        cleanup();
                    }
                }

            int mainLoop(void);
            int drawBuffer(SDL_Surface *buffer);
            void checkSDLVersion(void);
    };
};
