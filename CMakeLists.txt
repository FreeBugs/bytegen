cmake_minimum_required(VERSION 3.8)
project(bytegen)

set(CMAKE_CXX_STANDARD 11)

MESSAGE( STATUS "ENV BOOST ROOT: " $ENV{BOOST_ROOT} )

find_package(Boost)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()
set (Boost_USE_STATIC_LIBS ON) # enable dynamic linking
set (Boost_USE_MULTITHREAD ON)  # enable multithreading
find_package (Boost COMPONENTS REQUIRED program_options system)

set(SOURCE_FILES main.cpp)
add_executable(bytegen ${SOURCE_FILES})

target_link_libraries(bytegen
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_STRING_LIBRARY}
        )