#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include <SDL3/SDL.h>
#include <djinn/engine.hpp>

using namespace djinn;

const int TARGET_FPS = 60;
const int FRAME_TIME = (1000 / TARGET_FPS);

#define FRAME_START() uint32_t frame_start = SDL_GetTicks();

#define FRAME_END() uint32_t frame_time = (SDL_GetTicks() - frame_start); \
    if (frame_time < FRAME_TIME) \
        SDL_Delay(FRAME_TIME - frame_time); \


int Engine::mainLoop(void){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        FRAME_START();

        if (event.type == SDL_EVENT_QUIT) {
            return DJINN_EXIT;
        }
        int draw_status = drawBuffer(surface);
        if (draw_status == DJINN_ERR)
            return DJINN_ERR;

        FRAME_END();
    }
    return DJINN_OK;
}

int Engine::drawBuffer(SDL_Surface *buffer){
    SDL_Surface *window_surface = SDL_GetWindowSurface(window);
    if (window_surface == nullptr){
        log->error("window has no surface: {}", SDL_GetError());
        return DJINN_ERR;
    }
    if (SDL_ClearSurface(window_surface, 1.0, 1.0, 1.0, 1.0) != true){
        log->error("failed to clear surface: {}", SDL_GetError());
        return DJINN_ERR;
    }
    if (SDL_BlitSurface(buffer, nullptr, window_surface, nullptr) != true){
        log->error("failed to blit surface: {}", SDL_GetError());
        return DJINN_ERR;
    }
    if (SDL_UpdateWindowSurface(window) != true){
        log->error("failed to update window surface: {}", SDL_GetError());
        return DJINN_ERR;
    }
    SDL_RenderPresent(renderer);
    return DJINN_OK;
}

void Engine::checkSDLVersion(void){
    const int compiled = SDL_VERSION;
    const int linked = SDL_GetVersion();
    log->info("Compiled against SDL v{}.{}.{}",
            SDL_VERSIONNUM_MAJOR(compiled),
            SDL_VERSIONNUM_MINOR(compiled),
            SDL_VERSIONNUM_MICRO(compiled));
    log->info("Linked against SDL v{}.{}.{}",
            SDL_VERSIONNUM_MAJOR(linked),
            SDL_VERSIONNUM_MINOR(linked),
            SDL_VERSIONNUM_MICRO(linked));
}
