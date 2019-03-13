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
void graphe::afficher() const{
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

    file.push(id);
    dejaVu.insert(id);

    while(!file.empty())
    {
        std::string s_courant = file.front();
        Sommet* s0 = (m_sommets.find(s_courant))->second;
        std::unordered_map<std::string, std::string> arbreSommet = s0->parcoursBFS();

        for(auto const& elem : arbreSommet) /// On parcourt la map pour ajouter ce qu'on a trouvé dans le set et pour les ajouter la file
        {
            auto recherche = dejaVu.find(elem.first);
            if (recherche == dejaVu.end()){
                dejaVu.insert(elem.first);
                file.push(elem.first);
                arbre.insert(elem);
            }
        }

        file.pop(); /// On retire le premier entre dans la liste pour lequel on a note les voisins
    }

    return arbre;
}
void graphe::afficherBFS(std::string id) const{

    std::unordered_map<std::string, std::string> arbre = parcoursBFS(id);

    for(auto const& elem : arbre)
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
std::unordered_map<std::string, std::string> graphe::parcoursDFS(std::string id) const{

    std::unordered_map<std::string, std::string> arbre; /// Permet de ranger l'arbre dans une map sous forme (sommet deocuvert, predecesseur)
    std::unordered_set<std::string> dejaVu;  /// Permet de garder une trace des sommets déjà rencontrés
    std::stack<std::string> pile;   /// File des sommets autour desquels il faut explorer

    pile.push(id);
    dejaVu.insert(id);

    while(!pile.empty())
    {
        std::string s_courant = pile.top();
        Sommet* s0 = (m_sommets.find(s_courant))->second;
        std::unordered_map<std::string, std::string> arbreSommet = s0->parcoursDFS();
        pile.pop(); /// On pop ici afin de l'enlever avant d'ajouter d'autres sommets

        for(auto const& elem : arbreSommet) /// On parcourt la map pour ajouter ce qu'on a trouvé dans le set et pour les ajouter la pile
        {
            auto recherche = dejaVu.find(elem.first);
            if (recherche == dejaVu.end()){
                dejaVu.insert(elem.first);
                pile.push(elem.first);
                arbre.insert(elem);
            }
        }

    }

    return arbre;
}
void graphe::afficherDFS(std::string id) const{

    std::unordered_map<std::string, std::string> arbre = parcoursDFS(id);

    for(auto const& elem : arbre)
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
int graphe::rechercher_afficherToutesCC() const{
    int i=0;
    std::cout<<"composantes connexes :"<<std::endl;
    std::cout<<"recherche et affichage de toutes les composantes connexes a coder"<<std::endl;
    return i;
}
graphe::~graphe()
{
    //dtor
}
