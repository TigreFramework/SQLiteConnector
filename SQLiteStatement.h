#ifndef TIGREFRAMEWORK_SQLITESTATEMENT_H
#define TIGREFRAMEWORK_SQLITESTATEMENT_H

#include <TigreFramework/Database/DataObjectStatement.h>

#ifndef _SQLITE3_H_
typedef struct sqlite3;
typedef struct sqlite3_stmt;
#endif

class SQLiteStatement : public DataObjectStatement {

public:
    SQLiteStatement(sqlite3 * connection, std::string sql);
    ~SQLiteStatement() override ;

    /**
     * Bind a column to a PHP variable
     */
    void bindColumn() override { }
    /**
     * Binds a parameter to the specified variable name
     */
    void bindParam() override { }
    /**
     * Binds a value to a parameter
     */
    void bindValue() override { }
    /**
     * Closes the cursor, enabling the statement to be executed again
     */
    void closeCursor() override { }
    /**
     * Returns the number of columns in the result set
     */
    void columnCount() override { }
    /**
     * Dump an SQL prepared command
     */
    void debugDumpParams() override { }
    /**
     * Fetch the SQLSTATE associated with the last operation on the statement handle
     */
    void errorCode() override { }
    /**
     * Fetch extended error information associated with the last operation on the statement handle
     */
    void errorInfo() override { }
    /**
     * Executes a prepared statement
     */
    /**
     * Use named field
     * @param params
     * @return bool
     */
    bool execute(std::map<string, Value> params) override ;
    /**
     * Use interrogation as marker
     * @param params
     * @return bool
     */
    bool execute(std::vector<Value> params)  override ;
    /**
     * No bind Used
     * @return bool
     */
    bool execute()  override ;
    /**
     * Fetches the next row from a result set
     */
    void fetch() override { }
    /**
     * Returns an array containing all of the result set rows
     */
    vector<Line> fetchAll() override ;
    /**
     * Returns a single column from the next row of a result set
     */
    void fetchColumn() override { }
    /**
     * Fetches the next row and returns it as an object
     */
    void fetchObject() override { }
    /**
     * Retrieve a statement attribute
     */
    void getAttribute() override { }
    /**
     * Returns metadata for a column in a result set
     */
    void getColumnMeta() override { }
    /**
     * Advances to the next rowset in a multi-rowset statement handle
     */
    void nextRowset() override { }
    /**
     * Returns the number of rows affected by the last SQL statement
     */
    void rowCount() override { }
    /**
     * Define um atributo na instrução
     */
    void setAttribute() override { }
    /**
     * Define o modo de carga de dados para esta instrução
     */
    void setFetchMode() override { }

private:
    sqlite3 * connection = nullptr;
    sqlite3_stmt *statement = nullptr;
    std::string sql;

    bool execute(std::string sql);

};


#endif //TIGREFRAMEWORK_SQLITESTATEMENT_H
