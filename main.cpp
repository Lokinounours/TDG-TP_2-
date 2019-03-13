#include <iostream>
#include "graphe.h"

int main()
{
    graphe g{"graphe_2.txt"};
    g.afficher();
    //g.afficherBFS("1");
    g.afficherDFS("1");
    //int ncc=g.rechercher_afficherToutesCC();
    return 0;
}
