#include <TigreFramework/String/String.h>
#include <TigreFramework/SQLiteConnector/Exceptions/SQLiteException.h>
#include "sqlite/sqlite3.h"
#include "SQLiteStatement.h"

SQLiteStatement::SQLiteStatement(sqlite3 *connection, std::string sql) : DataObjectStatement() {
    this->connection = connection;
    this->sql = std::move(sql);
}

SQLiteStatement::~SQLiteStatement() {
    if(this->statement != nullptr) {
        sqlite3_finalize(this->statement);
        this->statement = nullptr;
    }
}

bool SQLiteStatement::execute() {
    return this->execute(this->sql);
}

bool SQLiteStatement::execute(std::map<string, Value> params) {
    std::string prepared_sql;

    if(params.empty()) {
        prepared_sql = this->sql.c_str();
    } else {
        Tigre::String sql = this->sql;
        for(const auto & param : params) {
            const auto & p = param.second;
            Tigre::String value;
            if (p.isString()) {
                value += std::string("\"");
                value += p.getString();
                value += std::string("\"");
            } else if (p.isInteger()) {
                value += std::to_string(p.getInteger());
            } else if (p.isFloat()) {
                value += std::to_string(p.getFloat());
            } else if (p.isDouble()) {
                value += std::to_string(p.getDouble());
            }
            sql.replace(param.first, value);
        }
        prepared_sql = sql.getValue();
    }

    return this->execute(prepared_sql);
}

bool SQLiteStatement::execute(std::vector<Value> params) {
    std::string result;
    int j = 0;
    if(!params.empty()) {
        for (char i : this->sql) {
            if (i == '?' && j < params.size()) {
                if (params[j].isString()) {
                    result += std::string("\"");
                    result += params[j].getString();
                    result += std::string("\"");
                } else if (params[j].isInteger()) {
                    result += std::to_string(params[j].getInteger());
                } else if (params[j].isFloat()) {
                    result += std::to_string(params[j].getFloat());
                } else if (params[j].isDouble()) {
                    result += std::to_string(params[j].getDouble());
                }
                j++;
            } else {
                result += std::string(1, i);
            }
        }
    } else {
        result = this->sql;
    }
    return this->execute(result);
}

bool SQLiteStatement::execute(std::string sql) {
    if(this->statement != nullptr) {
        sqlite3_finalize(this->statement);
        this->statement = nullptr;
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
    int cols = sqlite3_column_count(this->statement);
    int status = sqlite3_step(this->statement);
    if (status == SQLITE_ROW) {
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
        switch (status) {
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
                throw SQLiteException("SQLite error num: " + std::to_string(status) + " message " + sqlite3_errmsg(this->connection));
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
