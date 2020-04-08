#include <iostream>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;

#include <cstdlib>
#include <ctime>
using namespace std ;

void InitRandom()
{
    srand((unsigned int)time(0));
}

int Random(int a, int b)
{
    return int(a + (b-a)*double(rand())/RAND_MAX);
}


// 0 -> Nord
// 1 -> est
// 2 -> sud
// 3 -> ouest

const int N = 31;
const int cote = 25;
const int delta[4][2] = {{0,-1},{1,0},{0,1},{-1,0}}; // tableau donnant le déplacement dans la grille pour chaque direction (N-E-S-O)
const int idep = 14;
const int jdep = 30; // coordonnées du depart du robot


bool pasfini(bool tab[N][N]){ //Renvoie true si la grille est incomplete et false sinon. Permet de depiler plus rapidement tous les appels recursifs a la fin
    bool fini = true ;
    for (int i = 0;i<N && fini;i++){
        for (int j = 0;j<N && fini;j++){
            fini = tab[i][j] && fini;

        }
    }
    return !fini;
}


void deplace(int i, int j, bool tab[N][N]){
    //Rq : le robot ne va pas à la meme vitesse dans toutes les directions : il regarde chaque direction selon la sequence N-E-S-O et attend a chaque fois

    for (int k = 0;k<4;k++){ //On regarde successivement chaque direction
        //if (pasfini(tab)){ // Ce test n'est pas necessaire mais il permet de depiler plus vite a la fin
            fillRect(i*cote,j*cote,cote,cote,RED); // Affiche le robot
            milliSleep(5);

            if (i+delta[k][0]>=0 && i+delta[k][0]<N && j+delta[k][1]>=0 && j+delta[k][1]<N && !(tab[i+delta[k][0]][j+delta[k][1]])){ //On vérifie que l'endroit ou veut aller le robot est vide et dans la grille

                tab[i+delta[k][0]][j+delta[k][1]] = true;
                fillRect(i*cote,j*cote,cote,cote,BLACK);
                deplace(i+delta[k][0],j+delta[k][1],tab); // On rappelle la fonction a la nouvelle position avec la grille mise a jour
            }

            else{

                fillRect(i*cote,j*cote,cote,cote,BLACK); //si c'est pas possible on affiche en noir car si c'etait la derniere direction on doit revenir sur nos pas
            }
        //}
        //else{
            //fillRect(i*cote,j*cote,cote,cote,BLACK); // On retire le robot a la fin si on a fait le test
        //}
    }

}

int compteVides(int i, int j, bool grille[N][N],bool tab[4]){ // Compte le nombre de case vides autour du robot
    int compteur = 0;
    for (int k = 0;k<4;k++){
        if (i+delta[k][0]>=0 && i+delta[k][0]<N && j+delta[k][1]>=0 && j+delta[k][1]<N && !grille[i+delta[k][0]][j+delta[k][1]]){
            tab[k]=true;
            compteur++;
        }
        else
            tab[k]=false;

    }
    return compteur;
}


void deplaceRandom(int i, int j, bool grille[N][N]){
    /* Le principe de déplacement est le suivant :
    le robot choisit aléatoirement une direction parmi les cases libres autour de lui
    et si aucune n'est libre alors il revient sur ses pas jusqu a trouver une case pas entouree de cases pleines.
    J'avais pensé a laisser le retour comme une option de déplacement à chaque fois mais le temps moyen de terminaison etait tres long*/

    bool tab[4] = {false,false,false,false};
    while (compteVides(i,j,grille,tab) !=0){
        int compteur = compteVides(i,j,grille,tab);

        fillRect(i*cote,j*cote,cote,cote,RED);
        milliSleep(10);

        if (compteur != 0){

            int n = Random(1,compteur+1);

            int direction;
            int l = 0;
            for (int k=0;k<4;k++){ // Warning non genant : etant donné le if ci dessus, direction sera toujours initialisée
                if (tab[k]){
                    l++;
                    if (l==n){
                        direction = k;
                        break;
                    }
                }
            }



            if (i+delta[direction][0]>=0 && i+delta[direction][0]<N && j+delta[direction][1]>=0 && j+delta[direction][1]<N && !(grille[i+delta[direction][0]][j+delta[direction][1]])){

                grille[i+delta[direction][0]][j+delta[direction][1]] = true;
                fillRect(i*cote,j*cote,cote,cote,BLACK);
                deplaceRandom(i+delta[direction][0],j+delta[direction][1],grille);
                fillRect(i*cote,j*cote,cote,cote,RED);
                milliSleep(10);


            }
            else{

                fillRect(i*cote,j*cote,cote,cote,BLACK);
            }
        }
    }
    fillRect(i*cote,j*cote,cote,cote,BLACK);


}



int main(){

    // Les 2 animations vont se lancer à la suite, le robot partant de (idep,jdep)

    InitRandom();
    Window w1 = openWindow(cote*N,cote*N);

    bool grille[N][N];
    for (int i = 0;i<N;i++){
        for (int j = 0;j<N;j++){
            grille[i][j] = false;
        }
    }

    grille[idep][jdep] = true;

    deplace(idep,jdep,grille);

    closeWindow(w1);

    Window w2 = openWindow(cote*N,cote*N);

    for (int i = 0;i<N;i++){
        for (int j = 0;j<N;j++){
            grille[i][j] = false;
        }
    }
    grille[idep][jdep] = true;

    deplaceRandom(idep,jdep,grille);



    endGraphics();
    return 0;
}

