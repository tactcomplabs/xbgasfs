//
// _BGASRPC_cpp_
// Copyright (C) 2017-2020 Tactical Computing Laboratories, LLC
// All Rights Reserved
//
// contact@tactcomplabs.com
//
// See LICENSE in the top level directory for licensing details
//

#include "BGASRPC.hpp"

BGASRPC::BGASRPC(std::shared_ptr<Channel> channel)
  : stub_(BGASFSMsg::NewStub(channel)) {
}

BGASRPC::~BGASRPC() {
}

bool BGASRPC::ClientRqstFileAttr( const std::string& file ){
  return true;
}

bool BGASRPC::ClientRqstUpdateFileAttr( const std::string& file,
                                        const uint32_t& v_st_dev,
                                        const uint32_t& v_st_mode,
                                        const uint32_t& v_st_nlink,
                                        const uint32_t& v_st_uid,
                                        const uint32_t& v_st_gid,
                                        const uint32_t& v_st_rdev,
                                        const uint32_t& v_st_size,
                                        const uint32_t& v_st_blksize,
                                        const uint32_t& v_st_atime,
                                        const uint32_t& v_st_mtime,
                                        const uint32_t& v_st_ctime ){
  return true;
}

bool BGASRPC::ClientRqstIO( const std::string& file,
                            const bool& write ){
  return true;
}

bool BGASRPC::ClientReadRqst( const std::string& file,
                              const uint64_t& offset,
                              const uint64_t& len ){
  return true;
}

bool BGASRPC::ClientWriteRqst( const std::string& file,
                               const uint64_t& offset,
                               const uint64_t& len ){
  return true;
}

bool BGASRPC::MDSDataPrefetch( const std::string& file,
                               const uint64_t& offset,
                               const uint64_t& len ){
  return true;
}

// EOF
