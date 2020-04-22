#pragma once
#include "general.h"

#include <iostream>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;

#include <cstdlib>
#include <ctime>
using namespace std ;

#include <list>
#include <tuple>



using lis = list<pair<int,double>>;
using couple = pair<int,double>;


class Stack
{
    int w=800,h=600;
    Window Wmain;

    int hsol = h/4;
    int hbloc = h/20;
    int wbloci = w/3;
    double v = 0.005;
    lis pile; // tailles et positions des bloc
    int score = 0;

    void init();
    void afficheTout(lis pileCopie);
    couple genBloc(int wbloc);
    int calcTaille(couple mouv,couple fixe);
    bool bougeBloc();

    bool play();

public:

    void jeuSolo();




};
