cmake_minimum_required(VERSION 4.5.0-rc2)

project(DLang)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_C_COMPILER)

set(SOURCE_FILES
    src/main.cpp    
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

