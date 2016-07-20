#include "sprite.h"
#include "stb_image.h"
#include "SDL.h"
#include <cstdio>

namespace ex {

    void makemask(uint32_t & r, uint32_t & g, uint32_t & b, uint32_t & a);

    sprite::sprite(SDL_Renderer * renderer, const char * file, int framesx, int framesy)
        : renderer(renderer)
        , framesx(framesx)
        , framesy(framesy)
    {
        int bpp;
        unsigned char * pixels = stbi_load(file, &w, &h, &bpp, 0);
        make(pixels, bpp);
    }

    sprite::sprite(SDL_Renderer * renderer, const unsigned char * data, unsigned int len, int framesx, int framesy)
        : renderer(renderer)
        , framesx(framesx)
        , framesy(framesy)
    {
        int bpp;
        unsigned char * pixels = stbi_load_from_memory(data, len, &w, &h, &bpp, 0);
        make(pixels, bpp);
    }

    void sprite::render(int framex, int framey, int x, int y, double angle) {
        SDL_Rect srcrect = { (w/framesx) * framex, (h/framesy) * framey, w/framesx, h/framesy};
        SDL_Rect dstrect = {x, y, srcrect.w, srcrect.h};
        SDL_RenderCopyEx(renderer, texture, &srcrect, &dstrect, angle, NULL, SDL_FLIP_NONE);
    }

    sprite::~sprite() {
        if (texture) SDL_DestroyTexture(texture);
    }

    void sprite::render(int x, int y, double angle) {
        render(0, 0, x, y, angle);
    }

    sprite::sprite(sprite && other)
        : texture(other.texture)
        , renderer(other.renderer)
        , w(other.w), h(other.h)
        , framesx(other.framesx)
        , framesy(other.framesy)
    {
        printf("moving.\n");
        other.texture = nullptr;
        other.renderer = nullptr;
    }

    sprite::sprite(const sprite & other) {
        printf("copying.\n");
    }

    void sprite::make(unsigned char * pixels, int bpp) {
        uint32_t rmask, gmask, bmask, amask;
        makemask(rmask, gmask, bmask, amask);
        SDL_Surface * surface = SDL_CreateRGBSurfaceFrom(pixels, w, h, bpp * 8, w * bpp, rmask, gmask, bmask, amask);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    void makemask(uint32_t & r, uint32_t & g, uint32_t & b, uint32_t & a) {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        r = 0xff000000;
        g = 0x00ff0000;
        b = 0x0000ff00;
        a = 0x000000ff;
#else
        r = 0x000000ff;
        g = 0x0000ff00;
        b = 0x00ff0000;
        a = 0xff000000;
#endif
    }


}





