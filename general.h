#pragma once

#include <iostream>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;

#include <cstdlib>
#include <ctime>
using namespace std ;

#include <list>

#include "stack.h"
#include "stack2.h"
#include "piano_tiles.h"
#include "piano_tiles_course.h"

void InitRandom();
int Random(int a, int b); //randrange(a,b)

int AffichageMenu();
int MenuStack();
void Menu();
