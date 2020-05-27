#include "general.h"

void InitRandom()
{
    srand((unsigned int)time(0));
}

int Random(int a, int b) //randrange(a,b)
{
    return int(a + (b-a)*double(rand())/RAND_MAX);
}

int AffichageMenu(){ // retourne 1 si l'utilisateur veut jouer à Stack, 2 s'il veut jouer à Piano Tiles
    Window win = openWindow(800,400,"Menu");
    Event ev;

    //Displaying menu's buttons
    IntPoint2 P1(250,150), P2(250,250);
    int w=300, h=50;
    IntPoint2 Q1(P1.x()+w/3+25,P1.y()+h*3/5);
    IntPoint2 Q2(P2.x()+w/3,P2.y()+h*3/5);
    fillRect(P1,w,h,Color(45, 89, 134));
    drawString(Q1,"STACK",WHITE);
    fillRect(P2,w,h,Color(45, 89, 134));
    drawString(Q2,"PIANO TILES", WHITE);
    drawString(250, 110,"MENU", Color(32, 64, 96), 20);
    bool b = false;
    int k=0;

    // receiving mouse move events even if no button is pressed
    enableMouseTracking(true);
    do {
        getEvent(-1,ev); // ev becomes the next event
        switch (ev.type) {
        case EVT_NONE:
            cout << "No event" << endl;
            break;
        case EVT_MOTION: {
            int x = ev.pix.x();   // cursor's x coord
            int y = ev.pix.y();   // cursor's y coord
            // Cursor is in the "STACK" box.
            if(P1.x()<=x && x<P1.x()+w && P1.y()<=y && y<P1.y()+h) {
                // Changing the box's style
                fillRect(P1,w,h,Color(132, 225, 225));
                drawString(Q1,"STACK",Color(20, 82, 82));
            } else if(P2.x()<=x && x<P2.x()+w && P2.y()<=y && y<P2.y()+h) {
                // Cursor is in the "PIANO TILES" box.
                // Changing the box's style
                fillRect(P2,w,h,Color(132, 225, 225));
                drawString(Q2,"PIANO TILES", Color(20, 82, 82));
            } else {
                fillRect(P1,w,h,Color(45, 89, 134));
                drawString(Q1,"STACK",WHITE);
                fillRect(P2,w,h,Color(45, 89, 134));
                drawString(Q2,"PIANO TILES", WHITE);
            }
            break;
        }
        case EVT_KEY_ON:
            cout << "Use your mouse!"<< endl;
            break;
        case EVT_BUT_ON: {
            int x = ev.pix.x();   // cursor's x coord
            int y = ev.pix.y();   // cursor's y coord
            // Click on the SLACK box
            if(P1.x()<=x && x<P1.x()+w && P1.y()<=y && y<P1.y()+h) {
                k=1;
                b = true;         // Stop the menu's loop
            }
            else if(P2.x()<=x && x<P2.x()+w && P2.y()<=y && y<P2.y()+h) {
                k=2;
                b = true;         // Stop the menu's loop
            }
            break;
       }
        default: break;
        }
    } while ((ev.type!=EVT_KEY_ON || ev.key!='q' )&& !b);
    closeWindow(win);
    return k;
}

int MenuStack(){ //vaut 1 si on veut jouer en 1D, 2 si on veut jouer en 2D
    Window win = openWindow(800,400,"Menu Stack");
    Event ev;

    //Displaying menu's buttons
    IntPoint2 P1(250,150), P2(250,250);
    int w=300, h=50;
    IntPoint2 Q1(P1.x()+w/3,P1.y()+h*3/5);
    IntPoint2 Q2(P2.x()+w/3,P2.y()+h*3/5);
    fillRect(P1,w,h,Color(179, 45, 0));
    drawString(Q1,"VU  DE  PROFIL",WHITE);
    fillRect(P2,w,h,Color(179, 45, 0));
    drawString(Q2,"VU  DE  HAUT", WHITE);
    drawString(250, 110,"MENU STACK", Color(128, 32, 0), 20);
    bool b = false;
    int k=0;

    // receiving mouse move events even if no button is pressed
    enableMouseTracking(true);
    do {
        getEvent(-1,ev); // ev becomes the next event
        switch (ev.type) {
        case EVT_NONE:
            cout << "No event" << endl;
            break;
        case EVT_MOTION: {
            int x = ev.pix.x();   // cursor's x coord
            int y = ev.pix.y();   // cursor's y coord
            // Cursor is in the "VU DE PROFIL" box.
            if(P1.x()<=x && x<P1.x()+w && P1.y()<=y && y<P1.y()+h) {
                // Changing the box's style
                fillRect(P1,w,h,Color(223, 191, 159));
                drawString(Q1,"VU  DE  PROFIL",Color(191, 64, 64));
            } else if(P2.x()<=x && x<P2.x()+w && P2.y()<=y && y<P2.y()+h) {
                // Cursor is in the "VU DE HAUT" box.
                // Changing the box's style
                fillRect(P2,w,h,Color(223, 191, 159));
                drawString(Q2,"VU  DE  HAUT", Color(191, 64, 64));
            } else {
                fillRect(P1,w,h,Color(179, 45, 0));
                drawString(Q1,"VU  DE  PROFIL",WHITE);
                fillRect(P2,w,h,Color(179, 45, 0));
                drawString(Q2,"VU  DE  HAUT", WHITE);
            }
            break;
        }
        case EVT_KEY_ON:
            cout << "Use your mouse!"<< endl;
            break;
        case EVT_BUT_ON: {
            int x = ev.pix.x();   // cursor's x coord
            int y = ev.pix.y();   // cursor's y coord
            // Click on the SLACK box
            if(P1.x()<=x && x<P1.x()+w && P1.y()<=y && y<P1.y()+h) {
                k=1;
                b = true;         // Stop the menu's loop
            }
            else if(P2.x()<=x && x<P2.x()+w && P2.y()<=y && y<P2.y()+h) {
                k=2;
                b = true;         // Stop the menu's loop
            }
            break;
       }
        default: break;
        }
    } while ((ev.type!=EVT_KEY_ON || ev.key!='q' )&& !b);
    closeWindow(win);
    return k;
}

