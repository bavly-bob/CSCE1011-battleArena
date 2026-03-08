cmake_minimum_required(VERSION 3.10)

project(BattleArena)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include header files
include_directories(include)

# Source files
set(SOURCES
    Main.cpp
    src/Archer.cpp
    src/Character.cpp
    src/Mage.cpp
    src/Warrior.cpp
)

# Create executable
add_executable(BattleArena ${SOURCES})