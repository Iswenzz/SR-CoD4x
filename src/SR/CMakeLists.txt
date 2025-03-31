cmake_minimum_required(VERSION 3.27)
project(SR VERSION 1.0.0 LANGUAGES CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-fpermissive -m32 -Wall -msse2 -mfpmath=sse -fno-omit-frame-pointer -fno-pie -O1 -Wno-packed-not-aligned -Wp,-w")

# CMake
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(ClangTools)

# CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR 7Z)
include(CPack)

# Dependencies
find_path(MINIMP3_INCLUDE_DIRS "minimp3/minimp3.h")
find_library(SAMPLERATE_LIBRARY samplerate)
find_package(CoD4DM1 CONFIG REQUIRED)
find_package(libuv CONFIG REQUIRED)
find_package(speex CONFIG REQUIRED)

# Build
add_subdirectory(src)
