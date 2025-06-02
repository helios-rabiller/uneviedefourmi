// ants.cpp
#include "ants.hpp"

void run_simulation() {
    Anthill anthill;

    // Définition des salles
    anthill.addRoom("S_v", 1000);
    anthill.addRoom("S1", 8);
    anthill.addRoom("S2", 4);
    anthill.addRoom("S3", 2);
    anthill.addRoom("S4", 4);
    anthill.addRoom("S5", 2);
    anthill.addRoom("S6", 4);
    anthill.addRoom("S7", 2);
    anthill.addRoom("S8", 5);
    anthill.addRoom("S9");
    anthill.addRoom("S10");
    anthill.addRoom("S11");
    anthill.addRoom("S12");
    anthill.addRoom("S13", 4);
    anthill.addRoom("S14", 2);
    anthill.addRoom("S_d", 1000);

    // Connexions
    anthill.addTunnel("S_v", "S1");
    anthill.addTunnel("S1", "S2");
    anthill.addTunnel("S1", "S6");
    anthill.addTunnel("S2", "S3");
    anthill.addTunnel("S2", "S5");
    anthill.addTunnel("S3", "S4");
    anthill.addTunnel("S4", "S_d");
    anthill.addTunnel("S5", "S4");
    anthill.addTunnel("S6", "S7");
    anthill.addTunnel("S6", "S8");
    anthill.addTunnel("S7", "S9");
    anthill.addTunnel("S7", "S10");
    anthill.addTunnel("S8", "S11");
    anthill.addTunnel("S8", "S12");
    anthill.addTunnel("S9", "S14");
    anthill.addTunnel("S10", "S14");
    anthill.addTunnel("S11", "S13");
    anthill.addTunnel("S12", "S13");
    anthill.addTunnel("S13", "S_d");
    anthill.addTunnel("S14", "S_d");

    // Ajout de fourmis
    anthill.addAnts(50);


    // Résolution
    anthill.solve();
}

void Anthill::solve() {
    std::vector<std::vector<std::string>> paths = findMultipleShortestPaths();
    std::vector<Ant> active_ants;

    for (int i = 1; i <= ants_count; ++i) {
        Ant ant;
        ant.id = i;
        ant.path = paths[(i - 1) % paths.size()];
        active_ants.push_back(ant);
    }

    std::map<std::string, std::set<int>> roomOccupancy;
    for (const auto& r : rooms) roomOccupancy[r.first] = {};
    for (auto& ant : active_ants) roomOccupancy[vestibule].insert(ant.id);

    int step = 1;
    bool all_arrived = false;
    while (!all_arrived) {
        all_arrived = true;
        std::cout << "+++ E " << step << " +++\n";
        std::set<int> moved_this_step;
        for (auto& ant : active_ants) {
            if (ant.current_step < ant.path.size() - 1) {
                std::string curr = ant.path[ant.current_step];
                std::string next = ant.path[ant.current_step + 1];

                bool can_move = (rooms[next].capacity > (int)roomOccupancy[next].size()) || next == dormitory;

                if (can_move && roomOccupancy[curr].count(ant.id)) {
                    roomOccupancy[curr].erase(ant.id);
                    roomOccupancy[next].insert(ant.id);
                    ant.current_step++;
                    moved_this_step.insert(ant.id);
                    std::cout << "f" << ant.id << " - " << curr << " - " << next << "\n";
                    all_arrived = false;
                } else if (ant.current_step < ant.path.size() - 1) {
                    all_arrived = false;
                }
            }
        }
        step++;
    }
}

std::vector<std::vector<std::string>> Anthill::findMultipleShortestPaths() {
    std::vector<std::vector<std::string>> paths;
    std::queue<std::vector<std::string>> q;
    q.push({vestibule});

    int shortest_len = -1;

    while (!q.empty()) {
        auto path = q.front(); q.pop();
        std::string last = path.back();

        if (shortest_len != -1 && path.size() > shortest_len) break;

        if (last == dormitory) {
            if (shortest_len == -1) shortest_len = path.size();
            paths.push_back(path);
            continue;
        }

        for (const std::string& neighbor : rooms[last].neighbors) {
            if (std::find(path.begin(), path.end(), neighbor) == path.end()) {
                std::vector<std::string> new_path = path;
                new_path.push_back(neighbor);
                q.push(new_path);
            }
        }
    }

    return paths;
}
