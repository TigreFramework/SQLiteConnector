#include <TigreFramework/Core/Kernel/Application/Configuration.h>
#include "SQLiteServiceProvider.h"
#include "SQLiteConfiguration.h"

void SQLiteServiceProvider::boot() {
    Configuration::set("Database.driver.sqlite", new SQLiteConfiguration());
}
