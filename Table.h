#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class Table {
public:
    std::unordered_map<std::string, std::vector<std::string>> data;
    std::vector<std::string> columns;
    std::unordered_map<std::string, std::string> index;

    Table() = default;
    void insertRow(const std::vector<std::string>& row);
    void print();
};

#endif
