#include <iostream>
#include "Database.h"
using namespace std;

int main() {
    Database db;

    db.createTable("students", {"id", "name", "age"});
    db.createTable("courses", {"course_id", "course_name"});

    db.insertInto("students", {"1", "John", "25"});
    db.insertInto("students", {"2", "Alice", "30"});
    db.insertInto("courses", {"101", "Math"});
    db.insertInto("courses", {"102", "Science"});

    db.createIndex("age_index", "students", "age");

    db.selectFrom("students");
    db.selectFrom("courses");

    db.update("students", "age", "26", [](const string& age) { return age == "25"; });

    db.selectFrom("students");

    db.alterTableAddColumn("students", "favorite_color");

    db.insertInto("students", {"3", "Sam", "22", "Blue"});

    db.dropTable("courses");

    db.createView("student_view", "SELECT * FROM students");

    db.dropView("student_view");

    db.insertIntoSelect("students", {"id", "name", "age", "favorite_color"}, "SELECT 4, 'Bill', 23, 'Red' UNION SELECT 5, 'Sophia', 27, 'Red'");

    db.truncateTable("students");

    db.dropIndex("age_index");

    db.insertInto("students", {"4", "Bill", "23", "Red"});
    db.insertInto("students", {"5", "Sophia", "27", "Red"});

    db.printTable("students");

    return 0;
}
