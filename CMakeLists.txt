cmake_minimum_required(VERSION 3.10)
project(AdventOfCode)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add source files
file(GLOB SRC_FILES "src/*.cpp")

# Include directories
include_directories(include)
# Add executable target
add_executable(AdventOfCode ${SRC_FILES})


# Link with libraries if needed
# target_link_libraries(AdventOfCode some_library)