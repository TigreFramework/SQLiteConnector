#include "SQLiteException.h"


SQLiteException::SQLiteException() : Exception() {}

SQLiteException::SQLiteException(std::string message) : Exception(std::move(message)) {}

