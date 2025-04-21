#pragma once
#include <string>
#include <iostream>
#include <cctype>

using namespace std;

class User {
    int id;
    string name;
    string surname;

public:
    //konsturkotry
    User(const int& id, const string& name, const string& surname);
    User(string& name, string& surname);


    //gettery
    int getId() const;
    string getName() const;
    string getSurname() const;


    //funkcje
    void view();
};