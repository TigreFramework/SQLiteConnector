#ifndef TIGREFRAMEWORK_SQLITECONFIGURATION_H
#define TIGREFRAMEWORK_SQLITECONFIGURATION_H

#include <TigreFramework/Core/Kernel/Application/Configurable.h>
#include <TigreFramework/Database/DataObject.h>
#include <TigreFramework/Database/DataObjectConfiguration.h>

class SQLiteConfiguration  : public DataObjectConfiguration, public Configurable {

public:
    DataObject* getInstance(const string &dns, const string &username, const string &passwd, const map<string, string> &options);

};



#endif //TIGREFRAMEWORK_SQLITECONFIGURATION_H
