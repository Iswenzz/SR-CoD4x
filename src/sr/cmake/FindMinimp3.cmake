find_path(MINIMP3_INCLUDE_DIR "minimp3/minimp3.h")

set(MINIMP3_INCLUDE_DIRS
	${MINIMP3_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Minimp3 DEFAULT_MSG MINIMP3_INCLUDE_DIRS)
mark_as_advanced(MINIMP3_INCLUDE_DIRS)

if(NOT TARGET minimp3::minimp3)
	add_library(minimp3::minimp3 INTERFACE IMPORTED)
	set_property(TARGET minimp3::minimp3 PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${MINIMP3_INCLUDE_DIRS}")
endif()
