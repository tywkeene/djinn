#include <SDL3/SDL.h>
#include <djinn/engine.hpp>
#include <djinn/error.hpp>

using namespace djinn;

int main(int argc, char *argv[]) {
    int width = 1600;
    int height = 900;
    Engine engine(width, height);
    engine.checkSDLVersion();
    int status = 0;
    while (status == DJINN_OK) {
        status = engine.mainLoop();
    }
    return 0;
}
