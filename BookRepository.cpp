#include "BookRepository.h"
#include <iostream>
#include <sstream>

BookRepository* BookRepository::instance = nullptr;

BookRepository::BookRepository(Database& db) : BaseRepository(db) {}

BookRepository& BookRepository::getInstance(Database& db) {
    if (!instance) {
        instance = new BookRepository(db);
    }
    return *instance;
}

bool BookRepository::add(const Book& book)
{
    try
    {
        std::ostringstream oss;
        oss << "INSERT INTO books (title, author, year, genre) VALUES ('"
            << book.getTitle() << "', '"
            << book.getAuthor() << "', "
            << book.getYear() << ", '"
            << book.getGenre() << "')";
        db.executeUpdate(oss.str());
        return true;
    } catch (sql::SQLException& e)
    {
        cerr << "Błąd podczas dodawania użytkownika: " << e.what() << endl;
        return false;
    }
}

bool BookRepository::remove(int id) {
    try
    {
        std::ostringstream oss;
        oss << "DELETE FROM books WHERE id = " << id;
        db.executeUpdate(oss.str());
        return true;
    } catch (sql::SQLException& e)
    {
        cerr << "Błąd podczas usuwania książki: " << e.what() << endl;
        return false;
    }
}

bool BookRepository::exists(int id) const {
    try
    {
        auto res = db.executeQuery(
            "SELECT id FROM books WHERE id = " + std::to_string(id)
        );
        return res->next();
    } catch (sql::SQLException& e)
    {
        cerr << "Błąd podczas sprawdzania istnienia książki: " << e.what() << endl;
        return false;
    }
}

std::vector<Book> BookRepository::getAll() {
    try
    {
        std::vector<Book> books;
        auto res = db.executeQuery("SELECT id, title, author, year, genre FROM books");
        while (res->next()) {
            books.emplace_back(
                res->getInt("id"),
                res->getString("title"),
                res->getString("author"),
                res->getInt("year"),
                res->getString("genre")
            );
        }
        return books;
    } catch (sql::SQLException& e)
    {
        cerr << "Błąd podczas pobierania książek: " << e.what() << endl;
        return {};
    }
}

void BookRepository::displayAll() const {
    try
    {
        auto books = const_cast<BookRepository*>(this)->getAll();
        std::cout << "ID | Tytuł | Autor | Rok | Gatunek" << std::endl;
        std::cout << "-----------------------------------" << std::endl;
        for (auto& b : books) {
            std::cout << b << std::endl;
        }
    } catch (sql::SQLException& e)
    {
        cerr << "Błąd podczas wyświetlania listy książek: " << e.what() << endl;
    }
}
