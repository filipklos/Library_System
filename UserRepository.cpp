#include "UserRepository.h"
#include <mysql/jdbc.h>
#include <sstream>
#include <algorithm>

// inicjalizacja singletona
UserRepository* UserRepository::instance = nullptr;

UserRepository::UserRepository(Database& db) : BaseRepository(db)
{
    loadUsers();
}

UserRepository::~UserRepository() {}

UserRepository* UserRepository::getInstance(Database& db)
{
    if (!instance) instance = new UserRepository(db);
    return instance;
}

void UserRepository::loadUsers()
{
    users.clear();
    try
    {
        auto stmt = unique_ptr<sql::Statement>
        (
            db.getConnection()->createStatement()
        );
        auto res = unique_ptr<sql::ResultSet>
        (
            stmt->executeQuery("SELECT id, name, surname FROM users")
        );
        while (res->next())
        {
            users.emplace_back(
                res->getInt("id"),
                res->getString("name"),
                res->getString("surname")
            );
        }
    } catch (sql::SQLException& e)
    {
        cerr << "Błąd podczas ładowania użytkowników: " << e.what() << endl;
    }
}

bool UserRepository::add(const User& user)
{
    try
    {
        stringstream q;
        q << "INSERT INTO users (name, surname) VALUES ('"
          << user.getName() << "','" << user.getSurname() << "')";
        db.executeUpdate(q.str());
        refresh();
        return true;
    } catch (sql::SQLException& e)
    {
        cerr << "Błąd podczas dodawania użytkownika: " << e.what() << endl;
        return false;
    }
}

bool UserRepository::exists(int id) const
{
    return any_of(users.begin(), users.end(),
        [id](auto& u){ return u.getId() == id; });
}

bool UserRepository::remove(int id)
{
    if (!exists(id)) return false;
    try {
        stringstream q;
        q << "DELETE FROM users WHERE id = " << id;
        db.executeUpdate(q.str());
        refresh();
        return true;
    } catch (sql::SQLException& e)
    {
        cerr << "Błąd podczas usuwania użytkownika: " << e.what() << endl;
        return false;
    }
}

vector<User> UserRepository::getAll()
{
    return users;
}

void UserRepository::displayAll()
{
    cout << "ID    Imię    Nazwisko" << endl;
    cout << "--------------------------" << endl;
    for (auto& u : users) u.view();
}

void UserRepository::refresh()
{
    loadUsers();
}
