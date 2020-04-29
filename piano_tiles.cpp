#include "piano_tiles.h"
#include "general.h"

void PianoTiles2::init(){
    InitRandom();
    Wmain = openWindow(w+2*w_m,h+h_mh+h_mb);
    setActiveWindow(Wmain);

    clearWindow();
    //on initialise le tableau :
    int pos=0;
    for (int j=4; j>0; j--){
        pos=Random(0, 4);
        for (int i=0; i<4; i++){
            if (i==pos){
                t[i][j]={i*wbloc, h-(5-j)*hbloc, BLACK};
                fillRect(t[i][j].x+w_m, t[i][j].y+h_mh, wbloc, hbloc, t[i][j].c);
            }
            else{
                t[i][j]={i*wbloc, h-(5-j)*hbloc, WHITE};
                fillRect(t[i][j].x+w_m, t[i][j].y+h_mh, wbloc, hbloc, WHITE);
                drawRect(t[i][j].x+w_m, t[i][j].y+h_mh, wbloc, hbloc, BLACK);
            }
        }
    }
    pos=Random(0, 4);
    for (int i=0; i<4; i++){
        if (i==pos){
            t[i][0]={i*wbloc, 0, BLACK};
            fillRect(t[i][0].x+w_m, t[i][0].y+h_mh, wbloc, h-4*hbloc, t[i][0].c);
        }
        else{
            t[i][0]={i*wbloc, 0, WHITE};
            fillRect(t[i][0].x+w_m, t[i][0].y+h_mh, wbloc, h-4*hbloc, WHITE);
            drawRect(t[i][0].x+w_m, t[i][0].y+h_mh, wbloc, h-4*hbloc, BLACK);
        }
    }

    drawString(30, 30,"Cliquez sur espace pour commencer",BLUE,15,0,false,true);
}

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

void PianoTiles2::colorie(){
    //objectif : colorier la grille à un instant donné
    //fonctionnement : on remet tout l'écran en blanc puis on colorie en fonction de qui est où
    //clearWindow(); // pas nécessaire si on recolorie toutes les cases à chaque fois
    for (int i=0; i<4; i++){
        for (int j=1; j<4; j++){ //au milieu de la fenêtre :
            if (t[i][j].c==BLACK || t[i][j].c==GREEN)
                fillRect(t[i][j].x+w_m, t[i][j].y+h_mh, wbloc, hbloc, t[i][j].c);
            else{
                fillRect(t[i][j].x+w_m, t[i][j].y+h_mh, wbloc, hbloc, WHITE);
                drawRect(t[i][j].x+w_m, t[i][j].y+h_mh, wbloc, hbloc, BLACK);
            }
        }
        //si on est en haut de la fenetre :
        if (t[i][0].c==BLACK || t[i][0].c==GREEN)
            fillRect(t[i][0].x+w_m, 0+h_mh, wbloc, hbloc+t[i][0].y, t[i][0].c);
        else{
            fillRect(t[i][0].x+w_m, 0+h_mh, wbloc, hbloc+t[i][0].y, WHITE);
            drawRect(t[i][0].x+w_m, 0+h_mh, wbloc, hbloc+t[i][0].y, BLACK);
        }
        //si on est en bas de la fenetre :
        if (t[i][4].c==BLACK || t[i][4].c==GREEN)
            fillRect(t[i][4].x+w_m, t[i][4].y+h_mh, wbloc, h-t[i][4].y, t[i][4].c);
        else{
            fillRect(t[i][4].x+w_m, t[i][4].y+h_mh, wbloc, h-t[i][4].y, WHITE);
            drawRect(t[i][4].x+w_m, t[i][4].y+h_mh, wbloc, h-t[i][4].y, BLACK);
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

bool PianoTiles2::avance(){
    //fait avancer d'une unité tous les blocs
    // retourne false si la touche est sortie de l'écran alors qu'on n'a pas cliqué, true sinon
    if (t[0][0].y+v<=hbloc){ //aucun nouveau bloc ne va apparaitre en haut ni disparaitre en bas
        for (int i=0; i<4; i++){
            for (int j=1; j<5; j++){
                t[i][j].y+=v;
            }
        }
    }
    else { //il faut faire apparaitre un bloc en haut, disparaitre un bloc en bas, et décaller tout le tableau
        if (ligne==5){ //si la case qui va disparaitre est noire, càd que le joueur a perdu
            return false;
        }
        int pos=Random(0, 4); // nb entier aléatoire entre 0 et 3, position de la future case noire
        ligne++;
        for (int i=0; i<4; i++){
            for (int j=4; j>0; j--){
                t[i][j].x=t[i][j-1].x+v;
                t[i][j].y=t[i][j-1].y+v;
                t[i][j].c=t[i][j-1].c;
            }
            // pour j=0 :
            if (pos==i){
                t[i][0]={i*wbloc, 0, BLACK};
            }
            else {
                t[i][0]={i*wbloc, 0, WHITE};
            }
        }


    }
    return true;
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

bool PianoTiles2::bougeBloc(){
    //fait jouer une itération, retourne false si le joueur a perdu
    point bloc;
    int pos=0;
    for (int i=0; i<4; i++){
        if (t[i][ligne].c==BLACK){
            pos= i; //position du bloc sur lequel il va falloir cliquer, entre 0 et 3
            break;
        }
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
        t[pos][ligne].c=GREEN;
        ligne++;

    }

    bool pas_perdu=avance();
    if (!pas_perdu) // càd si on a perdu (car la touche est sortie de l'écran alors qu'on n'a pas cliqué)
        return false;

    colorie();

    if (100*v<score){ // plus le score est grand plus on augmente la vitesse
        v+=0.001;
    }

    milliSleep(1);
    return true;
}

bool PianoTiles2::play()
{
    bool ok=true;
    while (ok)
    {

        if (!bougeBloc()) // donc si on a perdu la partie
        {
            cout<<"Perdu!"<<endl;
            cout<<"Score : "<<score<<endl;
            ok=false;
        }

    }

    return ok;
}


void PianoTiles2::jeuSolo()
{
    init();

    getKey();

    fillRect(0,0,w+w_m,h_mh,WHITE);


    play();

    drawString(30, 20,"PERDU !",BLUE,30,0,false,true);
    drawString(30, 60,"Cliquez sur espace pour terminer",BLUE,15,0,false,true);

    getKey();

    closeWindow(Wmain);

    endGraphics();

}
