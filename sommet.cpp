#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include <algorithm>
#include "sommet.h"

bool compareSommets(const Sommet* a, const Sommet* b) { return ((*a).getID() > (*b).getID()); } /// Permet de comparer des const Sommet* (a l'envers car insert de map ajoute au debut)
bool compareSommetsDFS(const Sommet* a, const Sommet* b) { return ((*a).getID() < (*b).getID()); } /// Permet de comparer des const Sommet* (a l'envers car insert de map ajoute au debut)


Sommet::Sommet(std::string id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}
void Sommet::ajouterVoisin( Sommet* voisin){
    m_voisins.push_back(voisin);
}
 void Sommet::afficherData() const{
     std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
 }
void Sommet::afficherVoisins() const{
    std::cout<<"  voisins :"<<std::endl;
    for(auto v:m_voisins) {
        v->afficherData();
    }
}

std::unordered_map<std::string,std::string> Sommet::parcoursBFS(){

    std::unordered_map<std::string,std::string> arbre;

    std::sort(m_voisins.begin(), m_voisins.end(), compareSommets);

    for(const auto& elem : m_voisins)
    {
        arbre.insert(std::make_pair((*(elem)).getID(), this->getID()));
    }

    return arbre;
}
std::unordered_map<std::string,std::string> Sommet::parcoursDFS(){

    std::unordered_map<std::string,std::string> arbre;

    std::sort(m_voisins.begin(), m_voisins.end(), compareSommets);
    for(const auto& elem : m_voisins)
    {
        ///std::cout << "   valeurs du voisins après trie" << (*(elem)).getID() << std::endl;
        /// pour vérifier que le trie s'éffectue correctement et c'est validé
        arbre.insert(std::make_pair((*(elem)).getID(), this->getID()));
    }
    return arbre;
}
std::unordered_set<std::string> Sommet::rechercherCC() const{
    std::unordered_set<std::string> cc;
    std::cout<<"rechercherCC a coder"<<std::endl;
    return cc;
}

std::string Sommet::getID()const{
    return m_id;
}

int Sommet::getDegre()const{
    return m_voisins.size();
}

Sommet::~Sommet()
{
    //dtor
}
