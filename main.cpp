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
#include "Validation.h" 

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
            clearConsole();
            
            switch (choice) {
                case 1:
                {
                    // DODANIE UŻYTKOWNIKA
                    clearConsole();
                    // WALIDACJA: imię musi mieć 3–100 znaków
                    string name;
                    do {
                        cout << endl << "Dodawanie nowego użytkownika:" << endl;
                        cout << "Podaj imię: ";
                        cin >> name;
                        if (!Validator::isStringValid(name)) {
                            cout << "Imię musi mieć od 3 do 100 znaków. Spróbuj ponownie." << endl;
                        }
                    } while (!Validator::isStringValid(name));

                    string surname;
                    // WALIDACJA: nazwisko musi mieć 3–100 znaków
                    do {
                        cout << "Podaj nazwisko: ";
                        cin >> surname;
                        if (!Validator::isStringValid(surname)) {
                            cout << "Nazwisko musi mieć od 3 do 100 znaków. Spróbuj ponownie." << endl;
                        }
                    } while (!Validator::isStringValid(surname));
                    
                    User newUser(name, surname);
                    clearConsole();
                    
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
                    // USUWANIE UŻYTKOWNIKA
                    clearConsole();
                    int id;
                    cout << endl << "Lista użytkowników:" << endl;
                    repo->displayAll();

                    cout << endl << "Usuwanie użytkownika:" << endl;
                    cout << "Podaj ID użytkownika do usunięcia: ";
                    cin >> id;
                    // WALIDACJA: ID użytkownika musi być liczbą
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

                    // Sprawdzenie, czy użytkownik ma aktywne wypożyczenia
                    if (Validator::userHasActiveLoans(db, id)) {
                        cout << "Użytkownik ma aktywne wypożyczenia. Nie można go usunąć." << endl;
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
                    cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                    string title, author, genre;
                    int year;

                    cout << "\nDodawanie nowej książki:\n";

                    // WALIDACJA: tytuł 3–100 znaków
                    do {
                        cout << "Tytuł: ";
                        getline(cin, title);
                        if (!Validator::isStringValid(title)) {
                            cout << "Tytuł musi mieć od 3 do 100 znaków. Spróbuj ponownie." << endl;
                        }
                    } while (!Validator::isStringValid(title));

                    // WALIDACJA: autor 3–100 znaków
                    do {
                        cout << "Autor: ";
                        getline(cin, author);
                        if (!Validator::isStringValid(author)) {
                            cout << "Autor musi mieć od 3 do 100 znaków. Spróbuj ponownie." << endl;
                        }
                    } while (!Validator::isStringValid(author));

                    // WALIDACJA: poprawny format roku (liczba całkowita)
                    while (true) {
                        cout << "Rok wydania: ";
                        if (!(cin >> year)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Niepoprawny format roku. Podaj ponownie." << endl;
                            continue;
                        }
                        if (year <= 0 || year > 2025) {
                            cout << "Rok wydania musi być w zakresie od 0 DO 2025. Spróbuj ponownie." << endl;
                            continue;
                        }

                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }

                    // WALIDACJA: gatunek 3–100 znaków
                    do {
                        cout << "Gatunek: ";
                        getline(cin, genre);
                        if (!Validator::isStringValid(genre)) {
                            cout << "Gatunek musi mieć od 3 do 100 znaków. Spróbuj ponownie." << endl;
                        }
                    } while (!Validator::isStringValid(genre));

                    Book newBook(0, title, author, year, genre);

                    clearConsole();
                    if (bookRepo.add(newBook))
                    {
                        cout << "Książka dodana pomyślnie!" << endl;
                    } else 
                    {
                        cout << "Błąd podczas dodawania książki!" << endl;
                    }
                    break;
                }
                    

                   case 5: {
                    // Usuwanie książki
                    clearConsole();
                    int bookId;
                    cout << "\nLista książek:\n";
                    bookRepo.displayAll();

                    cout << "\nPodaj ID książki do usunięcia: ";
                    cin >> bookId;
                    clearConsole();
                    // WALIDACJA: ID książki musi być liczbą
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Nieprawidłowe ID książki." << endl;
                        break;
                    }
                    // WALIDACJA: sprawdzenie istnienia książki
                    if (!bookRepo.exists(bookId)) {
                        cout << "Książka o ID = " << bookId << " nie istnieje." << endl;
                        break;
                    }
                    // WALIDACJA: czy książka jest wypożyczona
                    if (Validator::bookIsBorrowed(db, bookId)) {
                        cout << "Książka jest aktualnie wypożyczona. Nie można jej usunąć." << endl;
                        break;
                    }

                    if (bookRepo.remove(bookId))
                    {
                        cout << "Książka usunięta pomyślnie!" << endl;
                    } else 
                    {
                        cout << "Błąd podczas usuwania książki!" << endl;
                    }
                    break;
                }

                case 6:
                    // Wyświetlanie książek
                    clearConsole();
                    cout << endl << "Lista książek:" << endl; 
                    bookRepo.displayAll();
                    break;

             case 7: {
                    // Wypożyczanie książki
                    clearConsole();
                    int uId, bId;
                    cout << endl << "Lista użytkowników:" << endl;
                    repo->displayAll();
                    cout << "Podaj ID użytkownika: ";
                    cin >> uId;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                        cout << "Nieprawidłowe ID użytkownika." << endl;
                        break;
                    }

                    cout << endl << "Lista książek:" << endl; 
                    bookRepo.displayAll();
                    cout << "Podaj ID książki: ";
                    cin >> bId;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Nieprawidłowe ID książki." << endl;
                        break;
                    }
                    clearConsole();
                    loanRepo.borrowBook(uId, bId);
                    break;
                }

                case 8: {
                    // Zwracanie książki
                    clearConsole();
                    int bId;
                    loanRepo.displayActiveLoans();
                    cout << "Podaj ID książki do zwrotu: ";
                    cin >> bId;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Nieprawidłowe ID książki." << endl;
                        break;
                    }
                    clearConsole();
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
