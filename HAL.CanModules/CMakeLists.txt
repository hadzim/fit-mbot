cmake_minimum_required(VERSION 2.6)
project (bin.HAL.CanModules)
 
set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
 
file(GLOB_RECURSE EXE_SOURCES "src/*.cpp")

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_ROOT}/TBS/include")
include_directories("${PROJECT_ROOT}/TBS.Services/include")
include_directories("${PROJECT_ROOT}/HAL.API/include")
include_directories("${PROJECT_ROOT}/TBS.Robo/include")
include_directories("${PROJECT_ROOT}/TBS.Robo.RoboCan/include")
 
LINK_LIBRARIES (PocoFoundation PocoUtil TBS TBS.Services HAL.API dbus-1 TBS.Robo TBS.Robo.RoboCan) 
 
add_executable(${PROJECT_NAME} ${EXE_SOURCES})
