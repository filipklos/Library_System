#pragma once
#include <string>

class Loan {
private:
    int id;
    int userId;            
    int bookId;            
    std::string borrowDate;  
    std::string returnDate;  

public:
    Loan() = default;
    Loan(int id, int userId, int bookId,
         const std::string& borrowDate,
         const std::string& returnDate);

    int getId() const;
    int getUserId() const;
    int getBookId() const;
    std::string getBorrowDate() const;
    std::string getReturnDate() const;
    void setReturnDate(const std::string& date);
};

