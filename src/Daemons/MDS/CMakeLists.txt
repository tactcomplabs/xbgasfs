#
# BGASFS/Src/Daemons/MDS CMakeLists.txt
#
# Copyright (C) 2017-2020 Tactical Computing Laboratories, LLC
# All Rights Reserved
# contact@tactcomplabs.com
#
# See LICENSE in the top level directory for licensing details
#

set(MDSSrcs
  MDSServer.cpp
)

include_directories(.)
include_directories(${BGASFS_INCLUDE_PATH})
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(BGASMDS ${MDSSrcs})

target_link_libraries(BGASMDS BGASRPC glog)

install(TARGETS BGASMDS RUNTIME DESTINATION bin)

#-- EOF
