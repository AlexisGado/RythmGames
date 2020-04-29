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
    double y;

    int w;
    int h;

    AlphaColor col;

};


class Stack2
{
    int w=800,h=600;
    Window Wmain;

    int cbloci = w/3;
    double v = 0.3;
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
