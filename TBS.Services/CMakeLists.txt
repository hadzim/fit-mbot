cmake_minimum_required(VERSION 2.6)
project (TBS.Services)
 
set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
 
file(GLOB_RECURSE DBUS_SOURCES "src/dbuscpp/*.cpp")
file(GLOB_RECURSE DBUSTBS_SOURCES "src/TBS/DBus/*.cpp")
file(GLOB_RECURSE TBS_SOURCES "src/Services.cpp")
 
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_ROOT}/TBS/include")
 
LINK_LIBRARIES (PocoFoundation TBS dbus-1)  
 
add_library(${PROJECT_NAME} SHARED ${DBUS_SOURCES} ${DBUSTBS_SOURCES} ${TBS_SOURCES})
