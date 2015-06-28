# Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  Custom/apt_system.cpp
  Custom/cs_legacy.cpp
 # Custom/cs_storyscript.cpp #Dynamic scripting system.
  Custom/euclid.cpp #spawn sytem
  Custom/carpus.cpp #teleporter
  Custom/galenus.cpp #death 2.0
 # Custom/2_deaths.cpp #death 1.0
 # Custom/mod_helf_rep.cpp 
 # Custom/kali_tele.cpp
  Custom/misc.cpp
 # Custom/hector.cpp #mount system
 # Custom/scale_npc.cpp 
 # Custom/crates.cpp #rts system
 # Custom/Transportation.cpp #Transportation system.
 # Custom/talent_spells.cpp
   Custom/upt.cpp
)

message("  -> Prepared: Custom")
