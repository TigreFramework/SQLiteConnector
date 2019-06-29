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
        // TODO Parse all Errors codes to create a more friendly message
        throw SQLiteException("Impossible to open a connection to the Database");
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
void SQLiteDataObject::beginTransaction() {}

/**
 * Envia uma transação
 */
void SQLiteDataObject::commit() {}

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
void SQLiteDataObject::exec() {}

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
void SQLiteDataObject::quote() {}

/**
 * Rolls back a transaction
 */
void SQLiteDataObject::rollBack() {}

/**
 * Set an attribute
 */
void SQLiteDataObject::setAttribute() {}