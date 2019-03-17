#include <iostream>
#include "graphe.h"

int main()
{
    graphe h{"graphe_1.txt"};
    graphe g{"graphe_2.txt"};
    int choix = 0;
    bool continuer = true;
    std::string graph = "1";
    while (continuer){
        std::cout << "Choose what you want to do" << std::endl;
        std::cout << "1-affichage BFS" << std::endl;
        std::cout << "2-affichage DFS" << std::endl;
        std::cout << "3-utiliser graph 1" << std::endl;
        std::cout << "4-utiliser graph 2" << std::endl;
        std::cout << "5-IsEulerien" << std::endl;
        std::cout << "6-afficher composante connexe" << std::endl;
        std::cin >> choix;
        switch(choix){
            case 1:
                g.afficherBFS(graph);
                break;
            case 2:
                g.afficherDFS(graph);
                break;
            case 3:
                graph = "1";
                break;
            case 4:
                graph = "2";
                break;
            case 5:
                std::cout << g.isEulerien();
                break;
            case 6:
                {
                    int ncc=g.rechercher_afficherToutesCC();
                    std::cout << "Nombre de composantes connexes : " << ncc;
                    break;
                }
            default:
                {
                    std::cout << "Erreur" << std::endl;
                    break;
                }
        }




        std::cout << "Would you like to continue ?" << std::endl;
        std::cin >> continuer;
    }
    return 0;
}
