cmake_minimum_required(VERSION 3.10.2)
project(yayatest)

include_directories(rp2)
include_directories(./)
include_directories(../lib/net/cmd/)
link_directories(../thirdparty/lib/)

set(SOURCE_FILES
    main.cpp
    ../lib/net/cmd/cmdbuilder.cpp
 )

set(HEADER_FILES    
    ../lib/net/cmd/cmdbuilder.h
 )

add_executable(yayatest ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(yayatest PRIVATE netsensorcli)
target_link_libraries(yayatest PRIVATE dt22sensor)
target_link_libraries(yayatest PRIVATE netdb)
target_link_libraries(yayatest PUBLIC -luv -ljansson -lpthread -ldl)

