cmake_minimum_required(VERSION 3.25)
project(piece_of_art)

set(CMAKE_CXX_STANDARD 14)

# Add the main executable and specify the source file
#add_executable(main_test ./src/main_test.cpp)
add_executable(crow_test ./src/crow_test.cpp)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(adaptive-radix-tree/include)
include_directories(adaptive-radix-tree/third_party/doctest/doctest)
include_directories(adaptive-radix-tree/third_party/picobench/include)
include_directories(adaptive-radix-tree/third_party/zipf/zipf.hpp)
include_directories(include)
include_directories(algorithm/include)
# Include the external library directory
add_subdirectory(adaptive-radix-tree)
add_subdirectory(algorithm)


# Link against the external library
#target_link_libraries(main_test PRIVATE art)
#target_link_libraries(main_test ${Boost_LIBRARIES})
target_link_libraries(crow_test PRIVATE art)
target_link_libraries(crow_test ${Boost_LIBRARIES})
