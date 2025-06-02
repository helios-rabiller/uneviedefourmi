#include "ants.hpp"
#include <iostream>
#include <queue>
#include <algorithm>
#include <unordered_set>

void Fourmiliere::ajouterLiaison(const std::string& a, const std::string& b) {
    graph[a].push_back(b);
    graph[b].push_back(a);

    if (capacitesSalles.find(a) == capacitesSalles.end())
        capacitesSalles[a] = 1;
    if (capacitesSalles.find(b) == capacitesSalles.end())
        capacitesSalles[b] = 1;

    if (occupationSalles.find(a) == occupationSalles.end())
        occupationSalles[a] = 0;
    if (occupationSalles.find(b) == occupationSalles.end())
        occupationSalles[b] = 0;
}

void Fourmiliere::definirCapaciteSalle(const std::string& salle, int capacite) {
    capacitesSalles[salle] = capacite;
    if (occupationSalles.find(salle) == occupationSalles.end())
        occupationSalles[salle] = 0;
}

// Trouve tous les chemins simples entre debut et fin avec DFS, limite maxChemins
void dfsChemins(const std::unordered_map<std::string, std::vector<std::string>>& graph,
                const std::string& current,
                const std::string& fin,
                std::vector<std::string>& path,
                std::vector<std::vector<std::string>>& result,
                std::unordered_set<std::string>& visited,
                int maxChemins) {
    if ((int)result.size() >= maxChemins) return;

    if (current == fin) {
        result.push_back(path);
        return;
    }

    for (const auto& voisin : graph.at(current)) {
        if (visited.find(voisin) == visited.end()) {
            visited.insert(voisin);
            path.push_back(voisin);
            dfsChemins(graph, voisin, fin, path, result, visited, maxChemins);
            path.pop_back();
            visited.erase(voisin);
        }
    }
}

void Fourmiliere::trouverTousChemins(const std::string& debut, const std::string& fin, int maxChemins) {
    chemins.clear();
    std::vector<std::string> cheminActuel = {debut};
    std::unordered_set<std::string> visited;
    visited.insert(debut);
    dfsChemins(graph, debut, fin, cheminActuel, chemins, visited, maxChemins);
}

// Trie les chemins du plus court au plus long
void Fourmiliere::trierCheminsParLongueur() {
    std::sort(chemins.begin(), chemins.end(), [](const std::vector<std::string>& a, const std::vector<std::string>& b){
        return a.size() < b.size();
    });
}

// Essaie de faire avancer la fourmi sur un chemin donné à sa position + 1
// Retourne true si mouvement effectué, false sinon
bool avancerFourmiSurChemin(Fourmi& f, const std::vector<std::string>& chemin,
                            std::unordered_map<std::string,int>& occupationSalles,
                            const std::unordered_map<std::string,int>& capacitesSalles,
                            const std::string& debut, const std::string& fin) {
    if (f.position >= (int)chemin.size() - 1) {
        f.arrivée = true;
        return false; // Déjà arrivé
    }

    std::string salleActuelle = chemin[f.position];
    std::string salleSuivante = chemin[f.position + 1];

    // Vérifier capacité
    if (salleSuivante == fin || occupationSalles[salleSuivante] < capacitesSalles.at(salleSuivante)) {
        // Libérer la salle actuelle sauf si départ ou arrivée
        if (salleActuelle != debut && salleActuelle != fin)
            occupationSalles[salleActuelle]--;

        // Occuper la nouvelle salle sauf départ ou arrivée
        if (salleSuivante != debut && salleSuivante != fin)
            occupationSalles[salleSuivante]++;

        f.position++;
        if (salleSuivante == fin)
            f.arrivée = true;
        return true;
    }
    return false;
}

