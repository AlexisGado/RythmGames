#pragma once
#include "general.h"

struct point_course {
    int x,y; //coordonées
};

class PianoTiles {
private:
    int w=300,h=400; // taille du tableau
    int w_m=100, h_mh=100, h_mb=10; // marges de la fenêtre qui va s'afficher
    int wbloc=w/4., hbloc=(h-5)/4.; //4 cases latérales, 5 cases en hauteur
    const int cases[4]={100, 102, 106, 107}; // cases[4]={'d', 'f', 'j', 'k'};
    Color c_texte=Color(0, 153, 153); // couleur du texte du jeu

    Window Wmain;

    point_course u[4][5]; // tableau contenant les positions des blocs : ne sera pas actualisé dans cette version
    Color t[4][5]; // tableau contenant les couleurs des blocs
    // Une case est blanche s'il n'y a rien dessus, noir s'il va falloir la taper ou vert si elle a déjà été tapée
    int score = 0; // score du joueur, entre 0 et 50
    int temps_debut = 0; // heure quand on commence à jouer
    int temps_actuel = 0; // durée de jeu

    void init();
    void colorie();
    void avance();
    bool bougeBloc();
    bool play();

public:
    void jeuSolo();

};
