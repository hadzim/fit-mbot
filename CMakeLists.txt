cmake_minimum_required(VERSION 2.6)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules") 

project (HALlibs)
 
SET(CMAKE_CXX_FLAGS "-std=c++0x") 
 
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/cbuild)
 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
 
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(PROJECT_ROOT ${PROJECT_SOURCE_DIR})
 
add_definitions(-DOLDPOCO13)

#include_directories("${PROJECT_INCLUDE_DIR}")
#include_directories("${PROJECT_SOURCE_DIR}")
 
add_subdirectory(TBS)
add_subdirectory(TBS.Services)
add_subdirectory(TBS.Robo)
add_subdirectory(TBS.Robo.RoboCan)
add_subdirectory(HAL.API)
add_subdirectory(HAL.Movement)
add_subdirectory(HAL.CanModules)
add_subdirectory(HAL.Client)
add_subdirectory(HAL.CvClient)
add_subdirectory(HAL.JoystickClient)
add_subdirectory(HAL.Observer)
#add_subdirectory(HAL.Remote)
#add_subdirectory(HAL.RemoteJoystickClient)
#add_subdirectory(HAL.RemoteClient)
