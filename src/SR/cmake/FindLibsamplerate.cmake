find_path(LIBSAMPLERATE_INCLUDE_DIR "samplerate.h")
find_library(LIBSAMPLERATE_LIB samplerate)

set(LIBSAMPLERATE_LIBS
	${LIBSAMPLERATE_LIB})

set(LIBSAMPLERATE_INCLUDE_DIRS
	${LIBSAMPLERATE_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Libsamplerate DEFAULT_MSG LIBSAMPLERATE_LIBS LIBSAMPLERATE_INCLUDE_DIRS)
mark_as_advanced(LIBSAMPLERATE_LIBS LIBSAMPLERATE_INCLUDE_DIRS)

if(NOT TARGET libsamplerate::libsamplerate)
	add_library(libsamplerate::libsamplerate INTERFACE IMPORTED)
    set_property(TARGET libsamplerate::libsamplerate PROPERTY INTERFACE_LINK_LIBRARIES "${LIBSAMPLERATE_LIBS}")
	set_property(TARGET libsamplerate::libsamplerate PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${LIBSAMPLERATE_INCLUDE_DIRS}")
endif()
