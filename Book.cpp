#include "Book.h"

Book::Book() : id(0), title(""), author(""), year(0) {}

Book::Book(int id, const std::string& title,
           const std::string& author, int year)
    : id(id), title(title), author(author), year(year) {}  

int Book::getId() const       { return id; }
const std::string& Book::getTitle() const  { return title; }
const std::string& Book::getAuthor() const { return author; }
int Book::getYear() const     { return year; }            

std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << book.id <<" " << book.title << " " << book.author << " " << book.year;
    return os;
}


