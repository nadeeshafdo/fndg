cmake_minimum_required(VERSION 3.10)
project(fndg C)

# Get version from git tag or use default
execute_process(
    COMMAND git describe --tags --always --dirty
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)
if(NOT GIT_VERSION)
    set(GIT_VERSION "v1.0.0")
endif()

# Set language standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.c
    ${CMAKE_SOURCE_DIR}/src/search.c
    ${CMAKE_SOURCE_DIR}/src/traverse.c
)

# Add executable
add_executable(fndg ${SOURCES})

# Include directories
target_include_directories(fndg PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Compiler flags
target_compile_options(fndg PRIVATE
    -Wall
    -Wextra
    -O3
)

# Strip binary in Release mode
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(fndg PRIVATE -s)
endif()

# Version definition
target_compile_definitions(fndg PRIVATE VERSION="${GIT_VERSION}")
target_compile_definitions(fndg PRIVATE _DEFAULT_SOURCE)

# Windows-specific settings
if(WIN32)
    # Link against Windows libraries for console support
    target_link_libraries(fndg PRIVATE kernel32)
endif()

# Installation
install(TARGETS fndg DESTINATION bin)

# Set build output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
