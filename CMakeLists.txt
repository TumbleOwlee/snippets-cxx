# Set version requirement
cmake_minimum_required(VERSION 3.16)

# Define project
project(snippets
    VERSION 0.0.1
    DESCRIPTION "Library providing various C++ snippets"
    LANGUAGES C CXX)

# Export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Set default to Debug
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif()
message("Build type: ${CMAKE_BUILD_TYPE}")

# Optionally switch to faster linker
find_program(MOLD mold)
if (MOLD)
    if (CMAKE_MAJOR_VERSION GREATER 2 OR (CMAKE_MAJOR_VERSION GREATER 1 AND CMAKE_MINOR_VERSION GREATER 28))
        set(CMAKE_LINKER_TYPE MOLD)
    else()
        set(CMAKE_CXX_FLAGS "-fuse-ld=mold")
    endif()
endif()


# Create list of all test files
set (TESTS_FILES
    "tests/unpacker.cxx"
    "tests/bitmask.cxx"
    "tests/routing.cxx"
)

enable_testing()
# Create target for each test
foreach(FILE IN LISTS TESTS_FILES)
    get_filename_component(TEST_NAME ${FILE} NAME_WE)
    add_executable(snippets-${TEST_NAME} ${FILE})
    target_include_directories(snippets-${TEST_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    add_test(NAME ${TEST_NAME} COMMAND snippets-${TEST_NAME})
endforeach()
