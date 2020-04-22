#include "piano_tiles.h"
#include "general.h"



void PianoTiles::colorie(list<point> pile){
    //objectif : colorier la grille à un instant donné
    //fonctionnement : on remet tout l'écran en blanc puis on colorie en fonction de qui est où
    clearWindow();
    while(!pile.empty()){
        point bloc=pile.back();
        pile.pop_back();
        if (bloc.y>0 && bloc.y+hbloc<h){
            fillRect(bloc.x, bloc.y, wbloc, hbloc, bloc.c);
        }
        else if (bloc.y<0){ //si on est en haut de la fenetre
            fillRect(bloc.x, 0, wbloc, hbloc+bloc.y, bloc.c);
        }
        else if (bloc.y+hbloc>h){ //si on est en bas de la fenetre
            fillRect(bloc.x, bloc.y, wbloc, h-bloc.y, bloc.c);
        }
    }
}

void PianoTiles::avance(){
    //fait avancer d'une unité tous les blocs
    list<point> pile_annexe;
    point bloc;
    while(!pile.empty()){
        //on modifie toutes les vitesses
        bloc=pile.back();
        pile.pop_back();
        if (bloc.y+v<=h){ //si la case ne sort pas du cadre, on l'ajoute
            bloc.y+=v;
            pile_annexe.push_front(bloc);
        }
    }
    while(!pile_annexe.empty()){
        point bloc=pile_annexe.back();
        pile_annexe.pop_back();
        pile.push_front(bloc);
    }
    //on regarde s'il faut ajouter un bloc tout en haut :
    bloc=pile.back();
    if (bloc.y>0){
        int pos=Random(0, 4); // /!\ ATTENTION /!\ à vérifier, peut être que c'est entre 0 et 3
        point nouveau_bloc;
        nouveau_bloc.y=-hbloc;
        nouveau_bloc.x=pos*wbloc;
        nouveau_bloc.c=BLACK;
        pile.push_back(nouveau_bloc);
    }

}

bool PianoTiles::bougeBloc()
{
    //pile est la liste des blocs, v la vitesse des blocs, h la hauteur de la fenêtre, score le score actuel du joueur
    point bloc = pile.front(); //le bloc sur lequel il faut cliquer
    int pos= bloc.x/wbloc;//position de ce bloc, entre 0 et 3

    if (bloc.y>=h) //si la touche est sortie de l'écran alors qu'on n'a pas cliqué
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

    avance();

    list<point> pileCopie=pile;
    colorie(pileCopie);

    return true;
}
