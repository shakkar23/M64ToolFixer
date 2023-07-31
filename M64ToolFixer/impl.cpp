#include "main.hpp"

#include <filesystem>
#include <fstream>

uint32_t pext(uint32_t source, uint32_t mask) {
    uint32_t result = 0;
    uint32_t iter = 1;

    for (int i = 0; i < 32; i++) {
        if (((1 << i) & mask) & source) {
            result |= iter;
            iter <<= 1;
        }
    }

    return result;
}


Uint32 getpixel(SDL_Surface* surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    // Here p is the address to the pixel we want to retrieve
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16*)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32*)p;
        break;

    default:
        // shouldn't happen, but avoids warnings
        return 0;
    }
}


void fix_file(std::string path) {
    SDL_Surface* image = IMG_Load(path.data());

    if (!image) {

        std::cout << "image null\n";
        return;
    }
    for (int y = 0; y < image->h; ++y)
        for (int x = 0; x < image->w; ++x) {
            uint32_t* Pixel = (uint32_t*)((Uint8*)image->pixels
                + (y)*image->pitch
                + (x)*image->format->BytesPerPixel);

            ShakColor pix;
            pix.r = pext(*Pixel, image->format->Rmask);
            pix.g = pext(*Pixel, image->format->Gmask);
            pix.b = pext(*Pixel, image->format->Bmask);
            pix.a = pext(*Pixel, image->format->Amask);

        }
    std::string new_path = path.data();

    new_path.replace(new_path.find(".bmp"), 4, ".png");

    IMG_SavePNG(image, new_path.data());
    SDL_FreeSurface(image);
}


void fix_mtl(std::string path) {

    // search entire file for the text "bmp" and replace it with "png"
    std::fstream file(path);

    if (!file.is_open()) {
        std::cout << "file not open\n";
        return;
    }

    std::string line;
    std::string new_file;

    while (std::getline(file, line)) {
        std::string new_line = line;
        std::string_view view = line;
        while (view.find("bmp") != std::string_view::npos) {
            new_line.replace(view.find("bmp"), 3, "png");
            view = new_line;
        }
        new_file += new_line + '\n';
    }

    file.close();
    file.open(path, std::ios::out | std::ios::trunc);
    file << new_file;
    file.close();

}