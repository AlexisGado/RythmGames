#include "piano_tiles_course.h"

void PianoTiles::init(){

    setActiveWindow(Wmain);

    score = 0; // score du joueur
    temps_debut = 0; // donne l'heure en secondes
    temps_actuel = 0;
    cout<<"Vous jouez a Piano Tiles, version course."<<endl;

    clearWindow();
    // on initialise le tableau :
    int pos=0;
    for (int j=3; j>0; j--){ // pour les 3 lignes du milieu-bas
        pos=Random(0, 4); // position de la case noire
        for (int i=0; i<4; i++){
            if (i==pos){
                u[i][j]={i*wbloc, h-(5-j)*hbloc};
                t[i][j]=BLACK;
                fillRect(u[i][j].x+w_m, u[i][j].y+h_mh, wbloc, hbloc, t[i][j]);
            }
            else{
                u[i][j]={i*wbloc, h-(5-j)*hbloc};
                t[i][j]=WHITE;
                fillRect(u[i][j].x+w_m, u[i][j].y+h_mh, wbloc, hbloc, WHITE);
                drawRect(u[i][j].x+w_m, u[i][j].y+h_mh, wbloc, hbloc, BLACK);
            }
        }
    }
    //pour la ligne tout en bas (ne joue pas au début):
    for (int i=0; i<4; i++){
        u[i][4]={i*wbloc, h-(5-4)*hbloc};
        t[i][4]=YELLOW;
        fillRect(u[i][4].x+w_m, u[i][4].y+h_mh, wbloc, hbloc, YELLOW);
        drawRect(u[i][4].x+w_m, u[i][4].y+h_mh, wbloc, hbloc, BLACK);
    }
    // pour la ligne tout en haut (la surface à colorier est plus petite) :
    pos=Random(0, 4);
    for (int i=0; i<4; i++){
        if (i==pos){
            u[i][0]={i*wbloc, h-5*hbloc};
            t[i][0]=BLACK;
            fillRect(u[i][0].x+w_m, 0+h_mh, wbloc, h-4*hbloc, t[i][0]);
        }
        else{
            u[i][0]={i*wbloc, h-5*hbloc};
            t[i][0]=WHITE;
            fillRect(u[i][0].x+w_m, 0+h_mh, wbloc, h-4*hbloc, WHITE);
            drawRect(u[i][0].x+w_m, 0+h_mh, wbloc, h-4*hbloc, BLACK);
        }
    }

    drawString(30, 30,"Cliquer sur espace pour commencer",c_texte,15,0,false,true);
    drawString(30, 50,"Puis jouer avec les touches D, F, J et K.",c_texte,10,0,false,true);
}



void PianoTiles::colorie(){
    //objectif : colorier la grille à un instant donné
    //clearWindow(); // pas nécessaire si on recolorie toutes les cases à chaque fois
    for (int i=0; i<4; i++){
        //si on est en haut de la fenetre :
        fillRect(u[i][0].x+w_m, 0+h_mh, wbloc, h-4*hbloc, t[i][0]); // avant : hbloc+t[i][0].y avec t[i][0].y<0
        drawRect(u[i][0].x+w_m, 0+h_mh, wbloc, h-4*hbloc, BLACK);
        for (int j=1; j<4; j++){ //au milieu de la fenêtre :
            fillRect(u[i][j].x+w_m, h-(5-j)*hbloc+h_mh, wbloc, hbloc, t[i][j]); // h-(5-j)*hbloc à la place de t[i][j]
            drawRect(u[i][j].x+w_m, h-(5-j)*hbloc+h_mh, wbloc, hbloc, BLACK);
        }
        //si on est en bas de la fenetre :
        fillRect(u[i][4].x+w_m, u[i][4].y+h_mh, wbloc, hbloc, t[i][4]);// ou, à la place de hbloc, h-t[i][4].y
        drawRect(u[i][4].x+w_m, u[i][4].y+h_mh, wbloc, hbloc, BLACK);
    }

}




