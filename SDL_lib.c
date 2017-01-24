#include "SDL_lib.h"

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel){
    int bpp = surface->format->BytesPerPixel;

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void sSetPixel(SDL_Surface *surface, int x, int y, Uint32 pixel){
    if(0<=x && x<surface->w && 0<=y && y<surface->h)
        setPixel(surface, x, y, pixel);
}

int Max(int a, int b){
    if(a>b)
        return a;
    return b ;
}
int Min(int a, int b){
    if(a>b)
        return b ;
    return a ;
}
void drawCircle(SDL_Surface *surface, int x, int y, double rad, Uint32 pixel){
    int i, j;
    int R = (int)rad ;
    for(i=Max(x-R,0) ; i<Min(x+R+1,surface->w) ; i++)
        for(j=Max(y-R,0) ; j<Min(y+R+1,surface->h) ; j++)
            if((int)sqrt((i-x)*(i-x)+(j-y)*(j-y)) == (int)rad)
                setPixel(surface, i, j, pixel) ;
}

void drawDisk(SDL_Surface *surface, int x, int y, double rad, Uint32 pixel){
    int i, j;
    int R = (int)rad ;
    for(i=Max(x-R,0) ; i<Min(x+R+1,surface->w) ; i++)
        for(j=Max(y-R,0) ; j<Min(y+R+1,surface->h) ; j++)
            if(sqrt((i-x)*(i-x)+(j-y)*(j-y)) < rad)
                setPixel(surface, i, j, pixel) ;
}
