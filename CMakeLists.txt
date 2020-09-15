cmake_minimum_required (VERSION 2.8.11)
project (yayasensor)

# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory (lib/sensor/libdht22)
add_subdirectory (lib/sql)
add_subdirectory (lib/net/server)
add_subdirectory (lib/net/client)
add_subdirectory (yayaclient)
add_subdirectory (yayaserver)
add_subdirectory (yayatest)
