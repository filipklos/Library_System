#include "Database.h"
#include "config.h"
#include "User.h"
#include "UserRepository.h"

int main() {
    try {
        // Utworzenie połączenia z bazą danych
        Database db(DB_HOST, DB_USER, DB_PASS, DB_NAME);

        // Wyświetlenie obecnych użytkowników
        cout << "Aktualni użytkownicy:" << endl;
        db.executeAndPrint("SELECT * FROM users");
        cout << endl;

        // Pobranie danych nowego użytkownika
        string name, surname;
        cout << "Dodawanie nowego użytkownika:" << endl;
        cout << "Podaj imię: ";
        cin >> name;
        cout << "Podaj nazwisko: ";
        cin >> surname;

        // Utworzenie użytkownika
        User newUser(name, surname);

        // Dodanie użytkownika do bazy danych
        UserRepository* repo = UserRepository::getInstance(db);

        if (repo->add(newUser)) {
            cout << "Użytkownik dodany pomyślnie!" << endl;
                    
            cout << endl << "Zaktualizowana lista użytkowników:" << endl;
            db.executeAndPrint("SELECT * FROM users");
        } else {
            cout << "Błąd podczas dodawania użytkownika!" << endl;
        }

    } catch (sql::SQLException& e) {
        cerr << "Błąd SQL: " << e.what() << endl;
        return 1;
    }
    return 0;
}