#include "stack.h"





void Stack::init()
{
    Wmain = openWindow(w,h);
    setActiveWindow(Wmain);

    int xi = (w-wbloci)/2;

    fillRect(xi,hsol,wbloci,hbloc,BLACK);

    drawString(xi+10,hsol-30,"Cliquez pour commencer",BLUE,20,0,false,true);
    pile.push_front(couple(wbloci,xi));
}


void Stack::afficheTout(lis pileCopie)
{
    clearWindow();

    int hactu = hsol;

    while(!pileCopie.empty())
    {
        couple bloc = pileCopie.front();
        pileCopie.pop_front();
        fillRect(int(bloc.second),hactu,bloc.first,hbloc,BLACK);
        hactu+=hbloc;
        if (hactu>h)
            break;
    }
    drawString(w/2-5,30,to_string(score),BLUE,20,0,false,true);
}


couple Stack::genBloc(int wbloc)
{
    int xdep = -wbloc;
    return couple(wbloc,xdep);
}


int Stack::calcTaille(couple mouv,couple fixe)
{
    if (mouv.second<fixe.second)
        return int(mouv.second)+mouv.first-int(fixe.second);
    else
        return int(fixe.second)+fixe.first-int(mouv.second);
}


bool Stack::bougeBloc()
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
        lis pileCopie = pile;
        afficheTout(pileCopie);

        bloc = genBloc(nvTaille);
    }


    bloc.second+=v;
    pile.push_front(bloc);


    fillRect(int(bloc.second)-1,hsol-hbloc,1,hbloc,WHITE);
    fillRect(int(bloc.second),hsol-hbloc,bloc.first,hbloc,RED);

    return true;
}


bool Stack::play()
{
    pile.push_front(genBloc(wbloci));

    while (true)
    {

        if (!bougeBloc())
        {
            lis pileCopie = pile;
            afficheTout(pileCopie);
            cout<<"Perdu!"<<endl;
            cout<<"Score : "<<pile.size()-1<<endl;
            break;
        }

    }

    return true;
}


void Stack::jeuSolo()
{
    init();

    getKey();

    fillRect(0,0,w,hsol,WHITE);


    play();

    closeWindow(Wmain);

}


