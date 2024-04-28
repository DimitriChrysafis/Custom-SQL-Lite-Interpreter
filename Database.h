#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include "Table.h"

class Database {
private:
    std::unordered_map<std::string, Table> tables;
    std::unordered_map<std::string, std::string> views; // Add views map

public:
    void createTable(const std::string& tableName, const std::vector<std::string>& columns);
    void insertInto(const std::string& tableName, const std::vector<std::string>& values);
    void selectFrom(const std::string& tableName);
    void deleteFrom(const std::string& tableName, const std::function<bool(const std::string&)>& condition);
    void update(const std::string& tableName, const std::string& columnToUpdate,
                const std::string& newValue, const std::function<bool(const std::string&)>& condition);
    void alterTableAddColumn(const std::string& tableName, const std::string& newColumnName);
    void dropTable(const std::string& tableName);
    void createIndex(const std::string& indexName, const std::string& tableName, const std::string& columnName);
    void dropIndex(const std::string& indexName);
    void createView(const std::string& viewName, const std::string& query);
    void dropView(const std::string& viewName);
    void insertIntoSelect(const std::string& tableName, const std::vector<std::string>& columns,
                          const std::string& selectQuery);
    void truncateTable(const std::string& tableName);
    void printTable(const std::string& tableName);
};

#endif /* DATABASE_H */
