add_library(SR STATIC)

add_subdirectory(Audio)
add_subdirectory(Commands)
add_subdirectory(Demo)
add_subdirectory(Entity)
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
	Base.hpp
	Macros.hpp)

target_precompile_headers(SR PUBLIC Base.hpp)
target_compile_definitions(SR PUBLIC COD4X18UPDATE)

target_link_libraries(SR PUBLIC
	CoD4DM1::CoD4DM1
	libsamplerate::libsamplerate
	minimp3::minimp3
	speex::speex)

target_include_directories(SR PUBLIC
	.
	../..
	../../version
	../../../plugins)

# Tree
get_target_property(SOURCES SR SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# Install
install(TARGETS SR
	LIBRARY DESTINATION "${CMAKE_SOURCE_DIR}/../../lib"
	ARCHIVE DESTINATION "${CMAKE_SOURCE_DIR}/../../lib")

install(DIRECTORY ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib/
	DESTINATION "${CMAKE_SOURCE_DIR}/../../lib"
	FILES_MATCHING PATTERN "*.a"
	PATTERN "pkgconfig" EXCLUDE)
