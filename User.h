#pragma once
#include <string>
#include <iostream>
using namespace std;

class User {
    int id;
    string name;
    string surname;
public:
    User(int id, const string& name, const string& surname);
    User(const string& name, const string& surname);
    int getId() const;
    string getName() const;
    string getSurname() const;
    void view() const;
};