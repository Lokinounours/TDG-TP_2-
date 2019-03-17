#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <set>
#include "sommet.h"

class graphe
{
    public:
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        graphe(std::string);
        ~graphe();
        void afficher() const;
        ///lance un parcours en largeur à partir du sommet d'identifiant id
        std::unordered_map<std::string, std::string> parcoursBFS(std::string) const;
        ///lance et affiche le parcours en largeur à partir du sommet d'identifiant id
        void afficherBFS(std::string) const;
         ///lance un parcours en profondeur à partir du sommet d'identifiant id
        std::unordered_map<std::string, std::string> parcoursDFS(std::string) const;
        ///lance et affiche le parcours en profondeur à partir du sommet d'identifiant id
        void afficherDFS(std::string) const;
        ///recherche et affiche les composantes connexes
        ///retourne le nombre de composantes connexes
        int rechercher_afficherToutesCC() const;
        ///Permet l'affichage des CC
        void afficherCC(std::unordered_map<std::string,std::string> arbre) const;

        int isEulerien();

        std::unordered_map<std::string, std::string> recursifDFS(std::string id, std::unordered_map<std::string, std::string> &arbre, std::unordered_set<std::string> &dejaVu) const;
        std::unordered_map<std::string, std::string> recursifDFS(std::string id) const;

    protected:

    private:
        /// Le réseau est constitué d'une collection de sommets
        std::unordered_map<std::string,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)

};

#endif // GRAPHE_H
