file(TO_CMAKE_PATH $ENV{VCPKG_ROOT} VCPKG_ROOT)
set(VCPKG_TARGET_TRIPLET x86-linux-static)
include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
