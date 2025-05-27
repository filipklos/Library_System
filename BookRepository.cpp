#include "BookRepository.h"
#include <iostream>
#include <sstream>

BookRepository* BookRepository::instance = nullptr;

BookRepository::BookRepository(Database& db) : BaseRepository(db) {}

BookRepository& BookRepository::getInstance(Database& db) {
    if (!instance) instance = new BookRepository(db);
    return *instance;
}

void BookRepository::add(const Book& book) {
    std::ostringstream oss;
    oss << "INSERT INTO books (title, author, year, genre) VALUES ('"
        << book.getTitle() << "', '"
        << book.getAuthor() << "', "
        << book.getYear() << ", '"
        << book.getGenre() << "')";
    db.executeUpdate(oss.str());
}

void BookRepository::remove(int id) {
    std::ostringstream oss;
    oss << "DELETE FROM books WHERE id = " << id;
    db.executeUpdate(oss.str());
}

std::vector<Book> BookRepository::getAll() {
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
}

void BookRepository::displayAll() const {
    auto books = const_cast<BookRepository*>(this)->getAll();
    std::cout << "--- Lista książek ---\n";
    for (auto& b : books) {
        std::cout << b << "\n";
    }
}
