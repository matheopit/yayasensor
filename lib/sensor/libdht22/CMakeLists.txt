cmake_minimum_required(VERSION 3.10.2)
project(dt22sensor)

include_directories(rp2)
include_directories(./)

set(SOURCE_FILES
    common_dht_read.c
    rp2/pi_2_dht_read.c
    rp2/pi_2_mmio.c
 )

add_library(dt22sensor STATIC ${SOURCE_FILES})
target_include_directories(dt22sensor PUBLIC rp2/)
