cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_MAKE_PROGRAM make)

# define output directory based on Android ABI
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/${ANDROID_ABI})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/${ANDROID_ABI})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/${ANDROID_ABI})

# define all hash logic in a library to use by main funtion and test methods
add_library(adjust_hash
		STATIC
		hasher.cpp)

set(SODIUM_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sodium_project-prefix/src/sodium_project)
# selecting libsodium output dir based on Android ABI
if("${ANDROID_ABI}" STREQUAL "x86")
	set(SODIUM_BUILD_DIR ${SODIUM_ROOT_DIR}/libsodium-android-i686)
elseif("${ANDROID_ABI}" STREQUAL "x86_64")
	set(SODIUM_BUILD_DIR ${SODIUM_ROOT_DIR}/libsodium-android-westmere)
elseif("${ANDROID_ABI}" STREQUAL "armv7-a")
	set(SODIUM_BUILD_DIR ${SODIUM_ROOT_DIR}/libsodium-android-armv7-a)
elseif("${ANDROID_ABI}" STREQUAL "armv8-a")
	set(SODIUM_BUILD_DIR ${SODIUM_ROOT_DIR}/libsodium-android-armv8-a)
else()
	message(FATAL_ERROR "ABI '${ANDROID_ABI}' not supported")
endif()

# Adding libsodium project as depenency for cross-compiling
include(ExternalProject)
ExternalProject_Add(sodium_project
		URL https://github.com/jedisct1/libsodium/releases/download/1.0.17/libsodium-1.0.17.tar.gz
		LOG_DOWNLOAD 1
		CONFIGURE_COMMAND ""
		INSTALL_COMMAND ""
		BUILD_COMMAND sh -c cd ${SODIUM_ROOT_DIR} && export ANDROID_NDK_HOME=${ANDROID_NDK} && ./dist-build/android-${ANDROID_ABI}.sh
		BUILD_IN_SOURCE 1
		BUILD_BYPRODUCTS ${SODIUM_BUILD_DIR}/lib/libsodium.so)

# define sodium library and sodium project as a dependency
add_library(sodium STATIC IMPORTED)
add_dependencies(sodium sodium_project)
set_target_properties(sodium PROPERTIES IMPORTED_LOCATION ${SODIUM_BUILD_DIR}/lib/libsodium.a )
include_directories(${SODIUM_BUILD_DIR}/include)

# adding log library
find_library(log-lib log)

# adding required dependencies that are needed by hash logic
target_link_libraries(adjust_hash sodium ${log-lib})

# define binary
add_executable(hasher main.cpp)
target_link_libraries(hasher adjust_hash)


#adding google test from NDK
enable_testing()
set(GOOGLETEST_ROOT ${ANDROID_NDK}/sources/third_party/googletest)
add_library(gtest STATIC ${GOOGLETEST_ROOT}/src/gtest_main.cc ${GOOGLETEST_ROOT}/src/gtest-all.cc)
target_include_directories(gtest PRIVATE ${GOOGLETEST_ROOT})
target_include_directories(gtest PUBLIC ${GOOGLETEST_ROOT}/include)

add_executable(unittest test/unittest.cpp)
target_include_directories(unittest PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(unittest gtest adjust_hash)

add_test(AllTests dist/${ANDROID_ABI}/unittest)

