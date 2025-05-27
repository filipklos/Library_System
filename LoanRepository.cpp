#include "LoanRepository.h"
#include <iostream>

LoanRepository* LoanRepository::instance = nullptr;

LoanRepository::LoanRepository(Database& db)
    : BaseRepository(db) {}


LoanRepository& LoanRepository::getInstance(Database& db) {
    if (!instance) {
        instance = new LoanRepository(db);
    }
    return *instance;
}

void LoanRepository::borrowBook(int userId, int bookId) {
    
    //Sprawdzenie istnienia użytkownika
    auto resUser = db.executeQuery(
        "SELECT id FROM users WHERE id = " + std::to_string(userId)
    );
    if (!resUser->next()) {
        std::cout << "Użytkownik o ID=" << userId << " nie istnieje.\n";
        return;
    }


    //Sprawdzenie istnienia książki
    auto resBook = db.executeQuery(
        "SELECT id FROM books WHERE id = " + std::to_string(bookId)
    );
    if (!resBook->next()) {
        std::cout << "Książka o ID=" << bookId << " nie istnieje.\n";
        return;
    }



    //Sprawdzenie dostępności książki
    auto resLoan = db.executeQuery(
        "SELECT id FROM loans WHERE book_id = " + std::to_string(bookId) +
        " AND return_date IS NULL"
    );
    if (resLoan->next()) {
        std::cout << "Książka o ID=" << bookId << " jest już wypożyczona.\n";
        return;
    }

    //Dodanie wypożyczenia
    db.executeUpdate(
        "INSERT INTO loans (user_id, book_id, borrow_date) VALUES (" +
        std::to_string(userId) + ", " + std::to_string(bookId) + ", CURDATE())"
    );
    std::cout << "Wypożyczenie zostało dodane.\n";
}

void LoanRepository::returnBook(int bookId) {
    //Znalezienie wypożyczonej książki
    auto res = db.executeQuery(
        "SELECT id FROM loans WHERE book_id = " + std::to_string(bookId) +
        " AND return_date IS NULL"
    );
    if (!res->next()) {
        std::cout << "Brak aktywnego wypożyczenia dla książki ID=" << bookId << "\n";
        return;
    }
    int loanId = res->getInt("id");

    //Ustawnie daty zwrotu
    db.executeUpdate(
        "UPDATE loans SET return_date = CURDATE() WHERE id = " +
        std::to_string(loanId)
    );
    std::cout << "Książka została zwrócona.\n";
}

void LoanRepository::displayActiveLoans() const {
    auto res = db.executeQuery(
        "SELECT u.name, u.surname, b.title, l.borrow_date "
        "FROM loans l "
        "JOIN users u ON l.user_id = u.id "
        "JOIN books b ON l.book_id = b.id "
        "WHERE l.return_date IS NULL"
    );
    std::cout << "--- Aktywne wypożyczenia ---\n";
    while (res->next()) {
        std::cout
            << res->getString("name") << " " << res->getString("surname")
            << " | " << res->getString("title")
            << " | Wypożyczono: " << res->getString("borrow_date")
            << " | Zwrot: brak\n";
    }
}

void LoanRepository::displayLoanHistory() const {
    auto res = db.executeQuery(
        "SELECT u.name, u.surname, b.title, l.borrow_date, l.return_date "
        "FROM loans l "
        "JOIN users u ON l.user_id = u.id "
        "JOIN books b ON l.book_id = b.id"
    );
    std::cout << "--- Historia wypożyczeń ---\n";
    while (res->next()) {
        std::string ret = res->isNull("return_date")
            ? "brak"
            : res->getString("return_date");
        std::cout
            << res->getString("name") << " " << res->getString("surname")
            << " | " << res->getString("title")
            << " | Wypożyczenie: " << res->getString("borrow_date")
            << " | Zwrot: " << ret << "\n";
    }
}
