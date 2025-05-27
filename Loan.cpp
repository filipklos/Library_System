#include "Loan.h"

Loan::Loan(int id, int userId, int bookId,
           const std::string& borrowDate,
           const std::string& returnDate)
    : id(id), userId(userId), bookId(bookId),
      borrowDate(borrowDate), returnDate(returnDate) {}

int Loan::getId() const            { return id; }
int Loan::getUserId() const        { return userId; }
int Loan::getBookId() const        { return bookId; }
std::string Loan::getBorrowDate() const { return borrowDate; }
std::string Loan::getReturnDate() const { return returnDate; }
void Loan::setReturnDate(const std::string& date) { returnDate = date; }
