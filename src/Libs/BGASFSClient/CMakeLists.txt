#
# BGASFS/Src/Libs/BGASFSClient CMakeLists.txt
#
# Copyright (C) 2017-2020 Tactical Computing Laboratories, LLC
# All Rights Reserved
# contact@tactcomplabs.com
#
# See LICENSE in the top level directory for licensing details
#

set(BGASFSClientSrcs
  BGASFSClient.hpp
  BGASFSClient.cpp
)

include_directories(.)
include_directories(/usr/local/include)
include_directories(${GRPC_INCLUDE_PATH})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${XBGASFS_BUILD_DIR})
include_directories(${XBGASFS_INCLUDE_PATH})
include_directories(${XBGASFS_BINARY_INCLUDE_PATH})
link_directories(/usr/local/lib)
link_directories(${GRPC_LIB_PATH})

add_library(BGASFSClient ${BGASFSClientSrcs})
target_link_libraries(BGASFSClient protobuf grpc++ grpc++_reflection dl)
set_target_properties(BGASFSClient PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS BGASFSClient ARCHIVE DESTINATION lib)
install(DIRECTORY "."
        DESTINATION "include/BGASFSClient"
        FILES_MATCHING
        PATTERN "*.hpp")

#-- EOF
