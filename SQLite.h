//
// Created by pedro on 05/12/17.
//

#ifndef TIGREFRAMEWORK_SQLITE_H
#define TIGREFRAMEWORK_SQLITE_H

#include <vector>
#include <string>
#include <map>

#include "sqlite/sqlite3.h"

using namespace std;

class SQLite {

    public:
        SQLite(string filename);
        ~SQLite();

        bool open(string filename);
        vector<vector< map<string, string> > > query(string query);
        void close();

    private:
        sqlite3 *database;

};


#endif //TIGREFRAMEWORK_SQLITE_H
