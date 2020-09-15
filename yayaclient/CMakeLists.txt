cmake_minimum_required(VERSION 3.10.2)
project(yayaclient)

include_directories(rp2)
include_directories(./)
include_directories(../lib/net/cmd/)
link_directories(../thirdparty/lib/)

set(SOURCE_FILES
    main.cpp
    sensorclient.cpp
     ../lib/net/cmd/cmdbuilder.cpp
 )

set(HEADER_FILES    
    sensorclient.h
    ../lib/net/cmd/cmdbuilder.h
 )

add_executable(yayaclient ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(yayaclient PRIVATE netsensorcli)
target_link_libraries(yayaclient PRIVATE dt22sensor)
target_link_libraries(yayaclient PUBLIC -luv -ljansson -lpthread -ldl)

