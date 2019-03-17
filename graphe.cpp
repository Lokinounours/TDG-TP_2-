#include <fstream>
#include <iostream>
#include "graphe.h"

graphe::graphe(std::string nomFichier){
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y; if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.insert({id,new Sommet{id,x,y}});
    }
    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    std::string id_voisin;
    //lecture des aretes
    for (int i=0; i<taille; ++i){
        //lecture des ids des deux extrémités
        ifs>>id; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 1");
        ifs>>id_voisin; if(ifs.fail()) throw std::runtime_error("Probleme lecture arete sommet 2");
        //ajouter chaque extrémité à la liste des voisins de l'autre (graphe non orienté)
        (m_sommets.find(id))->second->ajouterVoisin((m_sommets.find(id_voisin))->second);
        (m_sommets.find(id_voisin))->second->ajouterVoisin((m_sommets.find(id))->second);//remove si graphe orienté
    }
}
void graphe::afficher() const{  /// Affiche les sommets et coordonnees et voisins de ce qu'il y a dans graphe
    std::cout<<"graphe : "<<std::endl;
    std::cout << "  ordre : " << m_sommets.size() << std::endl;
    for(const auto& it : m_sommets)
    {
        std::cout << "  sommet : ";
        it.second->afficherData();
        it.second->afficherVoisins();
        std::cout << std::endl;
    }

}

std::unordered_map<std::string, std::string> graphe::parcoursBFS(std::string id) const{

    std::unordered_map<std::string, std::string> arbre; /// Permet de ranger l'arbre dans une map sous forme (sommet deocuvert, predecesseur)
    std::unordered_set<std::string> dejaVu;  /// Permet de garder une trace des sommets déjà rencontrés
    std::queue<std::string> file;   /// File des sommets autour desquels il faut explorer

    /// On initialise tous les contenants
    file.push(id);
    dejaVu.insert(id);
    arbre.insert(std::make_pair(id, "null"));

    while(!file.empty())
    {
        std::string s_courant = file.front();
        Sommet* s0 = (m_sommets.find(s_courant))->second;
        std::unordered_map<std::string, std::string> arbreSommet = s0->parcoursBFS();

        file.pop(); /// On retire le premier entre dans la liste pour lequel on a note les voisins

        for(auto const& elem : arbreSommet) /// On parcourt la map pour ajouter ce qu'on a trouvé dans le set et pour les ajouter la file
        {
            auto recherche = dejaVu.find(elem.first);
            if (recherche == dejaVu.end()){
                dejaVu.insert(elem.first);
                file.push(elem.first);
                arbre.insert(elem);
            }
        }
    }

    return arbre;
}
void graphe::afficherBFS(std::string id) const{

    std::unordered_map<std::string, std::string> arbre = parcoursBFS(id); /// On appelle parcoursBFS de graphe

    for(auto const& elem : arbre) /// Pour chaque element dans arbre on affiche ce qu'il faut
    {
        std::string courant = elem.first;
        while((arbre.find(courant))->second != "null"){
            std::cout << (arbre.find(courant))->first;
            std::cout << " <--- ";
            courant = (arbre.find(courant))->second;
        }
        std::cout << (arbre.find(courant))->first << std::endl;
    }
}
/// c'est une surcharge de la fonction recursifDFS pour pouvoir passer arbre et dejaVU en paramètre par défault
std::unordered_map<std::string, std::string> graphe::recursifDFS(std::string id) const{
    std::unordered_map<std::string, std::string> arbre;
    std::unordered_set<std::string> dejaVu;
    recursifDFS(id, arbre, dejaVu);
    return arbre;
}
std::unordered_map<std::string, std::string> graphe::recursifDFS(std::string id, std::unordered_map<std::string, std::string> &arbre, std::unordered_set<std::string> &dejaVu) const{

    dejaVu.insert(id); /// on crée un set pour les sommets qui sont déjà visité
    Sommet* s0 = (m_sommets.find(id))->second; /// first = id/ second = ptr
    std::unordered_map<std::string, std::string> arbreSommet = s0->parcoursDFS(); /// Renvoie en format : Valeur/predecesseur
    /// on retrouve ainsi l'ensemble des voisions du sommet(id)
    for(auto const& elem : arbreSommet)
    {
        if (dejaVu.find(elem.first) == dejaVu.end()){ /// si le sommet n'est pas visité alors on rajoute le sommet dans arbre et on relance le programme avec le sommet en id
            arbre.insert({elem.first, id});
            recursifDFS(elem.first, arbre, dejaVu);
        }
    }
    /// une fois la récursivité finie on peut envoyer l'arbre à afficherDFS
    return arbre;

}
void graphe::afficherDFS(std::string id) const{

    std::unordered_map<std::string, std::string> arbre = recursifDFS(id); /// On appelle recursifDFS qui va retourner la map qu'il faut

    for(auto const& elem : arbre) /// On affiche comme il faut
    {
        std::string courant = elem.first;
        std::cout << elem.first;
        while(arbre.find(courant) != arbre.end()){
            std::cout << " <--- " << (arbre.find(courant))->second;
            courant = (arbre.find(courant))->second;
        }
        std::cout << std::endl;
    }
}
int graphe::rechercher_afficherToutesCC() const{ /// Permet de retourner le nombre de CC avec affichage
    int composantes = 0;
    std::cout<< std::endl << "composantes connexes :"<<std::endl;

    std::unordered_map<std::string, std::string> arbreTotal;

    for(const auto& it : m_sommets){ /// Pour tous les sommets
        if(arbreTotal.find(it.first) == arbreTotal.end()){ /// Si le sommet n'a pas été croisé
            auto arbreBFS = parcoursBFS(it.first); /// Lancer un BFS (qui va donc ranger dans la map tous les sommets d'un composante connexe)
            for(const auto& parcoursArbre : arbreBFS){
                arbreTotal.insert(parcoursArbre);   /// On insert tous ce qu'on a eu avec le BFS dans l'arbre general contenant tout
            }
            composantes++; /// On incremente
            std::cout << std::endl << "    cc" << composantes;
            afficherCC(arbreBFS); /// On affiche la composante
        }
    }
    std::cout << std::endl << "Nombre de composantes connexes : " << composantes << std::endl << std::endl;

    return composantes;
}

