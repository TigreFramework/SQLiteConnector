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
    void closeCursor() override ;
    /**
     * Returns the number of columns in the result set
     */
    int columnCount() override ;
    /**
     * Dump an SQL prepared command
     */
    std::string debugDumpParams() override ;
    /**
     * Fetch the SQLSTATE associated with the last operation on the statement handle
     */
    int errorCode() override ;
    /**
     * Fetch extended error information associated with the last operation on the statement handle
     */
    std::string errorInfo() override ;
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
    Line fetch() override ;
    /**
     * Returns an array containing all of the result set rows
     */
    vector<Line> fetchAll() override ;
    /**
     * Returns metadata for a column in a result set
     */
    void getColumnMeta() override { }
    /**
     * Returns the number of rows affected by the last SQL statement
     */
    int rowCount() override ;

private:
    sqlite3 * connection = nullptr;
    sqlite3_stmt *statement = nullptr;
    std::string sql;

    //INFORMATION
    int columns = 0;
    int status = -1;
    std::string statusInfo;

    bool execute(std::string sql);

};


#endif //TIGREFRAMEWORK_SQLITESTATEMENT_H
