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

    bool add(const Book& book);
    bool remove(int id);
    std::vector<Book> getAll();
    void displayAll() const;
    bool exists(int id) const;     
};
