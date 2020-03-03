#
# BGASFS/Src/Daemons/Client CMakeLists.txt
#
# Copyright (C) 2017-2020 Tactical Computing Laboratories, LLC
# All Rights Reserved
# contact@tactcomplabs.com
#
# See LICENSE in the top level directory for licensing details
#

set(ClientSrcs
  FuseClient.cpp
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


add_executable(BGASFuseClient ${ClientSrcs})

target_link_libraries(BGASFuseClient BGASRPC BGASFSClient BGASFSConfig glog)

install(TARGETS BGASFuseClient RUNTIME DESTINATION bin)

#-- EOF
