cmake_minimum_required(VERSION 3.10.2)

project(netsensorcli)

include_directories(./)
include_directories(./../)
include_directories(../../../thirdparty/include)
link_directories(../thirdparty/lib/)
set(SOURCE_FILES
    mgclient.cpp 
    ../core/mgutils.cpp 
    ../core/mgclientbase.cpp 
    ../core/mgremotebuffer.cpp  
)

add_library(netsensorcli STATIC ${SOURCE_FILES} ${HEADER_LIST})
target_include_directories(netsensorcli PUBLIC ../core ./ ./../ ../../../thirdparty/include)
