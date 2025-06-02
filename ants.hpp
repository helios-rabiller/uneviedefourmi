// ants.hpp
#ifndef ANTS_HPP
#define ANTS_HPP

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <iostream>
#include <algorithm>

struct Room {
    std::string name;
    int capacity = 1; // default 1, unless vestibule or dormitory
    std::vector<std::string> neighbors;
};

struct Ant {
    int id;
    std::vector<std::string> path;
    int current_step = 0;
};

class Anthill {
public:
    void addRoom(const std::string& name, int capacity = 1) {
        rooms[name].name = name;
        rooms[name].capacity = capacity;
    }

    void addTunnel(const std::string& from, const std::string& to) {
        rooms[from].neighbors.push_back(to);
    }

    void addAnts(int count) {
        ants_count = count;
    }

    void solve() {
        std::vector<std::vector<std::string>> paths = findMultipleShortestPaths();
        std::vector<Ant> active_ants;

        // Assign paths to ants in round robin
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

private:
    std::map<std::string, Room> rooms;
    std::string vestibule = "S_v";
    std::string dormitory = "S_d";
    int ants_count = 0;

    // Generate all shortest paths from vestibule to dormitory (BFS variant)
    std::vector<std::vector<std::string>> findMultipleShortestPaths() {
        std::vector<std::vector<std::string>> paths;
        std::queue<std::vector<std::string>> q;
        std::set<std::string> visited;
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
                if (std::find(path.begin(), path.end(), neighbor) == path.end()) { // avoid cycles
                    std::vector<std::string> new_path = path;
                    new_path.push_back(neighbor);
                    q.push(new_path);
                }
            }
        }

        return paths;
    }
};

#endif
