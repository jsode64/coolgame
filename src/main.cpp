#include <iostream>

#include "SDL3/SDL.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
        std::cout << "SDL works!" << std::endl;
        return 0;
    } else {
        std::cout << "SDL didn't work!" << std::endl;
        return 1;
    }
}
