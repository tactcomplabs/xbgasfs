//
// _MDSServer_cpp_
// Copyright (C) 2017-2020 Tactical Computing Laboratories, LLC
// All Rights Reserved
//
// contact@tactcomplabs.com
//
// See LICENSE in the top level directory for licensing details
//

// Standard C++ Headers
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <list>
#include <fstream>

// Google logging mechanism
#include <glog/logging.h>

// GRPC++
#include <grpc++/grpc++.h>

// MDS Headers
//#include "MDSServiceImpl.hpp"

// BGASFS Headers
#include "BGASRPC/BGASRPC.hpp"

// Protocol Headers
#include "BGASRPC/bgasfs.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
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

class MDSServiceImpl final : public BGASFSMsg::Service {
  // Client ==> MDS: Request a file attribute
  Status ClientRqstFileAttr(ServerContext *context,
                            const FileAttrRqstMsg *request,
                            FileAttrRspMsg* reply) override {
    return Status::OK;
  }

  // Client ==> MDS: Update a file attribute
  Status ClientRqstUpdateFileAttr(ServerContext *context,
                                  const UpdateFileAttrRqstMsg* request,
                                  UpdateFileAttrRspMsg* reply) override {
    return Status::OK;
  }

  // Client ==> MDS: Initiate an I/O request
  Status ClientRqstIO(ServerContext *context,
                      const FileIORqstMsg* request,
                      FileIORspMsg* reply) override {
    return Status::OK;
  }

  // ---- UNDEFINED OPERATIONS ----
  Status ClientReadRqst(ServerContext *context,
                        const ClientIOReadRqstMsg* request,
                        ClientIOReadRspMsg* reply) override {
    return Status::CANCELLED;
  }

  Status ClientWriteRqst(ServerContext *context,
                         const ClientIOWriteRqstMsg* request,
                         ClientIOWriteRspMsg* reply) override {
    return Status::CANCELLED;
  }

  Status MDSDataPrefetch(ServerContext *context,
                         const DataPrefetchRqstMsg* request,
                         DataPrefetchRspMsg* reply) override {
    return Status::CANCELLED;
  }
};

/// MDS Server: Signal Handler
void handler(int signum){
  LOG(INFO) << "Exiting BGASFS MDS Server...";
  exit(EXIT_SUCCESS);
}

/// MDS Server: Daemon
void BGASMDSDaemon( std::string ServerAddress ){
  // create the child process
  pid_t pid = fork();

  if( pid < 0 ){
    LOG(FATAL) << "Could not create child process!";
    exit(EXIT_FAILURE);
  }

  // child process created, exit the parent
  if( pid > 0 ){
    exit(EXIT_SUCCESS);
  }

  // set the file permission for files created by the child
  umask(0);

  // create a session for the child
  pid_t sid = setsid();
  if( sid < 0 ){
    LOG(FATAL) << "Could not create session for child process!";
    exit(EXIT_FAILURE);
  }

  LOG(INFO) << "BGASFS MDS Server starting...";

  // close all the file descriptors
  fclose(stdin);
  fclose(stdout);
  fclose(stderr);

  // install our signal handler
  signal(SIGTERM, handler);

  // ignore signal when terminal session is closed
  signal(SIGHUP, SIG_IGN);

  // setup the server listener
  MDSServiceImpl service;

  // setup server and listen on the target port
  ServerBuilder builder;
  builder.AddListeningPort( ServerAddress, grpc::InsecureServerCredentials());

  // register the service
  builder.RegisterService(&service);

  // assemble the server
  std::unique_ptr<Server> server(builder.BuildAndStart());
  LOG(INFO) << "BGASFS MDS Server started on " << ServerAddress;

  // exeucte the server listener
  server->Wait();
}

/// MDS Server: Main
int main( int argc, char **argv ){

  // setup the logging
  google::InitGoogleLogging("BGASFS-MDS");
  google::SetLogDestination(google::INFO,  "/var/log/bgasfs/mds.log");
  google::SetLogDestination(google::FATAL, "/var/log/bgasfs/mds.log");
  google::SetLogDestination(google::ERROR, "/var/log/bgasfs/mds.log");

  // execute the daemon
  std::string ServerAddress;
  if( argc != 2 ){
    LOG(FATAL) << "Usage: MDSServer [ServerAddress]";
    return -1;
  }else{
    ServerAddress = std::string(argv[1]);
  }

  BGASMDSDaemon(ServerAddress);

  return 0;
}

// EOF
