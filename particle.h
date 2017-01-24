#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include <time.h>
#include "SDL_lib.h"

#define PI          3.14159265359
#define GRAVICONST  6.67234E-11
#define NBPARTICLE  500
#define tdiv        0.01         //s
#define spf         20        //ms
#define DENSITY     5E12
#define vINI        17

FILE *file;
Uint32 RED ;
Uint32 GREEN ;
Uint32 BLUE ;

typedef struct Vector{
    double x ;
    double y ;
}Vector;

Vector gCentre;
double sWeight;
Vector shift ;
double zoom;

Vector add(Vector a, Vector b);

typedef struct Particle{
    char flag ;
    double weight ;
    double rad ;
    Vector pos ;
    Vector spe ;
    Vector acc ;
}Particle;

void printState(int i, Particle particles[NBPARTICLE]);
double randDouble(double a, double b);
void initParticle(Particle *p, double weight, double x, double y, double vx , double vy);
double totalWeight(Particle particles[NBPARTICLE]);
double dist(const Vector a, const Vector b);
Vector accel(const Particle *a, const Particle *b);
void acceleration(Particle particles[NBPARTICLE]);
void position(Particle particles[NBPARTICLE]);
void vitesse(Particle particles[NBPARTICLE]);

void collision(Particle particles[NBPARTICLE]);

void show(SDL_Surface *screen, Particle particles[NBPARTICLE]);

#endif // PARTICLE_H_INCLUDED
