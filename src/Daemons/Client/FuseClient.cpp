//
// _FuseClient_cpp_
//
// Copyright (C) 2017-2020 Tactical Computing Laboratories, LLC
// All Rights Reserved
//
// contact@tactcomplabs.com
//
// See LICENSE in the top level directory for licensing details
//

//#define FUSE_USE_VERSION 31

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifdef linux
#define _XOPEN_SOURCE 700
#endif

// Standard C/C++ Headers
#include <fuse.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <dirent.h>
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <list>
#include <fstream>


#ifdef __FreeBSD__
#include <sys/socket.h>
#include <sys/un.h>
#endif

#ifdef HAVE_SETXATTR
#include <sys/xattr.h>
#endif

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

struct xmp{
  int case_insensitive;
};

static struct xmp xmp;

static const struct fuse_opt xmp_opts[] = {
  {"case_insensitive", offsetof(struct xmp, case_insensitive), 1},
  FUSE_OPT_END
};

/// FuseClient: xmp_init
static void *xmp_init(struct fuse_conn_info *conn){
  if( !Config ){
    delete Config;
    LOG(FATAL) << "BGASFS configuration is null";
    exit(EXIT_FAILURE);
  }

#if 0
  FUSE_ENABLE_SETVOLNAME(conn);
  FUSE_ENABLE_XTIMES(conn);
#endif

#ifdef FUSE_ENABLE_CASE_INSENSITIVE
  if( xmp.case_insensitive ){
    FUSE_ENABLE_CASE_INSENSITIVE(conn);
  }
#endif

  return NULL;
}

/// FuseClient: xmp_getattr
static int xmp_getattr(const char *path, struct stat *stbuf){

  //
  // Similar in struture to the 'stat()' function.
  // Must fill in all the fields of *stbuf except
  // the st_dev and st_blksize fields.
  //
  // This will require the ClientRqstFileAttr protocol
  //

  return 0;
}

/// FuseClient: xmp_access
static int xmp_access(const char *path, int mask){

  //
  // Called for the 'access()' system call.
  // If the 'default_permissions' mount option is given, this is
  // not called.
  //
  // This will require the ClientRqstFileAttr protocol as it checks
  // the accessibility of the file
  //

  return 0;
}

/// FuseClient: xmp_readlink
static int xmp_readlink(const char *path, char *buf, size_t size){

  //
  // Buffer should be a null terminated string, but check it anyway
  // The return value should be 0 on success
  //
  // This is similar to 'getattr()', but it follows the symlink
  // instead of the link itself.  This will require the ClientRqstFileAttr
  //

  return 0;
}

/// FuseClient: xmp_readdir
static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi){

  //
  // This may have multiple implementations, but the best likely implementation
  // is that readdir ignores the offset parameter and passes zero to the filler
  // function's offset.  The filler function will not return '1' (unless error
  // occurs) so tht whole directory is read in a single readdir operation.
  //
  // ClientRqstIO + some notional internal cache
  //

  return 0;
}

/// FuseClient: xmp_mknod
static int xmp_mknod(const char *path, mode_t mode, dev_t rdev){

  //
  // This is called for all non-directory, non-symlink nodes.
  // If the filesystme defines a create() method, then it will be called for
  // regular files instead.
  //
  // We need a new protocol handler for this... unless we cache the request
  // locally before writing to the new file
  //

  return 0;
}

/// FuseClient: xmp_mkdir
static int xmp_mkdir(const char *path, mode_t mode){

  //
  // Creates a directory on the target path
  //
  // MkdirRqstMsg protocol
  //

  return 0;
}

/// FuseClient: xmp_unlink
static int xmp_unlink(const char *path){
  //
  // Removes a file
  //
  // FileRmRqstMsg protocol
  //

  return 0;
}

/// FuseClient: xmp_rmdir
static int xmp_rmdir(const char *path){
  //
  // Removes a directory
  //
  // This definitely needs a new protocol handler
  //
  // FileRmRqstmsg protocol
  //
  return 0;
}

/// FuseClient: xmp_symlink
static int xmp_symlink(const char *from, const char *to){
  //
  // Creates a symbolic link
  //
  // FileLinkRqstMsg protocol
  //
  return 0;
}

/// FuseClient: xmp_rename
static int xmp_rename(const char *from, const char *to){
  //
  // Renames a file or directory
  //
  // FileRenameRqstMsg protocol
  //
  return 0;
}

