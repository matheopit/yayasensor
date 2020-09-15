cmake_minimum_required(VERSION 3.10.2)
project(netdb)

include_directories(./)
include_directories(../../thirdparty/include)
include_directories(../net/cmd)
set(SOURCE_FILES
    ctmgrdatabase.cpp
    ctmgrdb.cpp
    sqlite3.c
    ../net/cmd/cmdbuilder.cpp
)


add_library(netdb STATIC ${SOURCE_FILES})
target_include_directories(netdb PUBLIC ./)

