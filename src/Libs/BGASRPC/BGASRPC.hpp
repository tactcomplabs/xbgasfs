//
// _BGASRPC_hpp_
// Copyright (C) 2017-2020 Tactical Computing Laboratories, LLC
// All Rights Reserved
//
// contact@tactcomplabs.com
//
// See LICENSE in the top level directory for licensing details
//

#ifndef _BGASRPC_HPP_
#define _BGASRPC_HPP_

// Standard C++ Headers
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

// GRPC Headers
#include <grpc++/grpc++.h>

// Protocol Headers
#include "BGASRPC/proto/bgasfs.grpc.pb.h"

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using bgasfsmsg::FileAttrRqstMsg;
using bgasfsmsg::FileAttrRspMsg;
using bgasfsmsg::UpdateFileAttrRqstMsg;
using bgasfsmsg::UpdateFileAttrRspMsg;
using bgasfsmsg::FileIORqstMsg;
using bgasfsmsg::FileIORspMsg;
using bgasfsmsg::ClientIOReadRqstMsg;
using bgasfsmsg::ClientIOReadRspMsg;
using bgasfsmsg::ClientIOWriteRqstMsg;
using bgasfsmsg::ClientIOWriteRspMsg;
using bgasfsmsg::DataPrefetchRqstMsg;
using bgasfsmsg::DataPrefetchRspMsg;
using bgasfsmsg::BGASFSMsg;

class BGASRPC{
public:

  /// BGASRPC: Constructor
  BGASRPC(std::shared_ptr<Channel> channel);

  /// BGASRPC: Destructor
  ~BGASRPC();

  bool ClientRqstFileAttr( const std::string& file );

  bool ClientRqstUpdateFileAttr( const std::string& file,
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
                                 const uint32_t& v_st_ctime );

  bool ClientRqstIO( const std::string& file,
                     const bool& write );

  bool ClientReadRqst( const std::string& file,
                       const uint64_t& offset,
                       const uint64_t& len );

  bool ClientWriteRqst( const std::string& file,
                        const uint64_t& offset,
                        const uint64_t& len );

  bool MDSDataPrefetch( const std::string& file,
                        const uint64_t& offset,
                        const uint64_t& len );

private:
  std::unique_ptr<BGASFSMsg::Stub> stub_; ///< Message handler stubs
};

#endif

// EOF
