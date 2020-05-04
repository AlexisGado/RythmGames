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



struct Bloc1
{
    double x;
    int size;

    Color col;
};



using lis = list<Bloc1>;


class Stack
{
    int w=800,h=600;
    Window Wmain;

    int hsol = h/4;
    int hbloc = h/20;
    int wbloci = w/3;
    double v = 0.3;
    lis pile; // tailles et positions des bloc
    int score = 0;

    void init();
    void afficheTout(lis pileCopie);
    Bloc1 genBloc(int wbloc);
    int calcTaille(Bloc1 mouv,Bloc1 fixe);
    bool bougeBloc();

    bool play();

public:

    void jeuSolo();

};
