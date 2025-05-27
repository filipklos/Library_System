#include "Book.h"

Book::Book() : id(0), title(""), author(""), year(0), genre("") {}

Book::Book(int id, const std::string& title,
           const std::string& author, int year, const std::string& genre)
    : id(id), title(title), author(author), year(year), genre(genre) {} 



int Book::getId() const { return id; }
const std::string& Book::getTitle() const { return title; }
const std::string& Book::getAuthor() const { return author; }
int Book::getYear() const { return year; }
const std::string& Book::getGenre() const { return genre; }

std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << book.id << " " << book.title << " " << book.author << " " << book.year << " " << book.genre;
    return os;
}
