#include "stack.h"


void Stack::init() // ecran de base avant le depart
{
    Wmain = openWindow(w,h);
    setActiveWindow(Wmain);
    setBackGround(BLACK);

    double xi = (w-wbloci)/2;

    fillRect(int(xi),hsol,wbloci,hbloc,Color(200,0,0));

    drawString(int(xi)+10,hsol-30,"Cliquez pour commencer",Color(200,0,0),20,0,false,true);

    Bloc1 startBloc = {xi,wbloci,Color(200,0,0)};
    pile.push_front(startBloc); // On met la base de la tour dans la pile
}


void Stack::afficheTout(lis pileCopie) // est appelee quand le joueur a place le bloc
{
    setBackGround(BLACK); // on efface tout

    int hactu = hsol;
    Color coul = pileCopie.front().col;

    while(!pileCopie.empty())  // on vide la pile et on affiche les blocs successivement
    {
        Bloc1 bloc = pileCopie.front();
        pileCopie.pop_front();
        fillRect(int(bloc.x),hactu,bloc.size,hbloc,bloc.col);
        hactu+=hbloc;
        if (hactu>h) // on s'arrete si on est sorti de l ecran
            break;
    }
    drawString(w/2-5,80,to_string(score),coul,70,0,false,true); // on affiche le score
}


Bloc1 Stack::genBloc(int wbloc)  //renvoie un bloc venant aleatoirement de la droite ou la gauche
{
    int rx = Random(0,2);
    double xdep;

    if (rx==1)
    {
        vx = 1;
        xdep = -wbloc;
    }
    else
    {
        vx = -1;
        xdep = w;
    }

    return {xdep,wbloc,Color(200,byte(200*abs(sin(float(score+1)/10))),0)};
}


int Stack::calcTaille(Bloc1 mouv,Bloc1 fixe) // Calcule la taille du bloc apres le clic du joueur (retire les bouts qui depassent)
{

    if (mouv.x<fixe.x)
        return int(mouv.x)+mouv.size-int(fixe.x);
    else
        return int(fixe.x)+fixe.size-int(mouv.x);

}


bool Stack::bougeBloc()
{
    Bloc1 bloc = pile.front(); // On prend l element au sommet de la pile, le bloc mobile
    pile.pop_front();

    if (vx == 1 && bloc.x > pile.front().x+pile.front().size)  // Si le joueur n a pas appuye quand le bloc a depasse la tour il perd
    {
        return false;
    }
    else
    {
        if (vx == -1 && bloc.x + bloc.size < pile.front().x) // idem si le bloc vient de l autre direction
        {
            return false;
        }
    }


    Event e;
    getEvent(0,e);

    if (e.type == EVT_KEY_ON && e.key == ' ') // On detecte le clic du joueur
    {
        if (vx == 1 && bloc.x + bloc.size < pile.front().x) // si c est trop tot il perd
        {
            return false;
        }
        else
        {
            if (vx == -1 && bloc.x > pile.front().x+pile.front().size)
            {
                return false;
            }
        }

        score++; // si il a bien clique son score augmente
        if (score%5==0) // la vitesse augemente de 10 pourcents tous les 5 blocs
        {
            v*=1.1;
        }

        int nvTaille = calcTaille(bloc,pile.front());

        bloc.size = nvTaille;
        bloc.x = max(bloc.x,pile.front().x); // On calcule les nouvelles dimensions

        pile.push_front(bloc); // on remet le bloc dans la pile

        lis pileCopie = pile;
        afficheTout(pileCopie); // on affiche la nouvelle tour

        bloc = genBloc(nvTaille); // on genere un nouveau bloc mobile
    }


    bloc.x+=v*vx;  // On deplace le bloc mobile
    pile.push_front(bloc); // on le met au sommet de la pile

    if (vx==1) // on gere ici l affichage uniquement du bloc mobile pour ameliorer les performances et ne pas tout redessiner a chaque frame
    {
        fillRect(int(bloc.x)-1,hsol-hbloc,1,hbloc,BLACK);
        fillRect(int(bloc.x),hsol-hbloc,bloc.size,hbloc,bloc.col);
    }
    else
    {
        fillRect(int(bloc.x)+bloc.size,hsol-hbloc,1,hbloc,BLACK);
        fillRect(int(bloc.x),hsol-hbloc,bloc.size,hbloc,bloc.col);
    }

    milliSleep(1);
    return true;
}


bool Stack::play()
{
    pile.push_front(genBloc(wbloci));

    while (true)
    {

        if (!bougeBloc()) // On continue tant que le joueur ne fait pas d erreur
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

    Menu();

}


