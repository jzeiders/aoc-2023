cmake_minimum_required(VERSION 3.14)
project(AdventOfCode)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
FetchContent_MakeAvailable(googletest)


# Add source files
include_directories(src)
add_subdirectory(src)

# Test Files
enable_testing()
add_subdirectory(tests)

# Link with libraries if needed
# target_link_libraries(AdventOfCode some_library)
add_test (NAME MyTest COMMAND Test)
