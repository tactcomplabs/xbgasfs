//
// _BGASFSConfig_cpp_
//
// Copyright (C) 2017-2020 Tactical Computing Laboratories, LLC
// All Rights Reserved
//
// contact@tactcomplabs.com
//
// See LICENSE in the top level directory for licensing details
//

#include "BGASFSConfig.hpp"

BGASFSConfig::BGASFSConfig(std::string CF)
  : isInit(false), ConfigFile(CF), DeviceType(BGASUnk) {
  isInit = ReadConfigFile();
}

BGASFSConfig::~BGASFSConfig(){
}

bool BGASFSConfig::ConfigRescan(){
  isInit = ReadConfigFile();
  return isInit;
}

bool BGASFSConfig::IsInit(){
  return isInit;
}

BGASDev BGASFSConfig::GetDeviceType(){
  return DeviceType;
}

std::vector<std::string> BGASFSConfig::GetMDSServers(){
  return MDS;
}

std::vector<std::string> BGASFSConfig::GetDataServers(){
  return Data;
}

bool BGASFSConfig::ReadMDSServers(std::ifstream& CFile ){
  std::string line;

  while( getline( CFile, line ) ){
    if( line == "[END_MDS]" ){
      return true;
    }else{
      MDS.push_back(line);
    }
  }

  // didn't find an [END_MDS] line
  return false;
}

bool BGASFSConfig::ReadDataServers(std::ifstream& CFile ){
  std::string line;

  while( getline( CFile, line ) ){
    if( line == "[END_DATA]" ){
      return true;
    }else{
      Data.push_back(line);
    }
  }

  // didn't find an [END_DATA] line
  return false;
}

bool BGASFSConfig::ReadConfigFile(){

  // open the file
  std::ifstream CFile(ConfigFile);
  if( !CFile.is_open() ){
    return false;
  }

  // read all the lines
  std::string line;
  while( getline( CFile, line ) ){
    if( line == "[START_MDS]" ){
      if( !ReadMDSServers(CFile) ){
        CFile.close();
        return false;
      }
    }else if( line == "[START_DATA]" ){
      if( !ReadDataServers(CFile) ){
        CFile.close();
        return false;
      }
    } // else, ignore it
  }

  // if we find MDS and DATA lines, then the type is a client
  // if we find only DATA lines, then the type is a MDS
  if( (MDS.size() > 0) && (Data.size() > 0) ){
    DeviceType = BGASClient;
  }else if( Data.size() > 0 ){
    DeviceType = BGASMDS;
  }else{
    DeviceType = BGASData;
  }

  CFile.close();

  return true;
}

// EOF
