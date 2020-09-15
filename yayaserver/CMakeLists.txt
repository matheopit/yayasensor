cmake_minimum_required(VERSION 3.10.2)
project(yayaserver)

include_directories(rp2)
include_directories(./)
include_directories(../lib/net/cmd)

link_directories(../thirdparty/lib/)

set(SOURCE_FILES
    main.cpp
    sensorserver.cpp
    sensorremotecli.cpp
    sensorcmddb.cpp
    ../lib/net/cmd/mgcommand.cpp
    ../lib/net/cmd/mgcommanddecoder.cpp
    ../lib/net/cmd/cmdbuilder.cpp

 )

set(HEADER_FILES    
    sensorserver.h
    sensorremotecli.h
    sensorcmddb.h
   ../lib/net/cmd/mgcommand.h
   ../lib/net/cmd/mgcommanddecoder.h
   ../lib/net/cmd/cmdbuilder.h
 )

add_executable(yayaserver ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(yayaserver PRIVATE netsensorserv)
target_link_libraries(yayaserver PRIVATE netdb)
target_link_libraries(yayaserver PUBLIC -luv -ljansson -lpthread -ldl)
