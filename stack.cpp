#include "stack.h"


void Stack::init()
{
    Wmain = openWindow(w,h);
    setActiveWindow(Wmain);
    setBackGround(BLACK);

    double xi = (w-wbloci)/2;

    fillRect(int(xi),hsol,wbloci,hbloc,Color(200,0,0));

    drawString(int(xi)+10,hsol-30,"Cliquez pour commencer",Color(200,0,0),20,0,false,true);

    Bloc1 startBloc = {xi,wbloci,Color(200,0,0)};
    pile.push_front(startBloc);
}


void Stack::afficheTout(lis pileCopie)
{
    setBackGround(BLACK);

    int hactu = hsol;
    Color coul = pileCopie.front().col;

    while(!pileCopie.empty())
    {
        Bloc1 bloc = pileCopie.front();
        pileCopie.pop_front();
        fillRect(int(bloc.x),hactu,bloc.size,hbloc,bloc.col);
        hactu+=hbloc;
        if (hactu>h)
            break;
    }
    drawString(w/2-5,80,to_string(score),coul,70,0,false,true);
}


Bloc1 Stack::genBloc(int wbloc)
{
    double xdep = -wbloc;
    return {xdep,wbloc,Color(200,byte(200*abs(sin(float(score+1)/10))),0)};
}


int Stack::calcTaille(Bloc1 mouv,Bloc1 fixe)
{
    if (mouv.x<fixe.x)
        return int(mouv.x)+mouv.size-int(fixe.x);
    else
        return int(fixe.x)+fixe.size-int(mouv.x);
}


bool Stack::bougeBloc()
{
    Bloc1 bloc = pile.front();
    pile.pop_front();

    if (bloc.x > pile.front().x+pile.front().size)
    {
        return false;
    }


    Event e;
    getEvent(0,e);

    if (e.type == EVT_KEY_ON && e.key == ' ')
    {
        if (bloc.x + bloc.size < pile.front().x)
        {
            return false;
        }

        score++;
        int nvTaille = calcTaille(bloc,pile.front());

        bloc.size = nvTaille;
        bloc.x = max(bloc.x,pile.front().x);

        pile.push_front(bloc);

        fillRect(int(bloc.x),hsol-hbloc,bloc.size,hbloc,WHITE);
        lis pileCopie = pile;
        afficheTout(pileCopie);

        bloc = genBloc(nvTaille);
    }


    bloc.x+=v;
    pile.push_front(bloc);


    fillRect(int(bloc.x)-1,hsol-hbloc,1,hbloc,BLACK);
    fillRect(int(bloc.x),hsol-hbloc,bloc.size,hbloc,bloc.col);


    milliSleep(1);
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
            return false;
        }

    }

    return true;
}


void Stack::jeuSolo()
{
    init();

    getKey();

    fillRect(0,0,w,hsol,BLACK);


    play();

    closeWindow(Wmain);

}


