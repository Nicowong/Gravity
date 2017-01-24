#include "Particle.h"

Vector add(Vector a, Vector b){
    Vector c ;
    c.x = a.x - b.x ;
    c.y = a.y - b.y ;
    return c ;
}
void printState(int i, Particle p[NBPARTICLE]){
    fprintf(file, "P%d : w=%1.2e    x=%1.2e  y=%1.2e     vx=%1.2e    vy=%1.2e    ax=%1.2e    ay=%1.2e\n", i, p[i].weight, p[i].pos.x, p[i].pos.y, p[i].spe.x, p[i].spe.y, p[i].acc.x, p[i].acc.y);
}

double randDouble(double a, double b){
    return (double)rand()/(double)RAND_MAX * (b-a)+a;
}

void initParticle(Particle *p, double weight, double x, double y, double vx , double vy){
    p->flag = 1 ;
    p->weight = weight ;
    p->rad = pow(4.0/3.0/PI*weight/DENSITY,1.0/3.0);
    p->pos.x = x ;
    p->pos.y = y ;
    p->spe.x = vx ;
    p->spe.y = vy ;
    p->acc.x = 0 ;
    p->acc.y = 0 ;
}

double totalWeight(Particle particles[NBPARTICLE]){
    double w = 0 ;
    int i ;
    for(i=0 ; i<NBPARTICLE ; i++)
        if(particles[i].flag==1)
            w += particles[i].weight ;
    return w ;
}

double dist(const Vector a, const Vector b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

Vector accel(const Particle *a, const Particle *b){
    Vector res ;
    double d = dist(a->pos, b->pos);
    res.x = GRAVICONST*b->weight*(b->pos.x-a->pos.x)/d/d/d ;
    res.y = GRAVICONST*b->weight*(b->pos.y-a->pos.y)/d/d/d ;
    return res ;
}

void acceleration(Particle particles[NBPARTICLE]){
    int i,j;
    Vector c ;
    for(i = 0 ; i<NBPARTICLE ; i++){
        if(particles[i].flag==0)
            continue ;
        particles[i].acc.x = 0 ;
        particles[i].acc.y = 0 ;
        for(j=0 ; j<NBPARTICLE ; j++){
            if(i==j || particles[j].flag==0)
                continue ;
            c = accel(&particles[i], &particles[j]);
            particles[i].acc.x += c.x ;
            particles[i].acc.y += c.y ;
        }
    }
}

void position(Particle particles[NBPARTICLE]){
    int i;
    gCentre.x = 0;
    gCentre.y = 0;
    for(i=0 ; i< NBPARTICLE ; i++){
        if(particles[i].flag==0)
            continue ;
        particles[i].pos.x += (particles[i].acc.x*tdiv/2+particles[i].spe.x)*tdiv ;
        particles[i].pos.y += (particles[i].acc.y*tdiv/2+particles[i].spe.y)*tdiv ;
        gCentre.x += particles[i].weight*particles[i].pos.x ;
        gCentre.y += particles[i].weight*particles[i].pos.y ;
    }
    sWeight = totalWeight(particles);
    gCentre.x /= sWeight ;
    gCentre.y /= sWeight ;
}

void vitesse(Particle particles[NBPARTICLE]){
    int i;
    for(i=0 ; i<NBPARTICLE ; i++){
        if(particles[i].flag==0)
            continue ;
        particles[i].spe.x += particles[i].acc.x*tdiv ;
        particles[i].spe.y += particles[i].acc.y*tdiv ;
    }
}

void show(SDL_Surface *screen, Particle p[NBPARTICLE]){
    int i ;
    for(i=0 ; i<NBPARTICLE ; i++){
        if(p[i].flag==0){
            //sSetPixel(screen, (int)(p[i].pos.x), (int)(p[i].pos.y), BLUE);
            sSetPixel(screen, (int)((p[i].pos.x-shift.x)*zoom), (int)((p[i].pos.y-shift.y)*zoom), BLUE);
            continue ;
        }
        //drawDisk(screen, (int)(p[i].pos.x), (int)(p[i].pos.y), p[i].rad, RED);
        if(p[i].rad*zoom < 1)
            drawCircle(screen, (int)((p[i].pos.x-shift.x)*zoom), (int)((p[i].pos.y-shift.y)*zoom), 6, GREEN);
        else
            drawDisk(screen, (int)((p[i].pos.x-shift.x)*zoom), (int)((p[i].pos.y-shift.y)*zoom), p[i].rad*zoom, RED);
    }
    //sSetPixel(screen, (int)gCentre.x, (int)gCentre.y, SDL_MapRGB(screen->format,255,255,255));
    sSetPixel(screen, (int)((gCentre.x-shift.x)*zoom), (int)((gCentre.y-shift.y)*zoom), SDL_MapRGB(screen->format,255,255,255));//GCENTER
}

void collision(Particle p[NBPARTICLE]){ //SFML
    int i,j;
    for(i=0 ; i<NBPARTICLE ; i++){
        if(p[i].flag == 1)
            for(j=0 ; j<NBPARTICLE ; j++)
                if(p[j].flag == 1 && i!=j)
                    if(dist(p[i].pos,p[j].pos) < p[i].rad+p[j].rad){//collision
                        p[j].flag = 0 ;
                        p[i].pos.x = (p[i].pos.x*p[i].weight + p[j].pos.x*p[j].weight)/(p[i].weight+p[j].weight);
                        p[i].pos.y = (p[i].pos.y*p[i].weight + p[j].pos.y*p[j].weight)/(p[i].weight+p[j].weight);
                        p[i].spe.x = (p[i].spe.x*p[i].weight + p[j].spe.x*p[j].weight)/(p[i].weight+p[j].weight);
                        p[i].spe.y = (p[i].spe.y*p[i].weight + p[j].spe.y*p[j].weight)/(p[i].weight+p[j].weight);
                        p[i].weight += p[j].weight ;
                        p[i].rad = pow(4.0/3.0/PI*p[i].weight/DENSITY,1.0/3.0);
                    }
    }
}
