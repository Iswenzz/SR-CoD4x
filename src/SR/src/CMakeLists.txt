add_library(SR STATIC)

add_subdirectory(Audio)
add_subdirectory(Commands)
add_subdirectory(Demo)
add_subdirectory(Entity)
add_subdirectory(Macros)
add_subdirectory(Network)
add_subdirectory(Player)
add_subdirectory(Server)
add_subdirectory(System)
add_subdirectory(Utils)

# Build
target_sources(SR PRIVATE
	API.cpp
	API.hpp
	Application.cpp
	Application.hpp
	Base.hpp)

target_precompile_headers(SR PUBLIC Base.hpp)
target_compile_definitions(SR PUBLIC COD4X18UPDATE)

target_link_libraries(SR PUBLIC
	CoD4DM1::CoD4DM1
	libuv::uv_a
	speex::speex
	${SAMPLERATE_LIBRARY})

target_include_directories(SR PUBLIC
	.
	../..
	../../version
	../../../plugins
	${MINIMP3_INCLUDE_DIRS})

# Tree
get_target_property(SOURCES SR SOURCES)
set_target_properties(SR PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ../../../../lib)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# Dependencies
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
		COMMAND ${CMAKE_COMMAND} -E copy ${dependency} ../../../../lib)
endforeach()
