#include "UserRepository.h"
#include <sstream>

// Inicjalizacja statycznej zmiennej
UserRepository* UserRepository::instance = nullptr;

// Prywatny konstruktor
UserRepository::UserRepository(Database& db) : BaseRepository(db) {
}

// Destruktor
UserRepository::~UserRepository() {
}

// Implementacja Singletona
UserRepository* UserRepository::getInstance(Database& db) {
    if (instance == nullptr) {
        instance = new UserRepository(db);
    }
    return instance;
}

// Dodawanie użytkownika
bool UserRepository::add(const User& user) {
    try {
        stringstream query;
        query << "INSERT INTO users (name, surname) VALUES ('"
              << user.getName() << "', '" 
              << user.getSurname() << "')";
        
        db.executeUpdate(query.str());
        return true;
    } catch (sql::SQLException& e) {
        cerr << "Błąd podczas dodawania użytkownika: " << e.what() << endl;
        return false;
    }
}
