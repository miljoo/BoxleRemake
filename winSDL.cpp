#include "WinSDL.hpp"

//TODO: draw_worldmap_stateen kamera sisään


void init_SDL_Rect(SDL_Rect* rect, int x, int y, int height, int width){
  rect->x = x;
  rect->y = y;
  rect->h = height;
  rect->w = width;
}

/*
void draw_player_centric_player(Level* level, Player* player, SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer){
  From->x = TILESIZE * (1 + player->dir);
  From->y = TILESIZE * level->worldmap[player->x][player->y];
  To->x = (int)((SCREEN_WIDTH - TILESIZE) / 2);
  To->y = (int)((SCREEN_HEIGHT - TILESIZE) / 2);
  SDL_BlitSurface(sourceImage, From, buffer ,To);
}

void draw_player(Level* level, Player* player, SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer){
  From->x = TILESIZE * (1 + player->dir);
  From->y = TILESIZE * level->playmap[player->x][player->y];
  To->x = TILESIZE * player->x + offset_x;
  To->y = TILESIZE * player->y + offset_y;
  SDL_BlitSurface(sourceImage, From, buffer ,To);
}

void draw_player_centric_exit(Level* level, Player* player, SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer){
  From->x = TILESIZE * 5;
  From->y = TILESIZE * level->worldmap[level->ex][level->ey];
  To->x = (int)((SCREEN_WIDTH - TILESIZE) / 2 + TILESIZE*(level->ex - player->x));
  To->y = (int)((SCREEN_HEIGHT - TILESIZE) / 2 + TILESIZE*(level->ey - player->y));
  SDL_BlitSurface(sourceImage, From, buffer ,To);
}

void draw_exit(Level* level, Player* player, SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer){
  From->x = TILESIZE * 5;
  From->y = TILESIZE * level->playmap[level->ex][level->ey];
  To->x = TILESIZE * level->ex + offset_x;
  To->y = TILESIZE * level->ey + offset_y;
  SDL_BlitSurface(sourceImage, From, buffer ,To);
}

void draw_player_centric_portal(Level* level, Player* player, Levelportal portals[], SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer){
  for(unsigned int i = 0 ; i < portals_size ; ++i){
    From->x = TILESIZE * 5;
    From->y = TILESIZE * level->worldmap[level->ex][level->ey];
    To->x = (int)((SCREEN_WIDTH - TILESIZE) / 2 + TILESIZE*(portals[i].x - player->x));
    To->y = (int)((SCREEN_HEIGHT - TILESIZE) / 2 + TILESIZE*(portals[i].y - player->y));
    SDL_BlitSurface(sourceImage, From, buffer ,To);
  }
}

void draw_portal(Level* level, Player* player, Levelportal portals[], SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer){
  for(unsigned int i = 0 ; i < portals_size ; ++i){
    if(portals[i].active == true){
      From->x = TILESIZE * 6;
      From->y = TILESIZE * 2;
      To->x = (int)((SCREEN_WIDTH - TILESIZE) / 2 + TILESIZE*(portals[i].x - player->x));
      To->y = (int)((SCREEN_HEIGHT - TILESIZE) / 2 + TILESIZE*(portals[i].y - player->y));
      SDL_BlitSurface(sourceImage, From, buffer ,To);
    }else{
      From->x = TILESIZE * 6;
      From->y = TILESIZE * 1;
      To->x = (int)((SCREEN_WIDTH - TILESIZE) / 2 + TILESIZE*(portals[i].x - player->x));
      To->y = (int)((SCREEN_HEIGHT - TILESIZE) / 2 + TILESIZE*(portals[i].y - player->y));
      SDL_BlitSurface(sourceImage, From, buffer ,To);
    }
  }
}

void draw_player_centric_map(Level* level, Player* player, SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer){
  SDL_FillRect(buffer, NULL, SDL_MapRGB(buffer->format, 0,0,0));
  for(unsigned int j = 0 ; j < level->height ; ++j){
    for(unsigned int i = 0 ; i < level->width ; ++i){
      if(level->worldmap[i][j] <= 9){
        From->x = 0;
        From->y = TILESIZE * level->worldmap[i][j];
        To->x = (int)((SCREEN_WIDTH - TILESIZE) / 2 + TILESIZE*(i - player->x));
        To->y = (int)((SCREEN_HEIGHT - TILESIZE) / 2 + TILESIZE*(j - player->y));
        SDL_BlitSurface(sourceImage, From, buffer ,To);
      }else if(level->worldmap[i][j] == 11){
        From->x = TILESIZE * 6;
        From->y = 0;
        To->x = TILESIZE * i + offset_x;
        To->y = TILESIZE * j + offset_y;
        SDL_BlitSurface(sourceImage, From, buffer ,To);
      }
    }
  }
}

void draw_map(Level* level, SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer){
  SDL_FillRect(buffer, NULL, SDL_MapRGB(buffer->format, 0,0,0));
  for(unsigned int j = 0 ; j < level->height ; ++j){
    for(unsigned int i = 0 ; i < level->width ; ++i){
      if(level->playmap[i][j] <= 9 && level->pushable[i][j] == true){
        From->x = 0;
        From->y = TILESIZE * level->playmap[i][j];
        To->x = TILESIZE * i + offset_x;
        To->y = TILESIZE * j + offset_y;
        SDL_BlitSurface(sourceImage, From, buffer ,To);
      }else if(level->playmap[i][j] <= 9 && level->pushable[i][j] == false){
        From->x = TILESIZE * 7;
        From->y = TILESIZE * level->playmap[i][j];
        To->x = TILESIZE * i + offset_x;
        To->y = TILESIZE * j + offset_y;
        SDL_BlitSurface(sourceImage, From, buffer ,To);
      }else if(level->playmap[i][j] == 11){
        From->x = TILESIZE * 6;
        From->y = 0;
        To->x = TILESIZE * i + offset_x;
        To->y = TILESIZE * j + offset_y;
        SDL_BlitSurface(sourceImage, From, buffer ,To);
      }
    }
  }
}
*/

