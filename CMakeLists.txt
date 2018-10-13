cmake_minimum_required(VERSION 3.4)
project(TigreFramework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SYSTEM_FILES
    SQLite.cpp
    SQLite.h
    sqlite/shell.c
    sqlite/sqlite3.c
    sqlite/sqlite3.h
    sqlite/sqlite3ext.h
)

set(SOURCE_FILES ${SYSTEM_FILES})

add_library(tgSQLiteConnector ${SYSTEM_FILES})

find_package (Threads REQUIRED)

target_link_libraries (tgSQLiteConnector ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
