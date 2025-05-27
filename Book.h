#pragma once
#include <string>
#include <iostream>

class Book {
private:
    int id;
    std::string title;
    std::string author;
    int year;                 
    std::string genre; 
    
public:
    Book();                                           
    Book(int id, const std::string& title,
         const std::string& author, int year, const std::string& genre);        

    int getId() const;
    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    int getYear() const;  
    const std::string& getGenre() const;                          

    friend std::ostream& operator<<(std::ostream& os, const Book& b);
};
