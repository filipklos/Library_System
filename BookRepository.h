#pragma once
#include <vector>
#include "BaseRepository.h"
#include "Book.h"

class BookRepository : public BaseRepository {
private:
    static BookRepository* instance;
    BookRepository(Database& db);   

public:
    static BookRepository& getInstance(Database& db);

    void add(const Book& book);
    void remove(int id);
    std::vector<Book> getAll();
    void displayAll() const;     
};
