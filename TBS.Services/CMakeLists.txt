cmake_minimum_required(VERSION 2.6)
project (TBS.Services)
 
set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE JSON_SOURCES "src/jsonrpc/*.cpp")  
file(GLOB_RECURSE DBUS_SOURCES "src/dbuscpp/*.cpp")
file(GLOB_RECURSE DBUSTBS_SOURCES "src/TBS/DBus/*.cpp")
file(GLOB_RECURSE JSONTBS_SOURCES "src/TBS/Json/*.cpp")
file(GLOB_RECURSE TBS_SOURCES "src/Services.cpp")
 
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_ROOT}/TBS/include")
#include_directories("/usr/include/dbus-1.0")
#include_directories("/usr/lib/i386-linux-gnu/dbus-1.0/include/")

find_package( DBus REQUIRED )  

include_directories(${DBUS_INCLUDE_DIR})
include_directories(${DBUS_ARCH_INCLUDE_DIR})

LINK_LIBRARIES (PocoFoundation PocoNet PocoNetSSL TBS dbus-1)  
 
add_library(${PROJECT_NAME} SHARED ${DBUS_SOURCES} ${DBUSTBS_SOURCES} ${JSON_SOURCES} ${JSONTBS_SOURCES} ${TBS_SOURCES})
