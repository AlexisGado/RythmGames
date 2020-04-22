#pragma once
#include "general.h"

const int wbloc=wfen/4, hbloc=hfen/4; //4 cases latérales, 4 cases en hauteur
const char cases[4]={'D', 'F', 'J', 'K'};

struct point {
    int x,y; //coordonées
    Imagine::Color c;
};

void colorie(list<point> pile, int h);
void avance(list<point>&pile, int v, int h);
bool bougeBloc(list<point>& pile,int v, int h, int& score);
