#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL.h>

#include <djinn/engine.hpp>
#include <djinn/framebuffer.hpp>
#include <djinn/renderer.hpp>
#include <djinn/error.hpp>

using namespace djinn;

int Engine::mainLoop(void) {
    SDL_Event event;
    Framebuffer *frame = new Framebuffer(1600, 900);

    uint32_t blue = (0 << 24) | (0 << 16) | (255 << 8) | 255;
    while (true) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                return DJINN_EXIT;
            }
        }
        frame->drawFilledRect(100,100,10,10, 100,blue);
        if (renderer.drawFrame(frame) == DJINN_ERR){
            log->error("failed to draw frame");
        }
    }
    return DJINN_OK;
}

void Engine::checkSDLVersion(void) {
    const int compiled = SDL_VERSION;
    const int linked = SDL_GetVersion();
    log->info("Compiled against SDL v{}.{}.{}", SDL_VERSIONNUM_MAJOR(compiled),
            SDL_VERSIONNUM_MINOR(compiled), SDL_VERSIONNUM_MICRO(compiled));
    log->info("Linked against SDL v{}.{}.{}", SDL_VERSIONNUM_MAJOR(linked),
            SDL_VERSIONNUM_MINOR(linked), SDL_VERSIONNUM_MICRO(linked));
}
