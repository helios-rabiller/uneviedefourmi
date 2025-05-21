#include "ants.hpp"
#include <iostream>

int main() {
    AntColony colony;

    std::string filename;
    std::cout << "Choisissez le niveau à charger (ex: niveau1.txt): ";
    std::cin >> filename;

    colony.loadFromFile(filename);
    colony.displayGraph();

    std::string start = "Sv";
    std::string goal = "Sd";

    std::vector<std::string> path = colony.findPathAStar(start, goal);
    if (path.empty()) {
        std::cout << "Aucun chemin trouvé de " << start << " à " << goal << "\n";
    } else {
        std::cout << "Chemin trouvé : ";
        for (const std::string& room : path) {
            std::cout << room << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
