#include "User.h"

//konstruktory
User::User(const int& id, const string& name, const string& surname)
{
    this->id = id;
    this->name = name;
    this->surname = surname;
}

User::User(string& name, string& surname)
{
    // walidacja danych
    while (name.size() < 2 || name.size() > 20)
    {
        cout << "Imie musi mieć od 2 do 20 znaków!" << endl;
        cout << "Podaj imie: ";
        cin >> name;
    }


    while (surname.size() < 2 || surname.size() > 20)
    {
        cout << "Nazwisko musi mieć od 2 do 20 znaków!" << endl;
        cout << "Podaj nazwisko: ";
        cin >> surname;
    }

    // zamiana pierwszej litery na wielką
    name[0] = toupper(name[0]);
    surname[0] = toupper(surname[0]);


    // zamiana reszty liter na małe
    for (size_t i = 1; i < name.size(); i++)
    {
        name[i] = tolower(name[i]);     
    }

    for (size_t i = 1; i < surname.size(); i++)
    {
        surname[i] = tolower(surname[i]);
    }

    this->name = name;
    this->surname = surname;
}

//gettery
int User::getId() const
{
    return id;
}

string User::getName() const
{
    return name;
}

string User::getSurname() const
{
    return surname;
}

//funkcje
void User::view()
{
    cout << id << "    " << name << "    " << surname << endl;
}