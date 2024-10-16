#pragma once

#include <SDL3/SDL.h>
#include <vector>

typedef uint32_t pixel_t;

class Framebuffer {

  private:
    int width;
    int height;
    SDL_Surface *surface;
    std::vector<uint32_t> pixels;

  public:
    Framebuffer(int w, int h)
        : width(w), height(h), pixels(width * height, 0xFF000000){};

    void setPixel(int x, int y, uint32_t color);
    void drawFilledTriangle(int width, int height, int x0, int y0, int x1,
                            int y1, int x2, int y2, uint32_t color);
    void drawFilledRect(int width, int height, int x, int y, int size,
                          uint32_t color);

    SDL_Texture *getTexture(SDL_Renderer *renderer);
};
