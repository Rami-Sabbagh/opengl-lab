cmake_minimum_required (VERSION 3.28)
project("opengl-lab" LANGUAGES CXX)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# --== Prebuilt Packages Configuration ==-- #

option(USE_PREBUILT_LIBS "Use pre-build dependencies binaries if available" ON)
# Disable if you want to force the building of SFML from source on Windows 64-bit.

# Determine compiler and architecture
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" AND CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(PREBUILT_LIBS_PREFIX "msvc-x64")
endif()

if (USE_PREBUILT_LIBS AND PREBUILT_LIBS_PREFIX)
    set(PREBUILT_LIBS_PATH "${CMAKE_SOURCE_DIR}/dependencies/prebuilt/${PREBUILT_LIBS_PREFIX}")
endif()

if(EXISTS ${PREBUILT_LIBS_PATH})
    list(PREPEND CMAKE_PREFIX_PATH ${PREBUILT_LIBS_PATH})
else()
    set(USE_PREBUILT_LIBS OFF)
endif()

# --== Dependencies ==-- #

#list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/dependencies)
set(SFML_STATIC_LIBRARIES ON)
set(GLM_ENABLE_CXX_17 ON)

if(USE_PREBUILT_LIBS)
    message("Using prebuilt libraries.")

    find_package(SFML 3 COMPONENTS Window REQUIRED)
else()
    message("Using fetched libraries.")

    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
    FetchContent_MakeAvailable(SFML)
endif()

add_subdirectory("dependencies/glad" EXCLUDE_FROM_ALL)
add_subdirectory("dependencies/glm-1.0.2" EXCLUDE_FROM_ALL)

# --== Internal Libraries ==-- #

add_subdirectory("lib/lab-utils")

# --== Executables ==-- #

include(cmake/AddLabExecutable.cmake)

add_subdirectory("lectures/01")
add_subdirectory("lectures/02")