void PianoTiles::avance(){
    //fait avancer d'une unité tous les blocs
    //il faut faire apparaitre un bloc en haut, disparaitre un bloc en bas, et décaller tout le tableau vers le bas
    int pos=Random(0, 4); // nb entier aléatoire entre 0 et 3, position de la future case noire
    for (int i=0; i<4; i++){ //pour chaque colonne :
        for (int j=4; j>0; j--){
            // ici, faut-il actualiser u ?
            t[i][j]=t[i][j-1];
        }
        // pour la nouvelle ligne :
        // idem pour u ici ?
        if (score<57){
            if (pos==i){
                t[i][0]=BLACK;
            }
            else {
                t[i][0]=WHITE;
            }
        }
        else {
            t[i][0]=YELLOW;
        }
    }
}

bool PianoTiles::bougeBloc(){
    // fait jouer une itération, retourne false si le joueur a perdu
    // la ligne sur laquelle il va falloir cliquer est la ligne 3
    int pos=0;
    for (int i=0; i<4; i++){
        if (t[i][3]==BLACK){
            pos= i; // position du bloc sur lequel il va falloir cliquer, entre 0 et 3
            break;
        }
    }

    Event e;
    getEvent(10,e);
    //on récupère la commande de l'utilisateur

    if (e.type == EVT_KEY_ON && e.key != cases[pos]){ //si l'utilisateur clique sur la mauvaise touche
        for (int i=0; i<4; i++){
            if (cases[i]==e.key){
                fillRect(u[i][3].x+w_m, u[i][3].y+h_mh, wbloc, hbloc, RED);
                drawRect(u[i][3].x+w_m, u[i][3].y+h_mh, wbloc, hbloc, BLACK);
            }
        }
        cout << "Vous avez clique sur la mauvaise touche !"<<endl;
        return false;
    }

    if (e.type == EVT_KEY_ON && e.key == cases[pos]) //si l'utilisateur a cliqué sur la bonne case
    {
        //ici il faut augmenter le score et passer à la case suivante
        score++;
        t[pos][3]=Color(0, 179, 0);
        avance(); // on avance le tableau
    }
    temps_actuel=std::time(nullptr)-temps_debut;
    colorie(); // on actualise l'affichage de la grille


    fillRect(220,0,w,h_mh,WHITE);
    drawString(220,60,to_string(temps_actuel),c_texte,30,0,false,true);

    if (score>=50){
        return false;
    }
    return true; // si on n'est pas tombé sur une erreur alors on continue à jouer
}

bool PianoTiles::play()
{
    bool ok=true;
    drawString(30,60,"Temps : ",c_texte,30,0,false,true);
    drawString(220,60,to_string(temps_actuel),c_texte,30,0,false,true);
    temps_debut = std::time(nullptr);
    while (ok)
    {
        if (!bougeBloc()) // donc si on a fini
        {
            if (score>=50){
                cout<<"Votre temps : "<<temps_actuel<<endl;
            }
            else {
                cout << "Vous avez perdu !"<<endl;
            }
            ok=false;
            cout<<"Votre score : "<<score<<endl;
        }

    }

    return ok;
}


void PianoTiles::jeuSolo()
{
    int touche;
    InitRandom();
    Wmain = openWindow(w+2*w_m,h+h_mh+h_mb);
    do{

    init();

    getKey(); // pour lancer le jeu

    fillRect(0,0,w+w_m,h_mh,WHITE);


    play();

    fillRect(0,0,w+2*w_m,h_mh,WHITE);
    if (score>=50){
        drawString(85, 280,"BRAVO !",c_texte,60,0,false,true);
        drawString(85,320,"Temps : ",c_texte,30,0,false,true);
        drawString(255,320,to_string(temps_actuel),c_texte,30,0,false,true);
        drawString(330,320,"sec",c_texte,30,0,false,true);
    }
    else {
        drawString(85, 280,"PERDU !",c_texte,60,0,false,true);
    }
    drawString(30, 40,"Cliquer sur entrer pour rejouer",c_texte,15,0,false,true);
    drawString(30, 70,"Cliquer ailleurs pour terminer",c_texte,15,0,false,true);

    touche=getKey();
    } while(touche==16777220);

    // pour fermer le jeu

    closeWindow(Wmain);

    endGraphics();

}