int graphe::nombreCC() const{ /// Permet de retourner le nombre de CC sans affichage
    std::unordered_map<std::string, std::string> arbreTotal;
    int composantes = 0;
    for(const auto& it : m_sommets){ /// pour tous les sommets
        if(arbreTotal.find(it.first) == arbreTotal.end()){ /// On verifie si on l'a deja croise
            auto arbreBFS = parcoursBFS(it.first); /// Sinon on lajoute avec tous ceux qu'il touche dans une map
            for(const auto& parcoursArbre : arbreBFS){ ///On insere dans la map
                arbreTotal.insert(parcoursArbre);
            }
            composantes++;
        }
    }
    return composantes;
}

void graphe::afficherCC(std::unordered_map<std::string,std::string> arbre) const{
    std::cout << std::endl;
    for(const auto& it : arbre){ /// Affiche chaque element d'une meme composante connexe
        std::cout << "      " << it.first;
    }
}

int graphe::isEulerien(){
    std::set<int> degre; /// un set qui va stocker le nombre d'arrete pour chaque sommet
    int nbrComposantes = nombreCC();
    int nbImpair = 0;
    if(nbrComposantes == 1){
        for (const auto& item: m_sommets)degre.insert(item.second->getDegre()); /// rempli le set
        for (const auto& item: degre){ /// boucle parcourant le set et comptant le nombre de sommet de degre pair
                if(item%2 == 1){
                    nbImpair++;
                }
        }
        if (nbImpair == 2)return 1; /// si 2 nombres impairs alors le graph est une chaine eulerienne
        else if (nbImpair == 0)return 2; /// si aucun nombre impair alors c'est un cycle eulerien
        else return 0; /// sinon on renvoit 0 car le graph n'a rien d'eulerien
    }
    else    { return 0; } /// Si il y a plusieurs composantes connexes ont dit que le graphe n'est pas eulerien
}

graphe::~graphe()
{
    //dtor
}
