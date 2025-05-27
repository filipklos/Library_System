#include "Database.h"
#include <cstdlib>
#include "config.h"
#include "User.h"
#include "UserRepository.h"
#include <limits>
#include "Book.h"
#include "BookRepository.h"
#include "LoanRepository.h"
#include "Loan.h"

void clearConsole()
{
//czyszczenie konsoli
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void displayMenu()
{
    //Wyświetlanie menu
    cout << endl << "----System Biblioteczny----" << endl;
    cout << "1. Dodaj użytkownika" << endl;
    cout << "2. Usuń użytkownika" << endl;
    cout << "3. Wyświetl listę użytkowników" << endl;
    cout << "4. Dodaj książkę" << endl;
    cout << "5. Usuń książkę" << endl;
    cout << "6. Wyświetl listę książek" << endl;
    cout << "7. Wypożycz książkę"<<endl;
    cout << "8. Zwróć książkę"<<endl;
    cout << "9. Wyświetl aktywne wypożyczenia"<<endl;
    cout << "10. Wyświetl historię wypożyczeń"<<endl;
    cout << "0. Wyjdź" << endl;
    cout << "Wybierz opcję: ";
}

int main()
{
    try
    {
        // Utworzenie połączenia z bazą danych
        Database db(DB_HOST, DB_USER, DB_PASS, DB_NAME);
        UserRepository* repo = UserRepository::getInstance(db);
        BookRepository& bookRepo = BookRepository::getInstance(db);
        LoanRepository& loanRepo = LoanRepository::getInstance(db);
        clearConsole();
        
        int choice = -1;
        
        do
        {
            clearConsole();
            displayMenu();
            cin >> choice;
            
            // Obsługa nieprawidłowego wejścia
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Nieprawidłowy wybór. Spróbuj ponownie." << endl;
                continue;
            }
            
            switch (choice) {
                case 1:
                {
                    // Dodawanie użytkownika
                    clearConsole();
                    string name, surname;
                    cout << endl << "Dodawanie nowego użytkownika:" << endl;
                    cout << "Podaj imię: ";
                    cin >> name;
                    cout << "Podaj nazwisko: ";
                    cin >> surname;
                    
                    User newUser(name, surname);
                    
                    if (repo->add(newUser))
                    {
                        cout << "Użytkownik dodany pomyślnie!" << endl;
                    } else
                    {
                        cout << "Błąd podczas dodawania użytkownika!" << endl;
                    }
                    break;
                }
                case 2:
                    // Usuwanie użytkownika
                    clearConsole();
                    int id;
                    cout << endl << "Lista użytkowników:" << endl;
                    repo->displayAll();

                    cout << endl << "Usuwanie użytkownika:" << endl;
                    cout << "Podaj ID użytkownika do usunięcia: ";
                    cin >> id;
                    clearConsole();
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Nieprawne ID (to nie jest liczba)." << endl;
                        break;
                    }
                    // Walidacja istnienia w repozytorium
                    if (!repo->exists(id))
                    {
                        cout << "Użytkownik o ID = " << id << " nie istnieje." << endl;
                        break;
                    }
                    if (repo->remove(id))
                    {
                        cout << "Użytkownik usunięty pomyślnie!" << endl;
                    } else
                    {
                        cout << "Błąd podczas usuwania użytkownika!" << endl;
                    }
                    break;
                
                case 3:
                    // Wyświetlanie użytkowników
                    clearConsole();
                    cout << endl << "Lista użytkowników:" << endl;
                    repo->displayAll();
                    break;

                
                case 4: {
                    // Dodawanie książki
                    clearConsole();
                    cin.ignore(); 
                    string title, author,genre;
                    int year;
                    cout << "\nDodawanie nowej książki:\n";
                    cout << "Tytuł: ";  getline(cin, title);
                    cout << "Autor: ";  getline(cin, author);
                    cout << "Rok wydania: "; cin >> year;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Gatunek: ";   getline(cin, genre);
                    Book newBook(0, title, author, year, genre);
                    bookRepo.add(newBook);
                    break;
                }
                
                case 5: {
                    // Usuwanie książki
                    clearConsole();
                    int bookId;
                    cout << "\nLista książek:\n"; bookRepo.displayAll();
                    cout << "\nPodaj ID książki do usunięcia: "; cin >> bookId;
                    clearConsole();
                    bookRepo.remove(bookId);
                    

                    break;
                }
                case 6:
                    // Wyświetlanie książek
                    clearConsole();
                    cout << "\nLista książek:\n"; bookRepo.displayAll();
                    break;

                case 7: {
                    // Wypożyczanie książki
                    clearConsole();
                    int uId, bId;
                    cout << "Podaj ID użytkownika: "; cin >> uId;
                    cout << "Podaj ID książki: ";     cin >> bId;
                    loanRepo.borrowBook(uId, bId);
                break;
                }

                case 8: {
                    // Zwracanie książki
                    clearConsole();
                    int bId;
                    cout << "Podaj ID książki do zwrotu: "; cin >> bId;
                    loanRepo.returnBook(bId);
                break;
                }

                case 9:
                // Wyświetlanie aktywnych wypożyczeń
                clearConsole();
                loanRepo.displayActiveLoans();
                break;

                case 10:
                // Wyświetlanie historii wypożyczeń
                clearConsole();
                loanRepo.displayLoanHistory();
                break;

                case 0:
                    cout << "Zamykanie aplikacji..." << endl;
                    break;

                default:
                    clearConsole();
                    cout << "Nieznana opcja. Spróbuj ponownie." << endl;
            }
            
        } while (choice != 0);
        
    } catch (sql::SQLException& e)
    {
        cerr << "Błąd SQL: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}