/// FuseClient: xmp_link
static int xmp_link(const char *from, const char *to){
  //
  // Create a hard link to a file
  //
  // FileRenameRqstMsg protocol
  //
  return 0;
}

/// FuseClient: xmp_chmod
static int xmp_chmod(const char *path, mode_t mode){
  //
  // Changes the file/directory mode
  //
  // This should use the 'ClientRqstUpdateFileAttr' protocol
  //
  return 0;
}

/// FuseClient: xmp_chown
static int xmp_chown(const char *path, uid_t uid, gid_t gid){
  //
  // Changes the file/directory ownership
  //
  // This should use the 'ClientRqstUpdateFileAttr' protocol
  //
  return 0;
}

/// FuseClient: xmp_truncate
static int xmp_truncate(const char *path, off_t size){
  //
  // Change the size of a file.
  //
  // We may be able to use the `ClientRqstUpdateFileAttr` and update
  // the file size.  We may need to add an additional flag to trigger the
  // truncate operation rather than updating the remainder of the values
  //
  return 0;
}

#ifdef HAVE_UTIMENSAT
/// FuseClient: xmp_utimens
static int xmp_utimens(const char *path, const struct timespec ts[2],
		       struct fuse_file_info *fi){
  //
  // Change the access and modification time for the target file
  //
  // We may be able to reuse the `ClientRqstUpdateFileAttr` protocol.
  // However, the time set is relative to the client system triggering
  // the call... not the metadata server or the data server.  Other
  // file systems have similar issues with distributed time keeping.
  // We may need to implement some notional Lamport clock in order to
  // help soften the time shift between systems.
  //
  return 0;
}
#endif // HAVE_UTIMENSAT

/// FuseClient: xmp_create
static int xmp_create(const char *path, mode_t mode,
		      struct fuse_file_info *fi){
  //
  // create and open the file
  //
  // FileCreateRqstMsg
  //
  return 0;
}

/// FuseClient: xmp_open
static int xmp_open(const char *path, struct fuse_file_info *fi){
  //
  // opens a file
  // Use the following flags:
  // - Creation (O_CREAT, O_EXCL, O_NOCTTY)
  // - Access modes (O_RDONLY, O_WRONLY, O_RDWR, O_EXEC, O_SEARCH)
  //
  // This will likely be coupled to `ClientRqstIO`
  //
  return 0;
}

/// FuseClient: xmp_read
static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi){
  //
  // Read the target number of bytes from the file
  //
  // Will require `ClientRqstIO` + `ClientReadRqst`
  // These may be combined in the future
  //
  return 0;
}

/// FuseClient: xmp_write
static int xmp_write(const char *path, const char *buf, size_t size,
		     off_t offset, struct fuse_file_info *fi){
  //
  // Write the target number of bytes to the file
  //
  // Will require `ClientRqstIO` + `ClientWriteRqst`
  // These may be combined in the future
  //
  return 0;
}

/// FuseClient: xmp_statfs
static int xmp_statfs(const char *path, struct statvfs *stbuf){
  //
  // Retrieve the file system statistics
  //
  // FSStatRqstMsg protocol
  //
  return 0;
}

/// FuseClient: xmp_release
static int xmp_release(const char *path, struct fuse_file_info *fi){
  //
  // Called as the completed to 'open'
  // Signals that there are no open/used references for this file descriptor
  //
  // FileReleaseRqst protocol
  //
  return 0;
}

/// FuseClient: xmp_fsync
static int xmp_fsync(const char *path, int isdatasync,
		     struct fuse_file_info *fi){
  //
  // Syncs the file system
  //
  // If the datasync parameter is non-zero, then only the user data
  // is synced, not the metadata (data is written back to data servers)
  //
  return 0;
}

#ifdef HAVE_POSIX_FALLOCATE
/// FuseClient: xmp_fallocate
static int xmp_fallocate(const char *path, int mode,
			off_t offset, off_t length, struct fuse_file_info *fi){
  //
  // Allocates space for the open file
  //
  // FileIORqstMsg
  //
  return 0;
}
#endif // HAVE_POSIX_FALLOCATE

#ifdef HAVE_SETXATTR
/// FuseClient: xmp_setxattr
static int xmp_setxattr(const char *path, const char *name, const char *value,
			size_t size, int flags){
  //
  // Set the extended attributes
  //
  // A new protocol?  Not sure here... Need more research into what the
  // extended values are
  //
  return 0;
}

