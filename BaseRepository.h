#pragma once
#include "Database.h"

class BaseRepository
{
protected:
    Database& db;
    
public:
    BaseRepository(Database& db);
    virtual ~BaseRepository();

    //virtual bool deleteById(int id);
    //virtual int count();
};