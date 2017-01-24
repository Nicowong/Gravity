#ifndef SDL_LIB_H_INCLUDED
#define SDL_LIB_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>

#define SWIDTH  768
#define SHEIGHT 512

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void sSetPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
int Max(int a, int b);
int Min(int a, int b);
void drawCircle(SDL_Surface *surface, int x, int y, double rad, Uint32 pixel);
void drawDisk(SDL_Surface *surface, int x, int y, double rad, Uint32 pixel);

#endif // SDL_LIB_H_INCLUDED
