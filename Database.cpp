#include "Database.h"
using namespace std;

void Database::createTable(const string& tableName, const vector<string>& columns) {
    Table newTable;
    newTable.columns = columns;
    tables[tableName] = newTable;
    cout << "Table '" << tableName << "' created successfully." << endl;
}

void Database::insertInto(const string& tableName, const vector<string>& values) {
    if (tables.find(tableName) != tables.end()) {
        tables[tableName].insertRow(values);
        cout << "Inserted into table '" << tableName << "' successfully." << endl;
    } else {
        cerr << "Table '" << tableName << "' does not exist." << endl;
    }
}

void Database::selectFrom(const string& tableName) {
    if (tables.find(tableName) != tables.end()) {
        cout << "Data from table '" << tableName << "':" << endl;
        tables[tableName].print();
    } else {
        cerr << "Table '" << tableName << "' does not exist." << endl;
    }
}

void Database::deleteFrom(const string& tableName,
                          const function<bool(const string&)>& condition) {
    if (tables.find(tableName) != tables.end()) {
        auto& table = tables[tableName];
        vector<string> rowsToRemove;
        for (const auto& row : table.data[table.columns[0]]) {
            if (condition(row)) {
                rowsToRemove.push_back(row);
            }
        }
        for (const auto& row : rowsToRemove) {
            for (auto& col : table.columns) {
                table.data[col].erase(
                        remove(table.data[col].begin(), table.data[col].end(), row), table.data[col].end());
            }
        }
        cout << "Deleted from table '" << tableName << "' successfully." << endl;
    } else {
        cerr << "Table '" << tableName << "' does not exist." << endl;
    }
}

void Database::update(const string& tableName, const string& columnToUpdate,
                      const string& newValue, const function<bool(const string&)>& condition) {
    if (tables.find(tableName) != tables.end()) {
        auto& table = tables[tableName];
        for (size_t i = 0; i < table.data[columnToUpdate].size(); ++i) {
            if (condition(table.data[columnToUpdate][i])) {
                table.data[columnToUpdate][i] = newValue;
            }
        }
        cout << "Updated table '" << tableName << "' successfully." << endl;
    } else {
        cerr << "Table '" << tableName << "' does not exist." << endl;
    }
}

void Database::alterTableAddColumn(const string& tableName, const string& newColumnName) {
    if (tables.find(tableName) != tables.end()) {
        auto& table = tables[tableName];
        table.columns.push_back(newColumnName);
        for (auto& col : table.columns) {
            table.data[col].resize(table.data[table.columns[0]].size());
        }
        cout << "Added column '" << newColumnName << "' to table '" << tableName << "' successfully." << endl;
    } else {
        cerr << "Table '" << tableName << "' does not exist." << endl;
    }
}

void Database::dropTable(const string& tableName) {
    if (tables.find(tableName) != tables.end()) {
        tables.erase(tableName);
        cout << "Dropped table '" << tableName << "' successfully." << endl;
    } else {
        cerr << "Table '" << tableName << "' does not exist." << endl;
    }
}

void Database::createIndex(const string& indexName, const string& tableName, const string& columnName) {
    if (tables.find(tableName) != tables.end()) {
        if (tables[tableName].data.find(columnName) != tables[tableName].data.end()) {
            tables[tableName].index[indexName] = columnName;
            cout << "Index '" << indexName << "' created successfully on table '" << tableName << "' for column '" << columnName << "'." << endl;
        } else {
            cerr << "Column '" << columnName << "' does not exist in table '" << tableName << "'." << endl;
        }
    } else {
        cerr << "Table '" << tableName << "' does not exist." << endl;
    }
}

void Database::dropIndex(const string& indexName) {
    bool found = false;
    for (auto& table : tables) {
        auto& indexMap = table.second.index;
        if (indexMap.find(indexName) != indexMap.end()) {
            indexMap.erase(indexName);
            found = true;
        }
    }
    if (found) {
        cout << "Index '" << indexName << "' dropped successfully." << endl;
    } else {
        cerr << "Index '" << indexName << "' not found." << endl;
    }
}

void Database::createView(const string& viewName, const string& query) {
    views[viewName] = query;
    cout << "View '" << viewName << "' created successfully." << endl;
}

void Database::dropView(const string& viewName) {
    if (views.find(viewName) != views.end()) {
        views.erase(viewName);
        cout << "View '" << viewName << "' dropped successfully." << endl;
    } else {
        cerr << "View '" << viewName << "' not found." << endl;
    }
}

void Database::insertIntoSelect(const string& tableName, const vector<string>& columns,
                                const string& selectQuery) {
    vector<vector<string>> selectResults;

    // Execute the selectQuery and store the results in selectResults

    for (const auto& row : selectResults) {
        if (row.size() == columns.size()) {
            vector<string> values;
            for (size_t i = 0; i < columns.size(); ++i) {
                values.push_back(row[i]);
            }
            insertInto(tableName, values);
        } else {
            cerr << "Number of columns in select query result does not match the number of columns specified." << endl;
            return;
        }
    }
    cout << "Data inserted into table '" << tableName << "' from SELECT query successfully." << endl;
}

void Database::truncateTable(const string& tableName) {
    if (tables.find(tableName) != tables.end()) {
        tables[tableName].data.clear();
        cout << "Table '" << tableName << "' truncated successfully." << endl;
    } else {
        cerr << "Table '" << tableName << "' does not exist." << endl;
    }
}

void Database::printTable(const string& tableName) {
    if (tables.find(tableName) != tables.end()) {
        tables[tableName].print();
    } else {
        cerr << "Table '" << tableName << "' does not exist." << endl;
    }
}
