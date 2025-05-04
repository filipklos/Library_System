#include "Database.h"
#include "config.h"
#include "User.h"
#include "UserRepository.h"
#include <limits>

void displayMenu() {
    cout << endl << "----System Biblioteczny----" << endl;
    cout << "1. Dodaj użytkownika" << endl;
    cout << "2. Usuń użytkownika" << endl;
    cout << "3. Wyświetl listę użytkowników" << endl;
    cout << "0. Wyjdź" << endl;
    cout << "Wybierz opcję: ";
}

int main() {
    try {
        // Utworzenie połączenia z bazą danych
        Database db(DB_HOST, DB_USER, DB_PASS, DB_NAME);
        UserRepository* repo = UserRepository::getInstance(db);
        
        int choice = -1;
        
        do {
            displayMenu();
            cin >> choice;
            
            // Obsługa nieprawidłowego wejścia
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Nieprawidłowy wybór. Spróbuj ponownie." << endl;
                continue;
            }
            
            switch (choice) {
                case 1:
                {
                    // Dodawanie użytkownika
                    string name, surname;
                    cout << endl << "Dodawanie nowego użytkownika:" << endl;
                    cout << "Podaj imię: ";
                    cin >> name;
                    cout << "Podaj nazwisko: ";
                    cin >> surname;
                    
                    User newUser(name, surname);
                    
                    if (repo->add(newUser))
                    {
                        cout << "Użytkownik dodany pomyślnie!" << endl;
                    } else
                    {
                        cout << "Błąd podczas dodawania użytkownika!" << endl;
                    }
                    break;
                }
                case 2:
                    // Usuwanie użytkownika
                    int id;
                    cout << endl << "Lista użytkowników:" << endl;
                    repo->displayAll();

                    cout << endl << "Usuwanie użytkownika:" << endl;
                    cout << "Podaj ID użytkownika do usunięcia: ";
                    cin >> id;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Nieprawne ID (to nie jest liczba)." << endl;
                        break;
                    }
                    // Walidacja istnienia w repozytorium
                    if (!repo->exists(id))
                    {
                        cout << "Użytkownik o ID= " << id << " nie istnieje." << endl;
                        break;
                    }
                    if (repo->remove(id))
                    {
                        cout << "Użytkownik usunięty pomyślnie!" << endl;
                    } else
                    {
                        cout << "Błąd podczas usuwania użytkownika!" << endl;
                    }
                    break;
                
                case 3:
                    // Wyświetlanie użytkowników
                    cout << endl << "Lista użytkowników:" << endl;
                    repo->displayAll();
                    break;

                case 0:
                    cout << "Zamykanie aplikacji..." << endl;
                    break;

                default:
                    cout << "Nieznana opcja. Spróbuj ponownie." << endl;
            }
            
        } while (choice != 0);
        
    } catch (sql::SQLException& e)
    {
        cerr << "Błąd SQL: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}