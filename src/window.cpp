#include "window.hpp"

int
initWindow(void) {
    // Initialization
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "WIP -- coolspace");
    InitAudioDevice();
    SetTargetFPS(60);

    return (0);
}
