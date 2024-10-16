#include "SDL3/SDL_render.h"
#include <SDL3/SDL.h>
#include <djinn/framebuffer.hpp>
#include <iostream>

void Framebuffer::setPixel(int x, int y, uint32_t color) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        pixels[y * width + x] = color;
    }
}

void Framebuffer::drawFilledRect(int width, int height, int x, int y,
        int size, uint32_t color) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int pixelX = x + i;
            int pixelY = y + j;
            if (pixelX >= 0 && pixelX < width && pixelY >= 0 &&
                    pixelY < height) {
                setPixel(pixelX, pixelY, color);
            }
        }
    }
}

void Framebuffer::drawFilledTriangle(int width, int height, int x0, int y0,
        int x1, int y1, int x2, int y2,
        uint32_t color) {
    if (y0 > y1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    if (y0 > y2) {
        std::swap(x0, x2);
        std::swap(y0, y2);
    }
    if (y1 > y2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    auto scanLine = [&](int y, int x_start, int x_end) {
        for (int x = x_start; x <= x_end; ++x) {
            setPixel(x, y, color);
        }
    };

    auto interpolate = [](int y, int y0, int x0, int y1, int x1) {
        return x0 + (y - y0) * (x1 - x0) / (y1 - y0);
    };

    for (int y = y0; y <= y1; ++y) {
        int x_start = interpolate(y, y0, x0, y2, x2);
        int x_end = interpolate(y, y0, x0, y1, x1);
        scanLine(y, std::min(x_start, x_end), std::max(x_start, x_end));
    }

    for (int y = y1; y <= y2; ++y) {
        int x_start = interpolate(y, y0, x0, y2, x2);
        int x_end = interpolate(y, y1, x1, y2, x2);
        scanLine(y, std::min(x_start, x_end), std::max(x_start, x_end));
    }
}

SDL_Texture *Framebuffer::getTexture(SDL_Renderer *renderer) {
    surface = SDL_CreateSurfaceFrom(width, height, SDL_PIXELFORMAT_RGBA8888,
            pixels.data(), width * 4);
    if (!surface) {
        std::cerr << "SDL_CreateSurfaceFrom failed: " << SDL_GetError() << "\n";
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError()
            << "\n";
        return nullptr;
    }
    return texture;
}
