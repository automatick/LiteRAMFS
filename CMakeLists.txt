cmake_minimum_required(VERSION 3.16)

project(LiteRamFS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(LiteRamFS main.cpp
    typedefs.hpp)

include(GNUInstallDirs)
install(TARGETS LiteRamFS
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
