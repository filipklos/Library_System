#pragma once
#include "BaseRepository.h"
#include "Loan.h"
#include <vector>

class LoanRepository : public BaseRepository {
private:
    static LoanRepository* instance;
    LoanRepository(Database& db);

public:
    static LoanRepository& getInstance(Database& db);
    void borrowBook(int userId, int bookId);
    void returnBook(int bookId);
    void displayActiveLoans() const;
    void displayLoanHistory() const;
};


