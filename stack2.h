#pragma once
#include "general.h"

#include <iostream>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;

#include <cstdlib>
#include <ctime>
using namespace std ;



struct Bloc
{
    double x;
    double y; //position du bloc

    int w;
    int h; //taille du bloc

    Color col;

};


class Stack2
{
    int w=800,h=600;
    Window Wmain;

    int cbloci = w/3; // taille du bloc initial
    double v = 0.6; //vitesse (norme)
    int vx = 1;
    int vy = 0;

    int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};


    int score = 0;

    Bloc fixe;
    Bloc mobile;

    void init();
    void affiche();
    Bloc genBloc();
    Bloc calcColl();
    bool bougeBloc();

    bool play();

public:

    void jeuSolo();

};
