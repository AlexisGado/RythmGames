#include <iostream>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;

#include <cstdlib>
#include <ctime>
using namespace std ;

#include <list>

void InitRandom()
{
    srand((unsigned int)time(0));
}

int Random(int a, int b) //randrange(a,b)
{
    return int(a + (b-a)*double(rand())/RAND_MAX);
}


void init(int w,int h, Window& Wmain,int hsol,int wbloci,list<int> & pile)
{
    Wmain = openWindow(w,h);
    setActiveWindow(Wmain);

    int xi = (w-wbloci)/2;

    fillRect(xi,hsol,wbloci,h,BLACK);

    drawString(xi+10,hsol-30,"Cliquez pour commencer",BLUE,20,0,false,true);
    pile.push_front(wbloci);
}


void affiche(list<int> pile,Window Wmain)
{

}



bool bougeBloc(list<int>& pile)
{


    return true;
}


bool play(Window Wmain, int v0,int hbloc,list<int>& pile)
{
    while (true)
    {
        affiche(pile,Wmain);

        if (!bougeBloc(pile))
        {
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
    int v0 = 10;
    list<int> pile; // taille de chaque bloc

    init(w,h,Wmain,hsol,wbloci,pile);

    anyClick();
    clearWindow();

    play(Wmain,v0,hbloc,pile);






    endGraphics();
    return 0;
}

