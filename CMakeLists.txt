cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")

project(ece205-lab14a-RPG-beta-Lei2024)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add the executable
add_executable(${PROJECT_NAME}
        main.cpp
        GameCharacter.cpp
        GameCharacter.hpp
        PlayerCharacter_ETHAN.cpp
        PlayerCharacterETHAN.hpp
        Hunter.cpp
        Hunter.hpp
        Bard.cpp
        Bard.hpp
        Blacksmith.cpp
        Blacksmith.hpp
        json.hpp
        Battle.cpp
        Battle.hpp
)



