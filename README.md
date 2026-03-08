# BattleArena (CSCE1011)

A C++ console game that simulates a multi-round battle tournament using object-oriented programming concepts.

## Overview

Players create fighters, assign each one a class (`Warrior`, `Mage`, or `Archer`), and run a randomized arena simulation. In each round, two living characters are selected, one attacks (normal attack or special ability), and the game continues until rounds end or too few fighters remain.

The program then prints a final scoreboard and determines the winner (or offers tie-breaker rounds if multiple fighters survive).

## Features

- Polymorphic character system with an abstract base class (`Character`)
- Three playable classes with unique stats and special abilities
- Round-based random battle flow
- End-of-game statistics:
  - attacks performed
  - special abilities used
  - damage dealt
  - damage taken
  - alive/defeated status
- Optional tie-breaker mode when multiple survivors remain

## Character Classes

- `Warrior`
  - Health: `140`
  - Attack: `30`
  - Special: `Power Strike` (`+12` damage)
- `Mage`
  - Health: `80`
  - Attack: `35`
  - Special: `Arcane Storm` (`+20` damage)
- `Archer`
  - Health: `100`
  - Attack: `45`
  - Special: `Double Shot` (`2x` attack damage)

## Project Structure

```text
.
|-- CMakeLists.txt
|-- Main.cpp
|-- include/
|   |-- Character.h
|   |-- Warrior.h
|   |-- Mage.h
|   `-- Archer.h
`-- src/
    |-- Character.cpp
    |-- Warrior.cpp
    |-- Mage.cpp
    `-- Archer.cpp
```

## Build Instructions (CMake)

### Prerequisites

- CMake `3.10+`
- A C++17-compatible compiler (MSVC, GCC, or Clang)

### Build

```bash
cmake -S . -B build
cmake --build build
```

### Run

On Windows (common paths):

```powershell
.\build\BattleArena.exe
# or (Visual Studio generator):
.\build\Debug\BattleArena.exe
```

On Linux/macOS:

```bash
./build/BattleArena
```

## How to Play

1. Launch the game and choose `Start game`.
2. Enter number of characters and their names/classes.
3. Choose number of combat rounds.
4. Review final scoreboard and winner announcement.
5. If multiple survivors remain, optionally continue with tie-breaker rounds.

## Authors

- Bavly Attallah (`900251714`)
- Moataz Badawy (`900244214`)
