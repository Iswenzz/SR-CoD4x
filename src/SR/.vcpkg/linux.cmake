include(.vcpkg/cmake/env.cmake)
set(VCPKG_TARGET_TRIPLET x86-linux-static)
include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
