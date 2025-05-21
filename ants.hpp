#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm> 
#include <limits>    
#include <set>      

struct Room {
    std::string name;
    int capacity;
    std::unordered_map<std::string, int> neighbors; // voisins et distances

    Room() : name(""), capacity(1) {}
    Room(std::string n, int c = 1) : name(std::move(n)), capacity(c) {}
};


class AntColony {
public:
    void loadFromFile(const std::string& filename);

    void displayGraph() const;

    std::vector<std::string> findPathAStar(const std::string& start, const std::string& goal);

private:
    std::unordered_map<std::string, Room> rooms;
    int antCount = 0;

    // Heuristique basique pour A* (à adapter plus tard)
    int heuristic(const std::string& a, const std::string& b) const;

    // Ajouter ou récupérer une salle
    Room& getOrCreateRoom(const std::string& name);
};
