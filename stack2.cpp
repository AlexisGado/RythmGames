#include "stack2.h"





void Stack2::init()
{
    Wmain = openWindow(w,h);
    setActiveWindow(Wmain);

    fixe = {double(w-cbloci)/2,double(h-cbloci)/2,cbloci,cbloci,AlphaColor(0,0,0)};
    mobile = genBloc();

    affiche();

    drawString((w-cbloci)/2,(h-cbloci)/2-30,"Cliquez pour commencer",BLUE,20,0,false,true);
}


void Stack2::affiche()
{
    clearWindow();

    fillRect(int(fixe.x),int(fixe.y),fixe.w,fixe.h,fixe.col);
    fillRect(int(mobile.x),int(mobile.y),mobile.w,mobile.h,mobile.col);


    drawString(30,30,to_string(score),BLUE,20,0,false,true);
}


Bloc Stack2::genBloc()
{
    Bloc newBloc = {-double(fixe.w),fixe.y,fixe.w,fixe.h,fixe.col+AlphaColor(0,10,0)};
    return newBloc;
}


Bloc Stack2::calcColl()
{
    Bloc nvBloc;

    if (mobile.x<fixe.x)
    {
        nvBloc.w = int(mobile.x)+mobile.w-int(fixe.x);
        nvBloc.x = fixe.x;
    }
    else
    {
        nvBloc.w = int(fixe.x)+fixe.w-int(mobile.x);
        nvBloc.x = mobile.x;
    }

    if (mobile.y<fixe.y)
    {
        nvBloc.h = int(mobile.y)+mobile.h-int(fixe.y);
        nvBloc.y = fixe.y;
    }
    else
    {
        nvBloc.h = int(fixe.y)+fixe.h-int(mobile.y);
        nvBloc.y = mobile.y;
    }

    nvBloc.col = mobile.col;

    return nvBloc;
}


bool Stack2::bougeBloc()
{

    if (mobile.x > fixe.x+fixe.w)
    {
        return false;
    }


    Event e;
    getEvent(0,e);

    if (e.type == EVT_KEY_ON && e.key == ' ')
    {
        if (mobile.x + mobile.w < fixe.x)
        {
            return false;
        }

        score++;

        fixe = calcColl();
        mobile = genBloc();
    }


    mobile.x+=v;


    affiche();

    milliSleep(1);

    return true;
}


bool Stack2::play()
{
    while (true)
    {

        if (!bougeBloc())
        {

            affiche();
            cout<<"Perdu!"<<endl;
            cout<<"Score : "<<score<<endl;
            return false;
        }

    }

    return true;
}


void Stack2::jeuSolo()
{
    init();

    getKey();

    fillRect(0,0,w,(h-cbloci)/2,WHITE);


    play();

    closeWindow(Wmain);

    endGraphics();

}


