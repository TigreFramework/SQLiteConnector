#ifndef TIGREFRAMEWORK_SQLITESERVICEPROVIDER_H
#define TIGREFRAMEWORK_SQLITESERVICEPROVIDER_H


#include <TigreFramework/Core/Kernel/Application/ServiceProvider.h>
#include <TigreFramework/Core/Kernel/Application/Configurable.h>

class SQLiteServiceProvider : public ServiceProvider, public Configurable {

    public:
        void boot();

};


#endif //TIGREFRAMEWORK_SQLITESERVICEPROVIDER_H