/// FuseClient: xmp_getxattr
static int xmp_getxattr(const char *path, const char *name, char *value,
			size_t size){
  //
  // Retrieve the extended attribute
  //
  // This will likely require a new protocol
  //
  return 0;
}

/// FuseClient: xmp_listxattr
static int xmp_listxattr(const char *path, char *list, size_t size){
  //
  // List the extended attributes
  //
  // This will likely require a new protocol
  //
  return 0;
}

/// FuseClient: xmp_removexattr
static int xmp_removexattr(const char *path, const char *name){
  //
  // Remove an extended attribute
  //
  // This will likely require a new protocol
  return 0;
}
#endif // HAVE_SETXATTR

#ifdef HAVE_COPY_FILE_RANGE
/// FuseClient: xmp_copy_file_range
static ssize_t xmp_copy_file_range(const char *path_in,
				   struct fuse_file_info *fi_in,
				   off_t offset_in, const char *path_out,
				   struct fuse_file_info *fi_out,
				   off_t offset_out, size_t len, int flags){
  //
  // copy a range of data from one file to another
  //
  // this will definitely require a new protocol
  // however, implementing this as a backend activity will likely
  // improve performance for copy operations significantly
  return 0;
}
#endif // HAVE_COPY_FILE_RANGE

/// FuseClient: Signal Handler
void handler(int signum){
  LOG(INFO) << "Existing BGASFuseClient...";
  exit(EXIT_SUCCESS);
}

static const struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readlink	= xmp_readlink,
	.mknod		= xmp_mknod,
	.mkdir		= xmp_mkdir,
	.unlink		= xmp_unlink,
	.rmdir		= xmp_rmdir,
	.symlink	= xmp_symlink,
	.rename		= xmp_rename,
	.link		= xmp_link,
	.chmod		= xmp_chmod,
	.chown		= xmp_chown,
	.truncate	= xmp_truncate,
	.open		= xmp_open,
	.read		= xmp_read,
	.write		= xmp_write,
	.statfs		= xmp_statfs,
	.release	= xmp_release,
	.fsync		= xmp_fsync,
#ifdef HAVE_SETXATTR
	.setxattr	= xmp_setxattr,
	.getxattr	= xmp_getxattr,
	.listxattr	= xmp_listxattr,
	.removexattr	= xmp_removexattr,
#endif
	.readdir	= xmp_readdir,
	.init           = xmp_init,
	.access		= xmp_access,
	.create 	= xmp_create,
#ifdef HAVE_POSIX_FALLOCATE
	.fallocate	= xmp_fallocate,
#ifdef HAVE_UTIMENSAT
	.utimens	= xmp_utimens,
#endif
#endif
#ifdef HAVE_COPY_FILE_RANGE
	.copy_file_range = xmp_copy_file_range,
#endif
};


/// FuseClient: ValidateConfig
bool ValidateConfig(){
  if( Config->GetMDSServers().size() == 0 ){
    LOG(FATAL) << "BGASFS has no configured metadata servers";
    return false;
  }

  if( Config->GetDataServers().size() == 0 ){
    LOG(FATAL) << "BGASFS has no configured data servers";
    return false;
  }

  if( Config->GetDeviceType() != BGASClient ){
    LOG(FATAL) << "Invalid device type.  Must be a BGASFS client";
    return false;
  }

  return true;
}

/// FuseClient: Daemon
void FuseClientDaemon(std::string ServerConfig,
                      int argc, char **argv){

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

  // read the server config
  Config = new BGASFSConfig( ServerConfig );
  if( !Config->IsInit() ){
    delete Config;
    LOG(FATAL) << "Error reading configuration file: " << ServerConfig;
    exit(EXIT_FAILURE);
  }

  if( !ValidateConfig() ){
    delete Config;
    LOG(FATAL) << "Configuration is invalid: " << ServerConfig;
    exit(EXIT_FAILURE);
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
  int res = 0;
  struct fuse_args args = FUSE_ARGS_INIT(argc,argv);

  xmp.case_insensitive = 0;
  if( fuse_opt_parse(&args, &xmp, xmp_opts, NULL) == -1){
    LOG(FATAL) << "Error parsing libfuse options";
    delete(Config);
    exit(EXIT_FAILURE);
  }

  res = fuse_main(args.argc, args.argv, &xmp_oper, NULL );

  fuse_opt_free_args(&args);

  delete(Config);
  LOG(INFO) << "Exiting file system with exit code=" << res;
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

  FuseClientDaemon(ServerConfig,argc,argv);

  return 0;
}

// EOF