void draw_game_state(Level* level, Player* player, SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer){
  SDL_FillRect(buffer, NULL, SDL_MapRGB(buffer->format, 0,0,0));
  //draw map
  for(unsigned int j = 0 ; j < level->height ; ++j){
    for(unsigned int i = 0 ; i < level->width ; ++i){
      if(level->playmap[i][j] <= 9 && level->pushable[i][j] == true){
        From->x = 0;
        From->y = TILESIZE * level->playmap[i][j];
        To->x = TILESIZE * i + offset_x;
        To->y = TILESIZE * j + offset_y;
        //tähän kohtaa rotatiotestaus
        //SDL_RenderCopyEx(buffer,sourceImage,From,To,90,(32,32),0);
        SDL_BlitSurface(sourceImage, From, buffer ,To);
      }else if(level->playmap[i][j] <= 9 && level->pushable[i][j] == false){
        From->x = TILESIZE * 7;
        From->y = TILESIZE * level->playmap[i][j];
        To->x = TILESIZE * i + offset_x;
        To->y = TILESIZE * j + offset_y;
        SDL_BlitSurface(sourceImage, From, buffer ,To);
      }else if(level->playmap[i][j] == 11){
        From->x = TILESIZE * 6;
        From->y = 0;
        To->x = TILESIZE * i + offset_x;
        To->y = TILESIZE * j + offset_y;
        SDL_BlitSurface(sourceImage, From, buffer ,To);
      }
    }
  }
  //draw exit
  From->x = TILESIZE * 5;
  From->y = TILESIZE * level->playmap[level->ex][level->ey];
  To->x = TILESIZE * level->ex + offset_x;
  To->y = TILESIZE * level->ey + offset_y;
  SDL_BlitSurface(sourceImage, From, buffer ,To);
  //draw player
  From->x = TILESIZE * (1 + player->dir);
  From->y = TILESIZE * level->playmap[player->x][player->y];
  To->x = TILESIZE * player->x + offset_x;
  To->y = TILESIZE * player->y + offset_y;
  SDL_BlitSurface(sourceImage, From, buffer ,To);
}

void draw_worldmap_state(Level* level, Player* player, Levelportal portals[], SDL_Rect* From, SDL_Rect* To, SDL_Surface* sourceImage, SDL_Surface* buffer){
  SDL_FillRect(buffer, NULL, SDL_MapRGB(buffer->format, 0,0,0));

  //draw map
  for(unsigned int j = 0 ; j < level->height ; ++j){
    for(unsigned int i = 0 ; i < level->width ; ++i){
      if(level->worldmap[i][j] <= 9){
        From->x = TILESIZE * 7;
        //From->x = 0;
        From->y = TILESIZE * level->worldmap[i][j];
        To->x = (int)((SCREEN_WIDTH - TILESIZE) / 2 + TILESIZE*(i - player->x));
        To->y = (int)((SCREEN_HEIGHT - TILESIZE) / 2 + TILESIZE*(j - player->y));
        SDL_BlitSurface(sourceImage, From, buffer ,To);
      }else if(level->worldmap[i][j] == 11){
        From->x = TILESIZE * 6;
        From->y = 0;
        To->x = (int)((SCREEN_WIDTH - TILESIZE) / 2 + TILESIZE*(i - player->x));
        To->y = (int)((SCREEN_HEIGHT - TILESIZE) / 2 + TILESIZE*(j - player->y));
        SDL_BlitSurface(sourceImage, From, buffer ,To);
      }
    }
  }
  //draw portal(s)
  for(unsigned int i = 0 ; i < portals_size ; ++i){
    if(portals[i].active == true){
      From->x = TILESIZE * 6;
      From->y = TILESIZE * 2;

      To->x = (int)((SCREEN_WIDTH - TILESIZE) / 2 + TILESIZE*( portals[i].x - player->x ));
      To->y = (int)((SCREEN_HEIGHT - TILESIZE) / 2 + TILESIZE*( portals[i].y - player->y ));
      SDL_BlitSurface(sourceImage, From, buffer ,To);
    }else{
      From->x = TILESIZE * 6;
      From->y = TILESIZE * 1;
      To->x = (int)((SCREEN_WIDTH - TILESIZE) / 2 + TILESIZE*( portals[i].x - player->x ));
      To->y = (int)((SCREEN_HEIGHT - TILESIZE) / 2 + TILESIZE*( portals[i].y - player->y ));
      SDL_BlitSurface(sourceImage, From, buffer ,To);
    }
  }
  //draw player
  From->x = TILESIZE * (1 + player->dir);
  From->y = TILESIZE * level->worldmap[player->x][player->y];
  To->x = (int)((SCREEN_WIDTH - TILESIZE) / 2);
  To->y = (int)((SCREEN_HEIGHT - TILESIZE) / 2);
  SDL_BlitSurface(sourceImage, From, buffer ,To);
}
