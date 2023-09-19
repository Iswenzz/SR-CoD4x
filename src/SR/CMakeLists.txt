cmake_minimum_required(VERSION 3.16.0)
project(SR VERSION 1.0.0 LANGUAGES CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-fpermissive -m32 -Wall -msse2 -mfpmath=sse -fno-omit-frame-pointer -fno-pie -O1 -Wno-packed-not-aligned -Wp,-w")

# NASM
if(WIN32)
	set(CMAKE_ASM_NASM_FLAGS "-dWin32 --prefix _")
	set(CMAKE_ASM_NASM_OBJECT_FORMAT "win32")
else()
	set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")
endif()
enable_language(ASM_NASM)

# CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR 7Z)
include(CPack)

# Dependencies
find_path(CGSC_INCLUDE_DIRS "CGSC/cgsc.h")
find_path(MINIMP3_INCLUDE_DIRS "minimp3/minimp3.h")
find_library(SAMPLERATE_LIBRARY libsamplerate.a)
find_package(CoD4DM1 CONFIG REQUIRED)
find_package(libuv CONFIG REQUIRED)
find_package(speex CONFIG REQUIRED)

# Build
add_library(SR)
add_subdirectory(commands)
add_subdirectory(game)
add_subdirectory(net)
add_subdirectory(player)
add_subdirectory(sys)
add_subdirectory(utils)

target_sources(SR PUBLIC SR.cpp)
target_precompile_headers(SR PUBLIC SR.hpp SR.h)
target_compile_definitions(SR PUBLIC COD4X18UPDATE)

target_link_libraries(SR PUBLIC
	CoD4DM1::CoD4DM1
	libuv::uv_a
	speex::speex
	${SAMPLERATE_LIBRARY})

target_include_directories(SR PUBLIC . .. ../version ../../plugins
	${CGSC_INCLUDE_DIRS}
	${MINIMP3_INCLUDE_DIRS})

get_target_property(SOURCES SR SOURCES)
set_target_properties(SR PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../../lib)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

get_target_property(COD4DM1_LIBRARY CoD4DM1::CoD4DM1 LOCATION)
get_target_property(LIBUV_LIBRARY libuv::uv_a LOCATION)
get_target_property(SPEEX_LIBRARY speex::speex LOCATION)

set(STATIC_DEPENDENCIES
	${COD4DM1_LIBRARY}
	${SPEEX_LIBRARY}
	${SAMPLERATE_LIBRARY}
	${LIBUV_LIBRARY})

foreach(dependency ${STATIC_DEPENDENCIES})
	add_custom_command(TARGET SR POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${dependency} ../../../lib)
endforeach()

# Install
install(TARGETS SR LIBRARY DESTINATION lib)
install(DIRECTORY src/ DESTINATION include/SR FILES_MATCHING PATTERN "*.hpp" PATTERN "__test__" EXCLUDE)
