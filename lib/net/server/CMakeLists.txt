cmake_minimum_required(VERSION 3.10.2)
project(netsensorserv)

include_directories(./)
include_directories(../)
include_directories(../../../thirdparty/include)


set(SOURCE_FILES
    mgserverbase.cpp 
    mgconnhandle.cpp 
    ../core/mgutils.cpp 
    ../core/mgclientbase.cpp 
    ../core/mgremotebuffer.cpp  
)


add_library(netsensorserv STATIC ${SOURCE_FILES})
target_include_directories(netsensorserv PUBLIC ../core ./ ./../ ../../../thirdparty/include)