void Fourmiliere::simulerFourmis(const std::string& debut, const std::string& fin, int nombreFourmis) {
    const int MAX_CHEMINS = 10; // Limite max chemins à rechercher
    trouverTousChemins(debut, fin, MAX_CHEMINS);
    if (chemins.empty()) {
        std::cout << "Aucun chemin trouvé de " << debut << " à " << fin << std::endl;
        return;
    }
    trierCheminsParLongueur();

    // Création des fourmis, chacune attribuée à un chemin (modulo nb chemins)
    std::vector<Fourmi> fourmis;
    for (int i=0; i < nombreFourmis; i++) {
        Fourmi f;
        f.id = i+1;
        f.cheminIdx = i % (int)chemins.size();
        f.position = 0;
        f.arrivée = false;
        fourmis.push_back(f);
    }

    // Initialiser occupation salles (toutes à 0)
    for (auto& [salle, _] : capacitesSalles) {
        occupationSalles[salle] = 0;
    }
    // Mettre toutes les fourmis au départ
    occupationSalles[debut] = nombreFourmis;

    int etape = 0;
    bool toutesArrivees = false;

    while (!toutesArrivees && etape <= 100) {
        etape++;
        std::vector<std::string> mouvements; // Stocke les descriptions des mouvements de chaque fourmi

        for (auto& f : fourmis) {
            if (f.arrivée) {
                mouvements.push_back("f" + std::to_string(f.id) + " est arrivee");
                continue;
            }

            std::string salleActuelle = chemins[f.cheminIdx][f.position];
            std::string salleSuivante = chemins[f.cheminIdx][f.position + 1];

            // Si la salle suivante est pleine
            if (salleSuivante != debut && salleSuivante != fin && occupationSalles[salleSuivante] >= capacitesSalles[salleSuivante]) {
                bool avanceAlternatif = false;
                // Recherche d'un chemin alternatif qui passe par la même salle actuelle
                for (int idxChemin = 0; idxChemin < static_cast<int>(chemins.size()); ++idxChemin) {
                    if (idxChemin == f.cheminIdx) continue; // On reste pas sur le même chemin

                    auto& cheminAlt = chemins[idxChemin];
                    auto it = std::find(cheminAlt.begin(), cheminAlt.end(), salleActuelle);
                    if (it != cheminAlt.end()) {
                        size_t posDansCheminAlt = std::distance(cheminAlt.begin(), it);
                        if (posDansCheminAlt + 1 < cheminAlt.size()) {
                            std::string salleSuivanteAlt = cheminAlt[posDansCheminAlt + 1];

                            if (salleSuivanteAlt != debut && salleSuivanteAlt != fin && occupationSalles[salleSuivanteAlt] >= capacitesSalles[salleSuivanteAlt]) {
                                continue; // Pas de place sur cette alternative
                            }

                            // On libère la salle actuelle sur le chemin précédent (si ni début ni fin)
                            if (salleActuelle != debut && salleActuelle != fin)
                                occupationSalles[salleActuelle]--;

                            // On occupe la salle suivante alternative (si ni début ni fin)
                            if (salleSuivanteAlt != debut && salleSuivanteAlt != fin)
                                occupationSalles[salleSuivanteAlt]++;

                            // Mise à jour position et chemin
                            int anciennePosition = f.position;
                            std::string ancienneSalle = chemins[f.cheminIdx][anciennePosition];
                            std::string nouvelleSalle = salleSuivanteAlt;

                            f.cheminIdx = idxChemin;
                            f.position = posDansCheminAlt + 1;

                            if (nouvelleSalle == fin)
                                f.arrivée = true;

                            avanceAlternatif = true;

                            mouvements.push_back("f" + std::to_string(f.id) + " avance (chemin alternatif) de " + ancienneSalle + " a " + nouvelleSalle);
                            break;
                        }
                    }
                }

                if (!avanceAlternatif) {
                    mouvements.push_back("f" + std::to_string(f.id) + " attend a " + salleActuelle);
                }
            } else {
                // Mouvement normal
                int anciennePosition = f.position;
                std::string ancienneSalle = chemins[f.cheminIdx][anciennePosition];
                std::string nouvelleSalle = salleSuivante;

                // Mise à jour occupation salles
                if (ancienneSalle != debut && ancienneSalle != fin)
                    occupationSalles[ancienneSalle]--;
                if (nouvelleSalle != debut && nouvelleSalle != fin)
                    occupationSalles[nouvelleSalle]++;

                f.position++;
                if (nouvelleSalle == fin)
                    f.arrivée = true;

                mouvements.push_back("f" + std::to_string(f.id) + " avance de " + ancienneSalle + " a " + nouvelleSalle);
            }
        }

        // Afficher la situation à chaque étape
        std::cout << "Etape " << etape << " :\n";
        for (auto& m : mouvements)
            std::cout << "  - " << m << "\n";

        // Vérification si toutes sont arrivées
        toutesArrivees = true;
        for (auto& f : fourmis) {
            if (!f.arrivée) {
                toutesArrivees = false;
                break;
            }
        }
    }
}
