#include "Database.h"
#include "config.h"

int main() {
    try {
        Database db(DB_HOST, DB_USER, DB_PASS, DB_NAME);
        db.executeAndPrint("SELECT * FROM users");
    } catch (sql::SQLException& e) {
        cerr << "Błąd SQL: " << e.what() << endl;
        return 1;
    }
    return 0;
}