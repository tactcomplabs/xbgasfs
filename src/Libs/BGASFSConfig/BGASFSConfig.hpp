//
// _BGASFSConfig_hpp_
//
// Copyright (C) 2017-2020 Tactical Computing Laboratories, LLC
// All Rights Reserved
//
// contact@tactcomplabs.com
//
// See LICENSE in the top level directory for licensing details
//

#ifndef _BGASFSCONFIG_HPP_
#define _BGASFSCONFIG_HPP_

// Standard C++ Headers
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

typedef enum{
  BGASUnk     = 0,
  BGASMDS     = 1,
  BGASData    = 2,
  BGASClient  = 3
}BGASDev;

class BGASFSConfig{
private:
  bool isInit;                          ///< BGASFSConfig: is the config initialized?
  std::string ConfigFile;               ///< BGASFSConfig: configuration file path
  BGASDev DeviceType;                   ///< BGASFSConfig: device configuration type
  std::vector<std::string> MDS;         ///< BGASFSConfig: metadata servers
  std::vector<std::string> Data;        ///< BGASFSConfig: data servers

  // private functions

  /// BGASFSConfig: Read the configuration file
  bool ReadConfigFile();

  /// BGASFSConfig: Read the MDS servers
  bool ReadMDSServers(std::ifstream& CFile);

  /// BGASFSConfig: Read the Data servers
  bool ReadDataServers(std::ifstream& CFile);

public:
  /// BGASFSConfig: constructor
  BGASFSConfig(std::string ConfigFile);

  /// BGASFSConfig: destructor
  ~BGASFSConfig();

  /// BGASFSConfig: Is the library initialized?
  bool IsInit();

  /// BGASFSConfig: Rescan the configuration file
  bool ConfigRescan();

  /// BGASFSConfig: What type of configuration is this?
  BGASDev GetDeviceType();

  /// BGASFSConfig: Retrieve the list of metadata servers
  std::vector<std::string> GetMDSServers();

  /// BGASFSConfig: Retrieve the list of data servers
  std::vector<std::string> GetDataServers();
};

#endif

// EOF
