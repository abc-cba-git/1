set(CMAKE_TOOLCHAIN_FILE "путь/к/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
cmake_minimum_required(VERSION 3.10)
project(StrategyGame)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# TinyXML2
add_library(tinyxml2 STATIC extern/tinyxml2/tinyxml2.cpp)
target_include_directories(tinyxml2 PUBLIC extern/tinyxml2)

add_executable(StrategyGame
        src/main.cpp
        src/Unit.cpp
        src/GameMap.cpp
        src/Game.cpp
        src/GameUI.cpp
)

target_link_libraries(StrategyGame sfml-graphics sfml-window sfml-system tinyxml2)

# Копирование ресурсов
file(COPY data DESTINATION ${CMAKE_BINARY_DIR})