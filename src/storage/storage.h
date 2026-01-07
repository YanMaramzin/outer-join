#pragma once
#include <map>
#include <string>
#include <stdexcept>

struct Storage {
    std::map<int, std::string> A;
    std::map<int, std::string> B;

    std::map<int, std::string>& table(char name) {
        if (name == 'A') return A;
        if (name == 'B') return B;
        throw std::runtime_error("unknown table");
    }

    void truncate(char name) {
        table(name).clear();
    }

    void insert(char name, int id, const std::string& value) {
        auto& t = table(name);
        if (t.contains(id))
            throw std::runtime_error("duplicate " + std::to_string(id));
        t[id] = value;
    }
};
