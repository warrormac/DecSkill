cmake_minimum_required(VERSION 3.10)
project(DECSKILL)

set(CMAKE_CXX_STANDARD 17)

# Ensure headers are found
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add main executable
add_executable(DECSKILL 
    src/main.cpp 
    src/ModuleFactory.cpp 
    src/GeneratorModule.cpp 
    src/FilterModule.cpp 
    src/RecorderModule.cpp
)

# Enable testing
enable_testing()
add_subdirectory(tests)
