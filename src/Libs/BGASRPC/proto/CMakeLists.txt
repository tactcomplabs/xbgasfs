#
# BGASFS/Src/Libs/BGASRPC/proto CMakeLists.txt
#
# Copyright (C) 2017-2020 Tactical Computing Laboratories, LLC
# All Rights Reserved
# contact@tactcomplabs.com
#
# See LICENSE in the top level directory for licensing details
#

FIND_PACKAGE(Protobuf REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

FIND_PACKAGE(GRPC REQUIRED)
message(STATUS "Using protoc at ${PROTOBUF_PROTOC_EXECUTABLE}")

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#-- generate the CPP components
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS bgasfs.proto)

#-- generate the GRPC components
get_filename_component(hw_proto "bgasfs.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)
set(${hw_proto_path} ${CMAKE_CURRENT_BINARY_DIR})

#include_directories(${PROTO_HDRS})
include_directories(${XBGASFS_BUILD_DIR})

set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/bgasfs.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/bgasfs.grpc.pb.h")
set_source_files_properties("${hw_proto_path}/bgasfs.grpc.pb.cc"
                            "${hw_proto_path}/bgasfs.grpc.ph.h"
                            PROPERTIES GENERATED TRUE)
add_custom_command(
      OUTPUT "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
      COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}" -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN}
        "${hw_proto}"
      DEPENDS "${hw_proto}"
      COMMENT "Running GRPC protocol buffer compiler on ${hw_proto}"
      VERBATIM)


ADD_LIBRARY(ProtoObjs OBJECT ${PROTO_SRCS} ${PROTO_HDRS} ${hw_grpc_srcs} ${hw_grpc_hdrs})
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DESTINATION "include/BGASRPC/proto"
        FILES_MATCHING
        PATTERN "*.h")
install(DIRECTORY ${XBGASFS_BINARY_INCLUDE_PATH}
        DESTINATION "include/BGASRPC/proto"
        FILES_MATCHING
        PATTERN "*.h")

#-- EOF
