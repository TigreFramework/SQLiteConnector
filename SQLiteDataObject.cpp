#include <TigreFramework/SQLiteConnector/Exceptions/SQLiteException.h>
#include "sqlite/sqlite3.h"
#include "SQLiteDataObject.h"
#include "SQLiteStatement.h"

/**
 * Create Connection
 * @param dns
 * @param username
 * @param passwd
 * @param options
 */
SQLiteDataObject::SQLiteDataObject(const string &dns, const string &username, const string &passwd,
                                   const map<string, string> &options) {
    this->database = nullptr;
    int error = sqlite3_open(dns.c_str(), &this->database);
    if(error != SQLITE_OK) {
        std::string message = sqlite3_errmsg(this->database);
        if(this->database != NULL){
            sqlite3_close(this->database);
            this->database = nullptr;
        }
        throw SQLiteException(message);
    }

}

/**
 * Destroy Connection
 */
SQLiteDataObject::~SQLiteDataObject() {
    if(this->database != nullptr){
        sqlite3_close(this->database);
        this->database = nullptr;
    }
    for (auto &i : this->statement) {
        delete i;
    }
    this->statement.clear();
}

/**
 * Inicia uma transação
 */
void SQLiteDataObject::beginTransaction() {
    auto status = sqlite3_exec(this->database, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);
    if (status != SQLITE_OK) {
        auto message = std::string("\"SQLiteDataObject::beginTransaction\" failed: ") + sqlite3_errmsg(this->database);
        throw SQLiteException(message);
    }
}

/**
 * Envia uma transação
 */
void SQLiteDataObject::commit() {
    auto status = sqlite3_exec(this->database, "COMMIT TRANSACTION;", nullptr, nullptr, nullptr);
    if (status != SQLITE_OK) {
        auto message = std::string("\"SQLiteDataObject::beginTransaction\" failed: ") + sqlite3_errmsg(this->database);
        throw SQLiteException(message);
    }
}

/**
 * Fetch the SQLSTATE associated with the last operation on the database handle
 */
void SQLiteDataObject::errorCode() {}

/**
 * Fetch extended error information associated with the last operation on the database handle
 */
void SQLiteDataObject::errorInfo() {}

/**
 * Executa uma instrução SQL e retornar o número de linhas afetadas
 */
int SQLiteDataObject::exec(std::string sql) {
    auto statement = new SQLiteStatement(this->database, sql);
    this->statement.push_back(statement);
    statement->execute();
    statement->fetchAll();
    return statement->rowCount();
}

/**
 * Recuperar um atributo da conexão com o banco de dados
 */
void SQLiteDataObject::getAttribute() {}

/**
 * Retorna um array com os drivers PDO disponíveis
 */
void SQLiteDataObject::getAvailableDrivers() {}

/**
 * Checks if inside a transaction
 */
void SQLiteDataObject::inTransaction() {}

/**
 * Returns the ID of the last inserted row or sequence value
 */
int SQLiteDataObject::lastInsertId() {}

/**
 * Prepares a statement for execution and returns a statement object
 */
DataObjectStatement* SQLiteDataObject::prepare(std::string sql) {
    auto statement = new SQLiteStatement(this->database, sql);
    this->statement.push_back(statement);
    return statement;
}

/**
 * Executes an SQL statement, returning a result set as a PDOStatement object
 */
void SQLiteDataObject::query() {}

/**
 * Quotes a string for use in a query
 */
std::string SQLiteDataObject::quote(const std::string &value) {
    return "\"" + value + "\"";
}

/**
 * Rolls back a transaction
 */
void SQLiteDataObject::rollBack() {
    auto status = sqlite3_exec(this->database, "ROLLBACK TRANSACTION;", nullptr, nullptr, nullptr);
    if (status != SQLITE_OK) {
        auto message = std::string("\"SQLiteDataObject::beginTransaction\" failed: ") + sqlite3_errmsg(this->database);
        throw SQLiteException(message);
    }
}

/**
 * Set an attribute
 */
void SQLiteDataObject::setAttribute() {}