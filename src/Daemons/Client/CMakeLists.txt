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
include_directories(${BGASFS_INCLUDE_PATH})
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(BGASFuseClient ${ClientSrcs})

target_link_libraries(BGASFuseClient BGASRPC BGASFSClient BGASFSConfig glog)

install(TARGETS BGASFuseClient RUNTIME DESTINATION bin)

#-- EOF
