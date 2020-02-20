#
# BGASFS/Src/Libs/BGASFSConfig CMakeLists.txt
#
# Copyright (C) 2017-2020 Tactical Computing Laboratories, LLC
# All Rights Reserved
# contact@tactcomplabs.com
#
# See LICENSE in the top level directory for licensing details
#

set(BGASFSConfigSrcs
  BGASFSConfig.hpp
  BGASFSConfig.cpp
)

include_directories(.)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_library(BGASFSConfig ${BGASFSConfigSrcs})
set_target_properties(BGASFSConfig PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS BGASFSConfig ARCHIVE DESTINATION lib)

#-- EOF
