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

    void solve();

private:
    std::map<std::string, Room> rooms;
    std::string vestibule = "S_v";
    std::string dormitory = "S_d";
    int ants_count = 0;

    std::vector<std::vector<std::string>> findMultipleShortestPaths();
};

void run_simulation();

#endif
