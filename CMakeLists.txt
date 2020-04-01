#
# BGASFS Top-Level CMakeLists.txt
#
# Copyright (C) 2017-2020 Tactical Computing Laboratories, LLC
# All Rights Reserved
# contact@tactcomplabs.com
#
# See LICENSE in the top level directory for licensing details
#

#------------------------------------------------------------------------
#-- CMAKE PROJECT INFO
#------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.4.3)
project(bgasfs)

#------------------------------------------------------------------------
#-- EXTERNAL CMAKE SCRIPTS
#------------------------------------------------------------------------
set(CMAKE_MODULE_PATH
  "${CMAKE_SOURCE_DIR}/cmake"
  ${CMAKE_MODULE_PATH}
)
include(UseLATEX OPTIONAL)
#include(FindGRPC REQUIRED)
include(FindProtobuf REQUIRED)

#------------------------------------------------------------------------
#-- COMPILER OPTIONS
#------------------------------------------------------------------------

# Require C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D_THREAD_SAFE")

# Debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -DDBEUG")

# Set the system type
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCOREGEN_PLATFORM=${CMAKE_SYSTEM_NAME}")
message(STATUS "Building for ${CMAKE_SYSTEM_NAME}")

# Set the gRPC paths
if(NOT GRPC_INSTALL_PATH)
  set(GRPC_LIB_PATH "/usr/local/lib")
  set(GRPC_INCLUDE_PATH "/usr/local/include")
else()
  set(GRPC_LIB_PATH "${GRPC_INSTALL_PATH}/lib")
  set(GRPC_INCLUDE_PATH "${GRPC_INSTALL_PATH}/include")
endif()

message(STATUS "GRPC_LIB_PATH set to ${GRPC_LIB_PATH}")
message(STATUS "GRPC_INCLUDE_PATH set to ${GRPC_INCLUDE_PATH}")

# Set the libFuse paths
if( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
  # -- OSX Darwin
  if(NOT FUSE_INSTALL_PATH)
    set(FUSE_INCLUDE_PATH "/usr/local/include/osxfuse/fuse")
    set(FUSE_LIB_PATH "/usr/local/lib")
  else()
    set(FUSE_INCLUDE_PATH "${FUSE_INSTALL_PATH}/osxfuse/fuse")
    set(FUSE_LIB_PATH "${FUSE_INSTALL_PATH}/lib")
  endif()
  set(FUSE_CFLAGS "-DFUSE_USE_VERSION=26 -D_FILE_OFFSET_BITS=64 -D_DARWIN_USE_64_BIT_INODE")
  set(FUSE_LIBS "osxfuse")
else()
  # -- Linux/BSD
endif()

message(STATUS "FUSE_INCLUDE_PATH set to ${FUSE_INCLUDE_PATH}")
message(STATUS "FUSE_CFLAGS set to ${FUSE_CFLAGS}")
message(STATUS "FUSE_LIBS set to ${FUSE_LIBS}")

if(NOT XBGASFS_BUILD_DIR)
  set(XBGASFS_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")
  message(STATUS "XBGASFS_BUILD_DIR set to ${XBGASFS_BUILD_DIR}")
endif()

if(NOT XBGASFS_INCLUDE_PATH)
  set(XBGASFS_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/Libs")
  message(STATUS "XBGASFS_INCLUDE_PATH set to ${XBGASFS_INCLUDE_PATH}")
endif()

if(NOT XBGASFS_BINARY_INCLUDE_PATH)
  set(XBGASFS_BINARY_INCLUDE_PATH "${CMAKE_CURRENT_BINARY_DIR}/src/Libs")
  message(STATUS "XBGASFS_BINARY_INCLUDE_PATH set to ${XBGASFS_BINARY_INCLUDE_PATH}")
endif()

# Check for memory sanity checks
if(XBGASFS_MEMORY_SANITY)
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message(STATUS "Memory sanitizier is suitable for use with Clang")
  elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    message(STATUS "Memory sanitizier is suitable for use with AppleClang")
  else()
    message(FATAL_ERROR "Clang is required to build using memory sanitizer.")
  endif()
  unset(CMAKE_CXX_FLAGS)
  set(CMAKE_CXX_FLAGS "-std=c++11 -D_THREAD_SAFE -O1 -g -Wall -stdlib=libc++ -fsanitize=address -fno-omit-frame-pointer")
  message(STATUS "CMAKE_CXX_FLAGS set to ${CMAKE_CXX_FLAGS}")
endif()

#------------------------------------------------------------------------
#-- EXTERNAL PACKAGES
#------------------------------------------------------------------------
# Find Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the doxygen-ized API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

#------------------------------------------------------------------------
#-- TESTING
#------------------------------------------------------------------------
enable_testing()

#------------------------------------------------------------------------
#-- DOCUMENTATION
#------------------------------------------------------------------------
# Doxygen config
if(BUILD_DOCUMENTATION)
  if( NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is required to build the documentation.")
  endif()

  set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/doxygen.conf)

  add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM)

  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/html DESTINATION share/doc)
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/man DESTINATION share/man)
endif()

#------------------------------------------------------------------------
#-- PACKAGING OPTIONS
#------------------------------------------------------------------------
if(BUILD_DEB)
  SET(CPACK_GENERATOR "DEB")
  SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "John Leidel: jleidel@tactcomplabs.com")
  SET(CPACK_DEBIAN_PACKAGE_NAME "bgasfs")
  SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libgoogle-glog-dev")
  SET(CPACK_PACKAGE_VENDOR "Tactical Computing Laboratories, LLC")
  INCLUDE(CPack)
endif()
if(BUILD_SRC)
  SET(CPACK_CMAKE_GENERATOR "Unix Makefiles")
  SET(CPACK_GENERATOR "STGZ;TGZ;TZ")
  SET(CPACK_PACKAGE_VENDOR "Tactical Computing Laboratories, LLC")
  SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "xBGAS File System")
  SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
  SET(CPACK_PACKAGE_VERSION_MAJOR "0")
  SET(CPACK_PACKAGE_VERSION_MINOR "0")
  SET(CPACK_PACKAGE_VERSION_PATCH "1")
  INCLUDE(CPack)
endif()


#------------------------------------------------------------------------
#-- SUBDIRECTORIES
#------------------------------------------------------------------------
add_subdirectory(src)
#add_subdirectory(test)

# EOF
