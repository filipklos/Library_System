#pragma once
#include "BaseRepository.h"
#include "User.h"
#include <vector>

class UserRepository : public BaseRepository {
private:
    // Singleton
    static UserRepository* instance;
    
    // Wektor przechowujący użytkowników
    std::vector<User> users;
    
    // Prywatny konstruktor (wzorzec Singleton)
    UserRepository(Database& db);
    
    // Metoda ładująca użytkowników z bazy do wektora
    void loadUsers();
    
public:
    // Usunięcie konstruktora kopiującego i operatora przypisania
    UserRepository(const UserRepository&) = delete;
    UserRepository& operator=(const UserRepository&) = delete;
    
    // Destruktor
    ~UserRepository() override;
    
    // Metoda dostępu do jedynej instancji
    static UserRepository* getInstance(Database& db);
    
    bool add(const User& user);
    vector<User> getAll();
    
    // Wyświetlanie wszystkich użytkowników
    void displayAll();
    
    // Odświeżanie danych z bazy
    void refresh();
};