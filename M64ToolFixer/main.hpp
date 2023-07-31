#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
// TODO: Reference additional headers your program requires here.

void fix_file(std::string path);
void fix_mtl(std::string path);

struct ShakColor {
    ShakColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) : b(b), g(g), r(r), a(a) {}
    ShakColor() {}
    Uint8 b{}, g{}, r{}, a{};

    constexpr inline explicit operator Uint32() {
        return
            (b << (8 * 3)) &
            (g << (8 * 2)) &
            (r << (8 * 1)) &
            (a << (8 * 0));
    }
    constexpr inline explicit ShakColor(Uint32 input) {
        this->b = (input >> (8 * 3));
        this->g = (input >> (8 * 2));
        this->r = (input >> (8 * 1));
        this->a = (input >> (8 * 0));
    }

};
