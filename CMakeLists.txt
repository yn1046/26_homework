cmake_minimum_required(VERSION 3.23)
project(26_homework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(26_homework main.cpp)

include(FindPkgConfig)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(Threads REQUIRED)
    pkg_check_modules(TBB REQUIRED tbb)
endif()

# ...

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(26_homework PRIVATE Threads::Threads ${CMAKE_DL_LIBS} ${TBB_LIBRARIES})
endif()