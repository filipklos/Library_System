#include "User.h"
#include <iostream>
#include <cctype>

// konstruktor z id
User::User(int id, const string& name, const string& surname)
    : id(id), name(name), surname(surname) {}

// konstruktor bez id
User::User(const string& name, const string& surname)
    : id(-1), name(name), surname(surname) {}

int User::getId() const { return id; }
string User::getName() const { return name; }
string User::getSurname() const { return surname; }

void User::view() const {
    // jedna spacja między polami
    cout << id << " " << name << " " << surname << endl;
}