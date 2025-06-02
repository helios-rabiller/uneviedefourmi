#ifndef ANTS_HPP
#define ANTS_HPP

#include <string>
#include <vector>
#include <unordered_map>

struct Fourmi {
    int id;
    int cheminIdx;               // indice du chemin choisi
    int position;                // position dans ce chemin
    bool arrivée;
};

class Fourmiliere {
private:
    std::unordered_map<std::string, std::vector<std::string>> graph;
    std::unordered_map<std::string, int> capacitesSalles;      // capacité max par salle
    std::unordered_map<std::string, int> occupationSalles;     // occupation actuelle par salle

    std::vector<std::vector<std::string>> chemins;             // chemins trouvés du plus court au plus long

    // Recherche tous les chemins possibles du début à la fin (avec limite max chemins)
    void trouverTousChemins(const std::string& debut, const std::string& fin, int maxChemins);

    void trierCheminsParLongueur();

public:
    void ajouterLiaison(const std::string& a, const std::string& b);
    void definirCapaciteSalle(const std::string& salle, int capacite);
    void simulerFourmis(const std::string& debut, const std::string& fin, int nombreFourmis);
};

#endif
