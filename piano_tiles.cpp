#include "piano_tiles.h"
#include "general.h"

void PianoTiles2::init(){
    InitRandom();
    Wmain = openWindow(w+2*w_m,h+h_mh+h_mb);
    setActiveWindow(Wmain);

    clearWindow();
    //on initialise le tableau :
    int pos=0;
    for (int j=4; j>0; j--){ //pour les 4 cases du bas
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
    // pour la case en haut :
    pos=Random(0, 4);
    for (int i=0; i<4; i++){
        if (i==pos){
            t[i][0]={i*wbloc, h-5*hbloc, BLACK};
            fillRect(t[i][0].x+w_m, 0+h_mh, wbloc, h-4*hbloc, t[i][0].c);
        }
        else{
            t[i][0]={i*wbloc, h-5*hbloc, WHITE};
            fillRect(t[i][0].x+w_m, 0+h_mh, wbloc, h-4*hbloc, WHITE);
            drawRect(t[i][0].x+w_m, 0+h_mh, wbloc, h-4*hbloc, BLACK);
        }
    }

    drawString(30, 30,"Cliquer sur espace pour commencer",c_texte,15,0,false,true);
    drawString(30, 50,"Puis jouer avec les touches D, F, J et K.",c_texte,10,0,false,true);
}



void PianoTiles2::colorie(){
    //objectif : colorier la grille à un instant donné
    //fonctionnement : on remet tout l'écran en blanc puis on colorie en fonction de qui est où
    //clearWindow(); // pas nécessaire si on recolorie toutes les cases à chaque fois
    for (int i=0; i<4; i++){
        for (int j=1; j<4; j++){ //au milieu de la fenêtre :
            fillRect(t[i][j].x+w_m, t[i][j].y+h_mh, wbloc, hbloc, t[i][j].c);
            drawRect(t[i][j].x+w_m, t[i][j].y+h_mh, wbloc, hbloc, BLACK);
        }
        //si on est en haut de la fenetre :
        fillRect(t[i][0].x+w_m, 0+h_mh, wbloc, hbloc+t[i][0].y, t[i][0].c);
        drawRect(t[i][0].x+w_m, 0+h_mh, wbloc, hbloc+t[i][0].y, BLACK);
        //si on est en bas de la fenetre :
        fillRect(t[i][4].x+w_m, t[i][4].y+h_mh, wbloc, h-t[i][4].y, t[i][4].c);
        drawRect(t[i][4].x+w_m, t[i][4].y+h_mh, wbloc, h-t[i][4].y, BLACK);
    }

}




bool PianoTiles2::avance(){
    //fait avancer d'une unité tous les blocs
    // retourne false si la touche est sortie de l'écran alors qu'on n'a pas cliqué, true sinon
    if (t[0][0].y+v<=0){ //aucun nouveau bloc ne va apparaitre en haut ni disparaitre en bas
        for (int i=0; i<4; i++){
            for (int j=0; j<5; j++){
                t[i][j].y+=v;
            }
        }
    }
    else { //il faut faire apparaitre un bloc en haut, disparaitre un bloc en bas, et décaller tout le tableau
        if (ligne>=4){ //si la case qui va disparaitre est noire, càd que le joueur a perdu
            return false;
        }
        ligne++;
        int pos=Random(0, 4); // nb entier aléatoire entre 0 et 3, position de la future case noire
        for (int i=0; i<4; i++){
            for (int j=4; j>0; j--){
                t[i][j].y=t[i][j-1].y+v;
                t[i][j].c=t[i][j-1].c;
            }
            // pour la nouvelle ligne :
            t[i][0].x=i*wbloc;
            t[i][0].y=h-5*hbloc;
            if (pos==i){
                cout<<"Le nouveau bloc va apparaitre en colonne" << pos<<endl;
                t[i][0].c=BLACK;
            }
            else {
                cout<<"Le nouveau bloc ne va pas apparaitre en colonne" << pos<<endl;
                t[i][0].c=WHITE;
            }
        }


    }
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
    getEvent(10,e);
    //on récupère la commande de l'utilisateur

    if (e.type == EVT_KEY_ON && e.key != cases[pos]){ //si l'utilisateur clique sur la mauvaise touche
        cout << "Vous avez appuye sur "<< e.key << " alors qu'il fallait appuyer sur " << cases[pos] << endl;
        return false;
    }

    if (e.type == EVT_KEY_ON && e.key == cases[pos]) //si l'utilisateur a cliqué sur la bonne case
    {
        //ici il faut augmenter le score et passer à la case suivante
        score++;
        t[pos][ligne].c=Color(0, 179, 0);
        ligne--;
        fillRect(180,0,w,h_mh,WHITE);
        drawString(180,60,to_string(score),c_texte,30,0,false,true);
    }

    bool pas_perdu=avance(); // vaut false si on a perdu (car la touche est sortie de l'écran alors qu'on n'a pas cliqué)
    if (pas_perdu==false){ // càd si on a perdu
        cout << "Vous n'avez pas tape a temps !" << endl;
        return false;
    }

    colorie();

    if (7*v<score){ // plus le score est grand plus on augmente la vitesse
        v+=1;
    }

    return true;
}

bool PianoTiles2::play()
{
    bool ok=true;
    drawString(30,60,"Score : ",c_texte,30,0,false,true);
    drawString(180,60,to_string(score),c_texte,30,0,false,true);
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

    drawString(85, 280,"PERDU !",c_texte,60,0,false,true);
    drawString(30, 80,"Cliquez sur espace pour terminer",c_texte,15,0,false,true);

    getKey();

    closeWindow(Wmain);

    endGraphics();

}
