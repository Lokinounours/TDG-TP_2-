#include <iostream>
#include "graphe.h"

int main()
{
    graphe g{"graphe_2.txt"};
    std::cout << g.isEulerien();
    //g.afficher();
    //g.afficherBFS("1");
    //g.recursifDFS("1");
    //g.afficherDFS("1");
    //int ncc=g.rechercher_afficherToutesCC();
    //std::cout << "Nombre de composantes connexes : " << ncc;
    return 0;
}
