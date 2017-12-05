#include "SQLite.h"

SQLite::SQLite(string filename) {
    database = NULL;
    open(filename.c_str());
}

SQLite::~SQLite() {

}

bool SQLite::open(string filename) {
    if(sqlite3_open(filename.c_str(), &database) == SQLITE_OK)
        return true;

    return false;
}

vector<vector< map<string, string> > > SQLite::query(string Query) {
sqlite3_stmt *statement;

vector<vector< map<string, string> > > results;

if(sqlite3_prepare_v2(database, Query.c_str(), -1, &statement, 0) == SQLITE_OK){
int cols = sqlite3_column_count(statement);
int result = 0;
while(true){
result = sqlite3_step(statement);

if(result == SQLITE_ROW){
vector<map<string, string>> values;
for(int col = 0; col < cols; col++){
map<string, string> value;
value[(char*)sqlite3_column_name(statement, col)] = (char*)sqlite3_column_text(statement, col);
values.push_back( value );
}
results.push_back(values);
}else{
break;
}
}

sqlite3_finalize(statement);
}

string error = sqlite3_errmsg(database);
//if(error != "not an error") cout << Query << " " << error << endl;

return results;
}

void SQLite::close() {
    sqlite3_close(database);
}