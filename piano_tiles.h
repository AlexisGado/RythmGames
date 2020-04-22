#pragma once
#include "general.h"

struct point {
    int x,y; //coordonées
    Imagine::Color c;
};

//void colorie(list<point> pile, int h);
//void avance(list<point>&pile, int v, int h);
//bool bougeBloc(list<point>& pile,int v, int h, int& score);

class PianoTiles {
private:
    int w=800,h=600;
    int wbloc=w/4, hbloc=h/4; //4 cases latérales, 4 cases en hauteur
    const char cases[4]={'D', 'F', 'J', 'K'};

    Window Wmain;

    double v = 0.005;
    list<point> pile; // positions et couleurs des blocs
    int score = 0;

    void colorie(list<point> pileCopie);
    void avance();
    bool bougeBloc();

public:
    //void jeuSolo();

};
