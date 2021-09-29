cmake_minimum_required(VERSION 3.13)

project(voice-filters)

file(GLOB_RECURSE PROJECT_SOURCE_FILES "src/*.h" "src/*.cpp")

macro(GroupSources curdir groupindex)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)

    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            GroupSources(${curdir}/${child} ${groupindex}/${child})
        else()
            string(REPLACE "/" "\\" groupname ${groupindex})
            source_group(${groupname} FILES ${curdir}/${child})
        endif()
    endforeach()
endmacro()

GroupSources(${CMAKE_SOURCE_DIR}/src "Source Files")

add_library(voice-filters SHARED ${PROJECT_SOURCE_FILES})

include_directories(
    ./src
)

set_target_properties(voice-filters PROPERTIES
    OUTPUT_NAME "voice-filters"
    SUFFIX ".dll"
    CXX_STANDARD 20
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/BIN/"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/BIN/Debug/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/BIN/Release/"
)

set(CMAKE_CONFIGURATION_TYPES Debug Release)

target_include_directories(voice-filters PRIVATE
    ./cpp-sdk
)