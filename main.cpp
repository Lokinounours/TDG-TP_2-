#include <iostream>
#include "graphe.h"

int main()
{
    graphe h{"graphe_1.txt"};
    graphe g{"graphe_2.txt"};
    int choix = 0;
    bool continuer = true;
    std::string graph = "1";
    std::string sommet = "1";

    while (continuer){
        std::cout << "Que voulez-vous faire ?" << std::endl;
        std::cout << "0- Quitter" << std::endl;
        std::cout << "1- Affichage BFS" << std::endl;
        std::cout << "2- Affichage DFS" << std::endl;
        std::cout << "3- Utiliser graphe 1" << std::endl;
        std::cout << "4- Utiliser graphe 2" << std::endl;
        std::cout << "5- IsEulerien" << std::endl;
        std::cout << "6- Afficher composantes connexes" << std::endl;
        std::cin >> choix;
        switch(choix){
            case 0:
                continuer = 0;
                break;
            case 1:
                std::cout << std::endl << "A partir de quel sommet ? Sommet : ";
                std::cin >> sommet;
                if(graph == "1") h.afficherBFS(sommet);
                else if(graph == "2") g.afficherBFS(sommet);
                else std::cout << "Erreur" << std::endl;
                break;
            case 2:
                std::cout << std::endl << "A partir de quel sommet ? Sommet : ";
                std::cin >> sommet;
                if(graph == "1")h.afficherDFS(sommet);
                else if(graph == "2")g.afficherDFS(sommet);
                else std::cout << "Erreur" << std::endl;
                break;
            case 3:
                graph = "1";
                break;
            case 4:
                graph = "2";
                break;
            case 5:
                if(graph == "1") std::cout << h.isEulerien();
                else if(graph == "2") std::cout << g.isEulerien();
                else std::cout << "Erreur" << std::endl;
                break;
            case 6:
            {
                if(graph == "1") int ncc = h.rechercher_afficherToutesCC();
                else if(graph == "2") int ncc = g.rechercher_afficherToutesCC();
                else std::cout << "Erreur" << std::endl;
                break;
            }
            default:
            {
                std::cout << "Erreur" << std::endl;
                break;
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
