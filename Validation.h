#pragma once
#include <string>
#include "Database.h"

class Validator {
public:
    // Sprawdza, czy napis jest poprawnej długości (3-100 znaków)
    static bool isStringValid(const std::string& str) {
        return str.size() >= 3 && str.size() <= 100;
    }
    // Sprawdza, czy istnieje użytkownik o podanym ID
    static bool userExists(Database& db, int userId) {
        auto res = db.executeQuery(
            "SELECT id FROM users WHERE id = " + std::to_string(userId)
        );
        return res->next();
    }
    // Sprawdza, czy istnieje książka o podanym ID
    static bool bookExists(Database& db, int bookId) {
        auto res = db.executeQuery(
            "SELECT id FROM books WHERE id = " + std::to_string(bookId)
        );
        return res->next();
    }
    // Sprawdza, czy książka jest dostępna 
    static bool bookAvailable(Database& db, int bookId) {
        auto res = db.executeQuery(
            "SELECT id FROM loans WHERE book_id = " + std::to_string(bookId) +
            " AND return_date IS NULL"
        );
        return !res->next(); // jeśli nie znaleziono aktywnego wypożyczenia -> dostępna
    }
    // Sprawdza, czy użytkownik ma aktywne wypożyczenia
    static bool userHasActiveLoans(Database& db, int userId) {
        auto res = db.executeQuery(
            "SELECT id FROM loans WHERE user_id = " + std::to_string(userId) +
            " AND return_date IS NULL"
        );
        return res->next(); // jeśli znaleziono, użytkownik ma aktywne wypożyczenia
    }
    // Sprawdza, czy książka jest wypożyczona 
    static bool bookIsBorrowed(Database& db, int bookId) {
        auto res = db.executeQuery(
            "SELECT id FROM loans WHERE book_id = " + std::to_string(bookId) +
            " AND return_date IS NULL"
        );
        return res->next(); // jeśli znaleziono, książka jest wypożyczona
    }
};
