#include "piano_tiles.h"
#include "general.h"



void colorie(list<point> pile){
    //on remet tout l'écran en blanc puis on colorie en fonction de qui est où
    clearWindow();
    while(!pile.empty()){
        point bloc=pile.back();
        pile.pop_back();
        fillRect(bloc.x, bloc.y, wbloc, hbloc, bloc.c);
    }
}

list<point> avance(list<point> pile, int v, int h){
    //fait avancer d'une unité tous les blocs
    list<point> pile_annexe;
    while(!pile.empty()){
        //on modifie toutes les vitesses
        point bloc=pile.back();
        pile.pop_back();
        if (bloc.y+v<h){
            bloc.y+=v;
            pile_annexe.push_front(bloc);
        }
    }
    while(!pile_annexe.empty()){
        point bloc=pile_annexe.back();
        pile_annexe.pop_back();
        pile.push_front(bloc);
    }
    //on regarde s'il faut ajouter un bloc :
}

bool bougeBloc(list<point>& pile,int v, int h, int& score)
{
    //pile est la liste des blocs, v la vitesse des blocs, h la hauteur de la fenêtre, score le score actuel du joueur
    point bloc = pile.front(); //le bloc sur lequel il faut cliquer
    int pos= bloc.x/wbloc;//position de ce bloc, entre 0 et 3

    if (bloc.y+hbloc > h) //si la touche est sortie de l'écran alors qu'on n'a pas cliqué
    {
        return false;
    }


    Event e;
    getEvent(0,e);
    //on récupère la commande de l'utilisateur

    if (e.type == EVT_KEY_ON && e.key != cases[pos]){ //si l'utilisateur clique sur la mauvaise touche
        return false;
    }

    if (e.type == EVT_KEY_ON && e.key == cases[pos]) //si l'utilisateur a cliqué sur la bonne case
    {
        //ici il faut augmenter le score et passer à la case suivante
        score++;
        bloc.c=GREEN;
        pile.pop_front();
        pile.push_front(bloc);

    }


    int k=pile.size();

    for (int j=0; j<k; j++){

    }
    bloc.y+=v; //on fait avancer

    colorie(pile);

    return true;
}
