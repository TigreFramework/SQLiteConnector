#ifndef TIGREFRAMEWORK_SQLITEEXCEPTION_H
#define TIGREFRAMEWORK_SQLITEEXCEPTION_H


#include <TigreFramework/Core/Kernel/Exception.h>

class SQLiteException : public Exception {

    public:
        SQLiteException();
        SQLiteException(std::string message);

};


#endif //TIGREFRAMEWORK_SQLITEEXCEPTION_H
