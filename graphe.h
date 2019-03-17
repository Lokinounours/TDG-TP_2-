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
        ///constructeur qui charge le graphe en m�moire
        //format du fichier ordre/liste des sommets/taille/liste des ar�tes
        graphe(std::string);
        ~graphe();
        void afficher() const;
        ///lance un parcours en largeur � partir du sommet d'identifiant id
        std::unordered_map<std::string, std::string> parcoursBFS(std::string) const;
        ///lance et affiche le parcours en largeur � partir du sommet d'identifiant id
        void afficherBFS(std::string) const;

        ///lance et affiche le parcours en profondeur � partir du sommet d'identifiant id
        void afficherDFS(std::string) const;
        ///recherche et affiche les composantes connexes
        ///retourne le nombre de composantes connexes
        int nombreCC() const;
        /// retourne aussi le nombre de cc mais les affiche en plus
        int rechercher_afficherToutesCC() const;
        ///Permet l'affichage des CC
        void afficherCC(std::unordered_map<std::string,std::string> arbre) const;
        /// Renvoie 0 si graphe pas eulerien, 1 si il ya une chaine eulerienne et 2 si il y a un cycle eulerien
        int isEulerien();

        ///lance un parcours en profondeur � partir du sommet d'identifiant id en mode R�cursif
        /// Le programme se relance ainsi de lui m�me tant qu'il n'a pas explor� tous les sommets ou si ils sont d�j� tous dans d�j�Vu
        std::unordered_map<std::string, std::string> recursifDFS(std::string id, std::unordered_map<std::string, std::string> &arbre, std::unordered_set<std::string> &dejaVu) const;
        ///Surchage de la fonction RecursifDFS pour pouvoir lancer le DFS sans avoir � donner un arbre et un d�j�VU
        std::unordered_map<std::string, std::string> recursifDFS(std::string id) const;

    protected:

    private:
        /// Le r�seau est constitu� d'une collection de sommets
        std::unordered_map<std::string,Sommet*> m_sommets;//stock�e dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)

};

#endif // GRAPHE_H
