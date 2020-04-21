#ifndef FILEHANDLING_HPP
#define FILEHANDLING_HPP

#include <stdio.h>
#include <string.h>
#include "boxle.hpp"

void save_init_portals(Levelportal portals[], int portals_size);

void load_init_portals(Levelportal portals[], int portals_size);

void save_portals(Levelportal portals[], int portals_size);

void load_portals(Levelportal portals[], int portals_size);

void save_play_level_with_name(Level* level, Player* player);

void save_current_play_level(Level* level, Player* player, char currentlvlname[]);

void load_play_level(Level* level, Player* player, char lvlname[]);

void save_world_level_with_name(Level* level, Player* player);

void save_current_world_level(Level* level, Player* player , char currentlvlname[]);

void load_world_level(Level* level, Player* player, char lvlname[]);

#endif
