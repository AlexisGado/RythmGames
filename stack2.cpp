#include "stack2.h"





void Stack2::init()
{
    Wmain = openWindow(w,h);
    setActiveWindow(Wmain);

    fixe = {double(w-cbloci)/2,double(h-cbloci)/2,cbloci,cbloci,Color(0,0,200)};
    mobile = genBloc();

    affiche();

    drawString((w-cbloci)/2 + 10,(h-cbloci)/2-30,"Cliquez pour commencer",BLUE,20,0,false,true);
}


void Stack2::affiche()
{
    setBackGround(BLACK);

    fillRect(int(fixe.x),int(fixe.y),fixe.w,fixe.h,fixe.col);
    fillRect(int(mobile.x),int(mobile.y),mobile.w,mobile.h,mobile.col);


    drawString(50,100,to_string(score),mobile.col,100,0,false,true);
}


Bloc Stack2::genBloc()
{

    int r = Random(0,4);
    double xdep,ydep;

    vx = dir[r][0];
    vy = dir[r][1];

    xdep = -(vx>0)*fixe.w + (vx<0)*w + (vx==0)*fixe.x;
    ydep = -(vy>0)*fixe.h + (vy<0)*h + (vy==0)*fixe.y;


    Bloc newBloc = {xdep,ydep,fixe.w,fixe.h,Color(0,byte(200*abs(sin(float(score+1)/6))),byte(200*abs(cos(float(score+1)/6))))};
    return newBloc;
}


Bloc Stack2::calcColl()
{
    Bloc nvBloc;

    nvBloc.x = max(fixe.x,mobile.x);
    nvBloc.y = max(fixe.y,mobile.y);
    nvBloc.w = fixe.w - int(abs(mobile.x-fixe.x));
    nvBloc.h = fixe.h - int(abs(mobile.y-fixe.y));


    nvBloc.col = mobile.col;

    return nvBloc;
}


bool Stack2::bougeBloc()
{


    if (vx == 1 && mobile.x > fixe.x+fixe.w)
    {
        return false;
    }
    if (vy == 1 && mobile.y > fixe.y+fixe.h)
    {
        return false;
    }
    if (vx == -1 && mobile.x+mobile.w < fixe.x)
    {
        return false;
    }
    if (vy == -1 && mobile.y + mobile.h < fixe.y)
    {
        return false;
    }



    Event e;
    getEvent(0,e);

    if (e.type == EVT_KEY_ON && e.key == ' ')
    {

        if (vx == -1 && mobile.x > fixe.x+fixe.w)
         {
            return false;
        }
        if (vy == -1 && mobile.y > fixe.y+fixe.h)
        {
            return false;
        }
        if (vx == 1 && mobile.x+mobile.w < fixe.x)
        {
            return false;
        }
        if (vy == 1 && mobile.y + mobile.h < fixe.y)
        {
            return false;
        }


        score++;

        fixe = calcColl();
        mobile = genBloc();
    }

    mobile.x+=v*vx;
    mobile.y+=v*vy;

    affiche();

    milliSleep(2);

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

    Menu();

}


