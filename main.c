#include <stdlib.h>
#include <SDL/SDL.h>
#include "Particle.h"


int main ( int argc, char** argv ){
    srand(time(NULL));
    //file = fopen("log.txt","w");
    Particle particles[NBPARTICLE];
    int i ;

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);
    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(SWIDTH, SHEIGHT, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen ){
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }

    RED = SDL_MapRGB(screen->format, 255,0,0);
    GREEN = SDL_MapRGB(screen->format, 0, 255, 0);
    BLUE = SDL_MapRGB(screen->format, 0,0,255);
    shift.x = -SWIDTH/2 ;
    shift.y = -SHEIGHT/2 ;
    zoom = 1 ;
    double wWidth = SWIDTH ;
    double wHeight = SHEIGHT ;
    char slide = 0;

    for(i=0 ; i<NBPARTICLE ; i++){
        initParticle(&particles[i], randDouble(1E12,1E13) , randDouble(-SWIDTH,SWIDTH), randDouble(-SHEIGHT,SHEIGHT), randDouble(-vINI,vINI), randDouble(-vINI,vINI));
        //fprintf(file, "INIT : ");
        //printState(i, particles);
    }
    initParticle(&particles[0], 2E15, 200, 0, 1, vINI);
    initParticle(&particles[1], 2E15, -200, 0, 1, -vINI);
    //fprintf(file,"\n");
    sWeight = totalWeight(particles);

    char loop = 0xFF ;
    while (loop){
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            // check for messages
            switch (event.type){
                // exit if the window is closed
            case SDL_QUIT:
                loop = !loop;
                break;
                // check for keypresses
            case SDL_KEYDOWN:
                    // exit if ESCAPE is pressed
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    loop = !loop;
                else if(event.key.keysym.sym == SDLK_RIGHT)
                    slide = slide|0b00000001 ;
                else if(event.key.keysym.sym == SDLK_UP)
                    slide = slide|0b00000010 ;
                else if(event.key.keysym.sym == SDLK_LEFT)
                    slide = slide|0b00000100 ;
                else if(event.key.keysym.sym == SDLK_DOWN)
                    slide = slide|0b00001000 ;
                else if(event.key.keysym.sym == SDLK_q){//zoom
                    zoom *=1.5 ;
                    shift.x += wWidth/8 ;
                    shift.y += wHeight/8 ;
                }else if(event.key.keysym.sym == SDLK_w){//dezoom
                    zoom /=1.5 ;
                    shift.x -= wWidth/6 ;
                    shift.y -= wHeight/6 ;
                }
                break;
            case SDL_KEYUP :
                if(event.key.keysym.sym == SDLK_RIGHT)
                    slide = slide & 0b11111110 ;
                else if(event.key.keysym.sym == SDLK_UP)
                    slide = slide & 0b11111101 ;
                else if(event.key.keysym.sym == SDLK_LEFT)
                    slide = slide & 0b11111011 ;
                else if(event.key.keysym.sym == SDLK_DOWN)
                    slide = slide & 0b11110111 ;
                break ;
             }// end switch
        } // end of message processing

        if(slide&0b00000001)
            shift.x += 1/zoom ;
        if(slide&0b00000010)
            shift.y -= 1/zoom ;
        if(slide&0b00000100)
            shift.x -= 1/zoom ;
        if(slide&0B00001000)
            shift.y += 1/zoom ;

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

        // draw bitmap
        SDL_LockSurface(screen);
        show(screen, particles);
        SDL_UnlockSurface(screen);

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);

        /*for(i=0 ; i<NBPARTICLE ; i++){
            fprintf(file,"MAIN : ");
            printState(i, particles);
        }
        fprintf(file,"\n");*/

        acceleration(particles);
        position(particles);
        vitesse(particles);
        collision(particles);

        //SDL_Delay(spf);

    } // end main loop

    // free loaded bitmap

    // all is well ;)
    fclose(file);
    printf("Exited cleanly\n");
    return 0;
}
