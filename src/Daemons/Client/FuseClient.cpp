//
// _FuseClient_cpp_
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

// BGASFS Headers
#include "BGASRPC/BGASRPC.hpp"
#include "BGASFSClient/BGASFSClient.hpp"
#include "BGASFSConfig/BGASFSConfig.hpp"

// Protocol Headers
#include "BGASRPC/proto/bgasfs.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
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

// Globals
BGASFSConfig *Config;

/// FuseClient: Signal Handler
void handler(int signum){
  LOG(INFO) << "Existing BGASFuseClient...";
  exit(EXIT_SUCCESS);
}

/// FuseClient: Daemon
void FuseClientDaemon(std::string ServerConfig){

  // read the server config
  Config = new BGASFSConfig( ServerConfig );
  if( !Config->IsInit() ){
    delete Config;
    LOG(FATAL) << "Error reading configuration file: " << ServerConfig;
    exit(EXIT_FAILURE);
  }

  // create the child process
  pid_t pid = fork();

  if( pid < 0 ){
    LOG(FATAL) << "Could not create child process!";
    delete Config;
    exit(EXIT_FAILURE);
  }

  // child process created, exit the parent
  if( pid > 0 ){
    delete Config;
    exit(EXIT_SUCCESS);
  }

  // set the file permission for the files created by the child
  umask(0);

  // create a session for the child
  pid_t sid = setsid();
  if( sid < 0 ){
    LOG(FATAL) << "Could not create session for child process!";
    delete Config;
    exit(EXIT_FAILURE);
  }

  LOG(INFO) << "BGASFS Fuse Client starting...";

  // close all the file descriptors
  fclose(stdin);
  fclose(stdout);
  fclose(stderr);

  // install our signal handler
  signal(SIGTERM, handler);

  // ignore signal when terminal session is closed
  signal(SIGHUP, SIG_IGN);

  // server is setup, start the file system
}

/// FuseClient: Main
int main( int argc, char **argv ){

  // setup the logging
  google::InitGoogleLogging("BGASFS-FuseClient");
  google::SetLogDestination(google::INFO,   "/var/log/bgasfs/client.log");
  google::SetLogDestination(google::FATAL,  "/var/log/bgasfs/client.log");
  google::SetLogDestination(google::ERROR,  "/var/log/bgasfs/client.log");

  // execute the daemon
  std::string ServerAddress;
  std::string ServerConfig;
  if( argc != 2 ){
    LOG(FATAL) << "Usage: BGASFuseClient [ServerConfig]";
    return -1;
  }else{
    ServerConfig = std::string(argv[1]);
  }

  FuseClientDaemon(ServerConfig);

  return 0;
}

// EOF