int MenuPiano(){ //vaut 1 si on veut jouer en mode arcade, 2 si on veut jouer en mode course
    Window win = openWindow(800,400,"Menu Piano Tiles");
    Event ev;

    //Displaying menu's buttons
    IntPoint2 P1(250,150), P2(250,250);
    int w=300, h=50;
    IntPoint2 Q1(P1.x()+w/3,P1.y()+h*3/5);
    IntPoint2 Q2(P2.x()+w/3,P2.y()+h*3/5);
    fillRect(P1,w,h,Color(134, 45, 89));
    drawString(Q1,"MODE ARCADE",WHITE);
    fillRect(P2,w,h,Color(134, 45, 89));
    drawString(Q2,"MODE COURSE", WHITE);
    drawString(250, 110,"MENU PIANO TILES", Color(96, 32, 64), 20);
    bool b = false;
    int k=0;

    // receiving mouse move events even if no button is pressed
    enableMouseTracking(true);
    do {
        getEvent(-1,ev); // ev becomes the next event
        switch (ev.type) {
        case EVT_NONE:
            cout << "No event" << endl;
            break;
        case EVT_MOTION: {
            int x = ev.pix.x();   // cursor's x coord
            int y = ev.pix.y();   // cursor's y coord
            // Cursor is in the "MODE ARCADE" box.
            if(P1.x()<=x && x<P1.x()+w && P1.y()<=y && y<P1.y()+h) {
                // Changing the box's style
                fillRect(P1,w,h,Color(217, 140, 179));
                drawString(Q1,"MODE ARCADE",Color(172, 57, 57));
            } else if(P2.x()<=x && x<P2.x()+w && P2.y()<=y && y<P2.y()+h) {
                // Cursor is in the "MODE COURSE" box.
                // Changing the box's style
                fillRect(P2,w,h,Color(217, 140, 179));
                drawString(Q2,"MODE COURSE", Color(172, 57, 57));
            } else {
                fillRect(P1,w,h,Color(134, 45, 89));
                drawString(Q1,"MODE ARCADE",WHITE);
                fillRect(P2,w,h,Color(134, 45, 89));
                drawString(Q2,"MODE COURSE", WHITE);
            }
            break;
        }
        case EVT_KEY_ON:
            cout << "Use your mouse!"<< endl;
            break;
        case EVT_BUT_ON: {
            int x = ev.pix.x();   // cursor's x coord
            int y = ev.pix.y();   // cursor's y coord
            // Click on the MODE ARCADE box
            if(P1.x()<=x && x<P1.x()+w && P1.y()<=y && y<P1.y()+h) {
                k=1;
                b = true;         // Stop the menu's loop
            }
            else if(P2.x()<=x && x<P2.x()+w && P2.y()<=y && y<P2.y()+h) {
                k=2;
                b = true;         // Stop the menu's loop
            }
            break;
       }
        default: break;
        }
    } while ((ev.type!=EVT_KEY_ON || ev.key!='q' )&& !b);
    closeWindow(win);
    return k;
}

void Menu(){
    int jeu = AffichageMenu();
    if (jeu==1){
        int version = MenuStack();
        if (version==1){
            Stack Sta;
            Sta.jeuSolo();
        }
        else if (version==2){
            Stack2 Sta;
            Sta.jeuSolo();
        }
    }
    else if (jeu==2) {
        int version = MenuPiano();
        if (version==1){
            PianoTiles2 Pia;
            Pia.jeuSolo();
        }
        else if (version==2){
            PianoTiles Pia;
            Pia.jeuSolo();
        }
    }
}
