#include "Table.h"

void Table::insertRow(const std::vector<std::string>& row) {
    for (size_t i = 0; i < row.size(); ++i) {
        data[columns[i]].push_back(row[i]);
    }
}

void Table::print() {
    for (auto& col : columns) {
        std::cout << col << "\t";
    }
    std::cout << std::endl;
    for (size_t i = 0; i < data[columns[0]].size(); ++i) {
        for (auto& col : columns) {
            std::cout << data[col][i] << "\t";
        }
        std::cout << std::endl;
    }
}
