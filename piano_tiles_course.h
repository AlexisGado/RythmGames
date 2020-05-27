#pragma once
#include "general.h"
#include <math.h>

struct point_course {
    int x,y; //coordonées
};

class PianoTiles {
private:
    int w=300,h=400; // taille du tableau
    int w_m=100, h_mh=100, h_mb=10; // marges de la fenêtre qui va s'afficher
    int wbloc=w/4., hbloc=(h-5)/4.; //4 cases latérales, 5 cases en hauteur
    //const char cases[4]={'d', 'f', 'j', 'k'};
    const int cases[4]={100, 102, 106, 107};
    Color c_texte=Color(0, 153, 153); // couleur du texte du jeu

    Window Wmain;

    point_course u[4][5];
    Color t[4][5]; // tableau contenant les positions et couleurs des blocs

    // Une case est blanche s'il n'y a rien dessus, noir s'il va falloir la taper ou vert si elle a déjà été tapée
    int score = 0; // score du joueur
    int temps_debut = 0;
    int temps_actuel = 0;

    void init();
    void colorie();
    void avance();
    bool bougeBloc();
    bool play();

public:
    void jeuSolo();

};
