cmake_minimum_required(VERSION 3.16.0)
project(SR VERSION 1.0.0 LANGUAGES CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-fpermissive -m32 -Wall -msse2 -mfpmath=sse -fno-omit-frame-pointer -fno-pie -O1 -Wno-packed-not-aligned -Wp,-w")

# NASM
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
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

# Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Tests
if(ENABLE_TESTING)
	include(CTest)
	add_executable(SR.Tests)
	target_link_libraries(SR.Tests PUBLIC ${CONAN_LIBS} SR)
	add_test(NAME Tests COMMAND SR.Tests)
endif()

# Build
add_library(SR)

add_subdirectory(commands)
add_subdirectory(game)
add_subdirectory(net)
add_subdirectory(player)
add_subdirectory(utils)

target_sources(SR PUBLIC SR.cpp Macros.hpp)
target_link_libraries(SR PUBLIC ${CONAN_LIBS})
target_include_directories(SR PUBLIC . .. ../version ../../plugins ../CGSC)
target_precompile_headers(SR PUBLIC SR.hpp SR.h)
target_compile_definitions(SR PUBLIC COD4X18UPDATE)

get_target_property(SOURCES SR SOURCES)
set_target_properties(SR PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../../lib)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# Dependencies
set(STATIC_DEPENDENCIES
	# ${CONAN_LIB_DIRS_COD4DM1}/libCoD4DM1.a # Missing exported methods on conan package
	${CONAN_LIB_DIRS_SPEEX}/libspeex.a
	${CONAN_LIB_DIRS_LIBUV}/libuv_a.a)

foreach(dependency ${STATIC_DEPENDENCIES})
	add_custom_command(TARGET SR POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${dependency} ../../../lib)
endforeach()

# Pack
install(TARGETS SR LIBRARY DESTINATION lib)
install(DIRECTORY src/ DESTINATION lib/include/SR
    FILES_MATCHING PATTERN "*.hpp" PATTERN "__test__" EXCLUDE)
