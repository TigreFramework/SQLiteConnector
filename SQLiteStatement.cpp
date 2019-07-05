#include <TigreFramework/String/String.h>
#include <TigreFramework/SQLiteConnector/Exceptions/SQLiteException.h>
#include "sqlite/sqlite3.h"
#include "SQLiteStatement.h"

SQLiteStatement::SQLiteStatement(sqlite3 *connection, std::string sql) : DataObjectStatement() {
    this->connection = connection;
    this->sql = std::move(sql);
}

SQLiteStatement::~SQLiteStatement() {
    this->closeCursor();
}

bool SQLiteStatement::execute() {
    Param param;
    param.set(this->bindValueByIndex);
    param.set(this->bindValueByName);
    return this->execute(param);
}

bool SQLiteStatement::execute(const Param& params) {
    if(!this->bindValueByName.empty() || !this->bindValueByIndex.empty()){
        throw SQLiteException("Do not use execute bind and bindValue at the same time.");
    }
    this->sql = params.bind(this->sql, this);
    this->execute(this->sql);
}

bool SQLiteStatement::execute(std::string sql) {
    if(this->statement != nullptr) {
        sqlite3_finalize(this->statement);
        this->statement = nullptr;
        this->columns = 0;
    }
    int status = sqlite3_prepare_v2(this->connection, sql.c_str(), -1, &this->statement, nullptr);
    if (status != SQLITE_OK) {
        auto message = std::string("\"SQLiteStatement::execute\" failed: ") + sqlite3_errmsg(this->connection);

        sqlite3_finalize(this->statement);
        this->statement = nullptr;

        throw SQLiteException(message);
    }

    return true;
}

Line SQLiteStatement::fetch() {
    if(this->statement == nullptr){
        throw SQLiteException("No Statement Executed!");
    }
    int cols = this->columnCount();
    this->status = sqlite3_step(this->statement);
    if (this->status == SQLITE_ROW) {
        vector<map<string, string>> values;
        Line line;
        for (int col = 0; col < cols; col++) {
            std::string column_name = (char *) sqlite3_column_name(this->statement, col);
            int column_type = sqlite3_column_type(this->statement, col);
            switch (column_type) {
                case SQLITE_INTEGER:
                    line[column_name] = sqlite3_column_int(this->statement, col);
                    break;
                case SQLITE_FLOAT:
                    line[column_name] = sqlite3_column_double(this->statement, col);
                    break;
                case SQLITE_TEXT:
                    line[column_name] = std::string((char *)sqlite3_column_text(this->statement, col));
                    break;
                default:
                    line[column_name] = std::string((char *)sqlite3_column_text(this->statement, col));
            }
        }
        return line;
    } else {
        switch (this->status) {
            case SQLITE_DONE:
                return {};
            case SQLITE_BUSY:
                throw SQLiteException("SQLite Resource is Busy");
            case SQLITE_ERROR:
                throw SQLiteException("SQLite unknown error");
            case SQLITE_READONLY:
                throw SQLiteException("SQLite Resource is readonly");
            case SQLITE_CANTOPEN:
                throw SQLiteException("SQLite Unable to open the database file");
            default:
                throw SQLiteException(
                        "SQLite error num: " +
                        std::to_string(this->status) + " message " +
                        this->errorInfo()
                );
        }
    }
}

vector<Line> SQLiteStatement::fetchAll() {
    if(this->statement == nullptr){
        throw SQLiteException("No Statement Executed!");
    }
    vector<Line> result;
    Line line;
    do {
        line = this->fetch();
        if(!line.empty()) {
            result.push_back(line);
        }
    } while(!line.empty());
    return result;
}

/**
 * Do not use this function to count number of rows on a select,
 * SQLite do not provide this functionality.
 * @return
 */
int SQLiteStatement::rowCount() {
    return sqlite3_changes(this->connection);
}

int SQLiteStatement::errorCode() {
    return this->status;
}

std::string SQLiteStatement::errorInfo() {
    if(this->statusInfo.empty()){
        this->statusInfo = sqlite3_errmsg(this->connection);
    }
    return this->statusInfo;
}

int SQLiteStatement::columnCount() {
    if(this->columns == 0){
        this->columns = sqlite3_column_count(this->statement);
    }
    return this->columns;
}

void SQLiteStatement::closeCursor() {
    if(this->statement != nullptr) {
        sqlite3_finalize(this->statement);
        this->statement = nullptr;
    }
}

std::string SQLiteStatement::debugDumpParams() {
    return this->sql;
}

void SQLiteStatement::bindValue(int index, Value value) {
    this->bindValueByIndex[index] = value;
}

void SQLiteStatement::bindValue(std::string name, Value value) {
    this->bindValueByName[name] = value;
}

std::string SQLiteStatement::quote(const std::string &value) {
    return "\"" + value + "\"";
}