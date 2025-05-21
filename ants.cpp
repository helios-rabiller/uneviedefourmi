#include "ants.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <limits>
#include <algorithm>

int numAnts = 0;
std::unordered_map<std::string, Room> rooms;
// Chargement du fichier
// 🔽 C'est ici que tu ajoutes les voisins
void AntColony::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    bool readingRooms = true;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (line.rfind("f=", 0) == 0) {
            numAnts = std::stoi(line.substr(2));
        } else if (line.find('-') != std::string::npos) {
            readingRooms = false;
            size_t dash = line.find('-');
            std::string from = line.substr(0, dash - 1);
            std::string to = line.substr(dash + 2);

            // 🔽 C'est ici que tu ajoutes les voisins
            rooms[from].neighbors[to] = 1;
            rooms[to].neighbors[from] = 1;
        } else if (readingRooms) {
            // Si on lit encore les salles (avant les '-')
            rooms[line] = Room(line);
        }
    }
}


Room& AntColony::getOrCreateRoom(const std::string& name) {
    if (rooms.find(name) == rooms.end()) {
        rooms.emplace(name, Room(name));
    }
    return rooms[name];
}

void AntColony::displayGraph() const {
    for (const auto& [name, room] : rooms) {
        std::cout << "Room " << name << " (capacity=" << room.capacity << ") connected to: ";
        for (const auto& n : room.neighbors) {
            std::cout << n << " ";
        }
        std::cout << "\n";
    }
}

// Heuristique simple : différence lexicographique (à remplacer plus tard par autre critère)
int AntColony::heuristic(const std::string& a, const std::string& b) const {
    return std::abs(static_cast<int>(a[0]) - static_cast<int>(b[0]));
}

std::vector<std::string> AntColony::findPathAStar(const std::string& start, const std::string& goal) {
    std::unordered_map<std::string, std::string> cameFrom;
    std::unordered_map<std::string, int> gScore, fScore;
    auto comp = [&](const std::string& lhs, const std::string& rhs) {
        return fScore[lhs] > fScore[rhs];
    };

    for (const auto& [name, _] : rooms) {
        gScore[name] = std::numeric_limits<int>::max();
        fScore[name] = std::numeric_limits<int>::max();
    }

    gScore[start] = 0;
    fScore[start] = heuristic(start, goal);

    std::priority_queue<std::string, std::vector<std::string>, decltype(comp)> openSet(comp);
    openSet.push(start);

    while (!openSet.empty()) {
        std::string current = openSet.top();
        openSet.pop();

        if (current == goal) {
            std::vector<std::string> path;
            while (current != start) {
                path.push_back(current);
                current = cameFrom[current];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const std::string& neighbor : rooms[current].neighbors) {
            int tentativeG = gScore[current] + 1;

            // Bonus : intègre la capacité en pénalité (- si grande capacité)
            tentativeG += (10 - rooms[neighbor].capacity);

            if (tentativeG < gScore[neighbor]) {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentativeG;
                fScore[neighbor] = tentativeG + heuristic(neighbor, goal);
                openSet.push(neighbor);
            }
        }
    }

    return {}; // chemin non trouvé
}