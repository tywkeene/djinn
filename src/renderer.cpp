#include <djinn/renderer.hpp>
#include <djinn/error.hpp>

using namespace djinn;

const int TARGET_FPS = 60;
const int FRAME_TIME = (1000 / TARGET_FPS);

#define FRAME_START() uint32_t frame_start = SDL_GetTicks();

#define FRAME_END()                                                            \
    uint32_t frame_time = (SDL_GetTicks() - frame_start);                      \
    if (frame_time < FRAME_TIME)                                               \
        SDL_Delay(FRAME_TIME - frame_time);

uint32_t blue = (0 << 24) | (0 << 16) | (255 << 8) | 255;

int Renderer::drawFrame(Framebuffer *frame){
    FRAME_START();
    SDL_Texture *texture = frame->getTexture(renderer);
    if (!texture) {
        log->error("null texture: {}", SDL_GetError());
        return DJINN_ERR;
    }

    SDL_RenderClear(renderer);
    if (!SDL_RenderTexture(renderer, texture, nullptr, nullptr)) {
        log->error("failed to render texture: {}", SDL_GetError());
        return DJINN_ERR;
    }
    SDL_RenderPresent(renderer);
    FRAME_END();
    return DJINN_OK;
}
