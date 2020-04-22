#include <iostream>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;

#include <cstdlib>
#include <ctime>
using namespace std ;

#include <list>
#include <tuple>

#include "general.h"

using lis = list<pair<int,double>>;
using couple = pair<int,double>;



void init(int w,int h, Window& Wmain,int hsol,int wbloci,int hbloc,lis & pile)
{
    Wmain = openWindow(w,h);
    setActiveWindow(Wmain);

    int xi = (w-wbloci)/2;

    fillRect(xi,hsol,wbloci,hbloc,BLACK);

    drawString(xi+10,hsol-30,"Cliquez pour commencer",BLUE,20,0,false,true);
    pile.push_front(couple(wbloci,xi));
}


void afficheTout(lis pile,int w,int h,int hbloc,int hsol,int score)
{
    clearWindow();

    int hactu = hsol;

    while(!pile.empty())
    {
        couple bloc = pile.front();
        pile.pop_front();
        fillRect(int(bloc.second),hactu,bloc.first,hbloc,BLACK);
        hactu+=hbloc;
        if (hactu>h)
            break;
    }

    drawString(w/2-5,30,to_string(score),BLUE,20,0,false,true);

}


couple genBloc(int wbloc)
{
    int xdep = -wbloc;
    return couple(wbloc,xdep);
}


int calcTaille(couple mouv,couple fixe)
{
    if (mouv.second<fixe.second)
        return int(mouv.second)+mouv.first-int(fixe.second);
    else
        return int(fixe.second)+fixe.first-int(mouv.second);
}


bool bougeBloc(lis& pile,double v,int w, int h,int hbloc,int hsol, int& score)
{
    couple bloc = pile.front();
    pile.pop_front();

    if (bloc.second > pile.front().second+pile.front().first)
    {
        return false;
    }


    Event e;
    getEvent(0,e);

    if (e.type == EVT_KEY_ON && e.key == ' ')
    {
        if (bloc.second + bloc.first < pile.front().second)
        {
            return false;
        }

        score++;
        int nvTaille = calcTaille(bloc,pile.front());

        bloc.first = nvTaille;
        bloc.second = max(bloc.second,pile.front().second);

        pile.push_front(bloc);

        fillRect(int(bloc.second),hsol-hbloc,bloc.first,hbloc,WHITE);
        afficheTout(pile,w,h,hbloc,hsol,score);

        bloc = genBloc(nvTaille);
    }


    bloc.second+=v;
    pile.push_front(bloc);


    fillRect(int(bloc.second)-1,hsol-hbloc,1,hbloc,WHITE);
    fillRect(int(bloc.second),hsol-hbloc,bloc.first,hbloc,RED);

    return true;
}


bool play(int w,int h, double v0,int hbloc,int wbloci,int hsol,lis& pile,int& score)
{
    pile.push_front(genBloc(wbloci));

    while (true)
    {

        if (!bougeBloc(pile,v0,w,h,hbloc,hsol,score))
        {
            afficheTout(pile,w,h,hbloc,hsol,score);
            cout<<"Perdu!"<<endl;
            cout<<"Score : "<<pile.size()-1<<endl;
            break;
        }

    }


    return true;
}






int main(){
    int w=800,h=600;
    Window Wmain;

    int hsol = h/4;
    int hbloc = h/20;
    int wbloci = w/3;
    double v0 = 0.005;
    lis pile; // taille de chaque bloc
    int score = 0;

    init(w,h,Wmain,hsol,wbloci,hbloc,pile);

    anyClick();

    fillRect(0,0,w,hsol,WHITE);


    play(w,h,v0,hbloc,wbloci,hsol,pile,score);






    endGraphics();
    return 0;
}

