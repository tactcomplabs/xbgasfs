#
# BGASFS Top-Level CMakeLists.txt
#
# Copyright (C) 2017-2020 Tactical Computing Laboratories, LLC
# All Rights Reserved
# contact@tactcomplabs.com
#
# See LICENSE in the top level directory for licensing details
#

cmake_minimum_required(VERSION 3.4.3)
project(bgasfs)

# Require C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D_THREAD_SAFE")

# Debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -DDBEUG")

# Set the system type
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCOREGEN_PLATFORM=${CMAKE_SYSTEM_NAME}")
message(STATUS "Building for ${CMAKE_SYSTEM_NAME}")

# Set the include path
if(NOT BGASFS_INCLUDE_PATH)
  set(BGASFS_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/Libs/")
  message(STATUS "BGASFS_INCLUDE_PATH set to ${BGASFS_INCLUDE_PATH}")
endif()

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

# Find Doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the doxygen-ized API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

# Enable testing
enable_testing()

# Add subdirectories
add_subdirectory(src)
#add_subdirectory(test)

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

# ------------ BEGIN PACKAGING
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
# ------------ END PACKAGING

# EOF
