#ifndef SPRITE_SPRITE_H
#define SPRITE_SPRITE_H

struct SDL_Texture;
struct SDL_Renderer;

namespace ex {
    class sprite {
        public:
            sprite(sprite && other);
            sprite(const sprite & other);
            sprite(SDL_Renderer * renderer, const char file[], int framesx, int framesy);
            sprite(SDL_Renderer * renderer, const unsigned char data[], unsigned int len, int framesx, int framesy);
            ~sprite();
            void render(int framex, int framey, int x, int y, double angle = 0.0f);
            void render(int x, int y, double angle = 0.0f);

        private:
            void make(unsigned char * pixels, int bpp);
            SDL_Texture * texture;
            SDL_Renderer * renderer;
            int w, h;
            int framesx, framesy;
    };
}

#endif //SPRITE_SPRITE_H
