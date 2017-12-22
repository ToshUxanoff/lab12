cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
include(cmake/HunterGate.cmake)

HunterGate(
    URL "https://github.com/ToshUxanoff/hunter/archive/v0.19.137.3.tar.gz"
    SHA1 17257ab891b12b911b54b67e4f8592b0d51485bd
)
project(cget)

hunter_add_package(CURL)
find_package(CURL CONFIG REQUIRED)
add_executable(cget ${CMAKE_CURRENT_SOURCE_DIR}/cget.cpp)
target_link_libraries(cget CURL::libcurl)
install(TARGETS cget RUNTIME DESTINATION bin)
