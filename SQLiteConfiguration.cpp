#include "SQLiteConfiguration.h"
#include "SQLiteDataObject.h"

DataObject* SQLiteConfiguration::getInstance(const string &dns, const string &username, const string &passwd,
                                             const map<string, string> &options) {
    return new SQLiteDataObject(dns, username, passwd, options);
}
