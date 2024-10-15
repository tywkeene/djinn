#include <SDL3/SDL.h>
#include <djinn/engine.hpp>

using namespace djinn;

int main(int argc, char *argv[]) {
    Engine engine(1600, 900);
    engine.checkSDLVersion();
    int status = 0;
    while (status == DJINN_OK) {
        status = engine.mainLoop();
    }
    return 0;
}
