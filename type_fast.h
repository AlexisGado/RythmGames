#pragma once

#include "general.h"


class TypeFast
{
    int w=500,h=500;
    Window Wmain;

    int score = 0;

    char lettre;



    void init();
    void affiche();
    char genLettre();

    bool play();

public:

    void jeuSolo();

};
