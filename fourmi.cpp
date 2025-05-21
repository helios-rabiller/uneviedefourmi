#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

void trouver_tous_les_chemins(
    unordered_map<string, vector<string>>& graphe,
    const string& courant,
    const string& arrivee,
    vector<string>& chemin_actuel,
    vector<vector<string>>& tous_les_chemins,
    unordered_map<string, bool>& visite
) {
    visite[courant] = true;
    chemin_actuel.push_back(courant);

    if (courant == arrivee) {
        tous_les_chemins.push_back(chemin_actuel);
    } else {
        for (const string& voisin : graphe[courant]) {
            if (!visite[voisin]) {
                trouver_tous_les_chemins(graphe, voisin, arrivee, chemin_actuel, tous_les_chemins, visite);
            }
        }
    }

    chemin_actuel.pop_back();
    visite[courant] = false;
}

int main() {
    unordered_map<string, vector<string>> graphe = {
        {"Sv", {"S1"}},
        {"S1", {"S2", "S6"}},
        {"S2", {"S3", "S5"}},
        {"S3", {"S4"}},
        {"S4", {"Sd"}},
        {"S5", {"S4"}},
        {"S6", {"S7", "S8"}},
        {"S7", {"S9", "S10"}},
        {"S8", {"S11", "S12"}},
        {"S9", {"S14"}},
        {"S10", {"S14"}},
        {"S11", {"S13"}},
        {"S12", {"S13"}},
        {"S13", {"Sd"}},
        {"S14", {"Sd"}},
        {"Sd", {}}
    };

    string depart = "Sv";
    string arrivee = "Sd";

    vector<vector<string>> tous_les_chemins;
    vector<string> chemin_actuel;
    unordered_map<string, bool> visite;

    trouver_tous_les_chemins(graphe, depart, arrivee, chemin_actuel, tous_les_chemins, visite);

    if (tous_les_chemins.empty()) {
        cout << "Aucun chemin trouvé de " << depart << " à " << arrivee << endl;
    } else {
        sort(tous_les_chemins.begin(), tous_les_chemins.end(),
            [](const vector<string>& a, const vector<string>& b) {
                return a.size() < b.size();
            });

        for (const auto& chemin : tous_les_chemins) {
            cout << "Chemin (" << chemin.size() << " étapes) :" << endl;
            for (const string& noeud : chemin) {
                cout << "  La fourmi est dans " << noeud << endl;
            }
            cout << "  La fourmi est arrivée" << endl << endl;
        }
    }

    return 0;
}
