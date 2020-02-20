#
# BGASFS/Src/Libs/BGASRPC CMakeLists.txt
#
# Copyright (C) 2017-2020 Tactical Computing Laboratories, LLC
# All Rights Reserved
# contact@tactcomplabs.com
#
# See LICENSE in the top level directory for licensing details
#

set(BGASRPCSrcs
  BGASRPC.hpp
  bgasfs.grpc.pb.h
  bgasfs.grpc.pb.cc
  bgasfs.pb.h
  bgasfs.pb.cc
)

include_directories(.)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_library(BGASRPC ${BGASRPCSrcs})
target_link_libraries(BGASRPC protobuf grpc++ grpc++_reflection dl)
set_target_properties(BGASRPC PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS BGASRPC ARCHIVE DESTINATION lib)

#-- EOF
