cmake_minimum_required(VERSION 3.10)
project(restbl VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(ABSL_WAITER_MODE 0)

include(CTest)
enable_testing()

add_library(restbl STATIC
    ./src/restbl.cpp
    ./src/include/restbl/restbl.h
)

target_include_directories(restbl PUBLIC ./src/include)

if(MSVC)
    target_compile_options(restbl PRIVATE /W4 /wd4244 /wd4127 /Zc:__cplusplus)
else()
    target_compile_options(restbl PRIVATE -Wall -Wextra -fno-plt)
endif()

set(BUILD_TESTING ON)
add_subdirectory(./lib/abseil)
add_subdirectory(./lib/ExtendedIO)
target_link_libraries(restbl
    PUBLIC
    ExtendedIO
    absl::flat_hash_map
    PRIVATE
)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
