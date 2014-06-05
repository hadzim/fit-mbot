cmake_minimum_required(VERSION 2.6)
project (HAL.API)
 
set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
 
file(GLOB_RECURSE LIB_SOURCES "src/*.cpp")
 
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_ROOT}/TBS/include")
include_directories("${PROJECT_ROOT}/TBS.Services/include")

find_package( DBus REQUIRED )  

include_directories(${DBUS_INCLUDE_DIR})
include_directories(${DBUS_ARCH_INCLUDE_DIR})

 
LINK_LIBRARIES (PocoFoundation PocoUtil TBS TBS.Services dbus-1)  
 
add_library(${PROJECT_NAME} SHARED ${LIB_SOURCES})
