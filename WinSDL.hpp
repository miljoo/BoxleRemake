#ifndef WINSDL_HPP
#define WINSDL_HPP

#include <SDL.h>
#include "boxle.hpp"
#include "config.hpp"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int TILESIZE;
extern int offset_x;
extern int offset_y;
extern unsigned int portals_size;

void init_SDL_Rect(SDL_Rect* rect, int x, int y, int height, int width);

/*
void draw_player_centric_player(Level* level, Player* player, SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer);

void draw_player(Level* level, Player* player, SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer);

void draw_player_centric_exit(Level* level, Player* player, SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer);

void draw_exit(Level* level, SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer);

void draw_player_centric_portal(Level* level, Levelportal portals[], SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer);

void draw_portal(Level* level, Levelportal portals[], SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer);

void draw_player_centric_map(Level* level, Player* player, SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer);

void draw_map(Level* level, Player* player, SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer);
*/

void draw_game_state(Level* level, Player* player, SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer);

void draw_worldmap_state(Level* level, Player* player, Levelportal portals[], SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer);

#endif
