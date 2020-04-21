#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>

#include "boxle.hpp"
#include "WinSDL.hpp"
#include "filehandling.hpp"
#include "config.hpp"

//For editor mode to check if file exist
#include <unistd.h>

int TILESIZE = 64;
int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 1024;

int SCREEN_FPS = 30;
int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;


//can these be moved inside main?
//-----------------
int offset_x;
int offset_y;

SDL_Rect From;
SDL_Rect To;
SDL_Rect sFrom;
SDL_Rect sTo;
//-----------------

int get_portal_index(unsigned int mouse_selection_x, unsigned int mouse_selection_y, Levelportal portals[], int portals_size){
  for(int i = 0 ; i < portals_size ; ++i){
    if(mouse_selection_x == portals[i].x && mouse_selection_y == portals[i].y){
      //DEBUG
      printf("Found index:%d\n", i);
      return i;
    }
  }
  //DEBUG
  printf("Didn't find a portal\n");
  return -1;
}

int main(int argc, char* args[]){

  bool run_once = true; //toggle to draw screen once to prevent white window on start
  bool game_loop_running = true;
  bool editmode = false;
  bool worldmapmode = true;
  bool portal_selected = false; //is a portal selected
  bool valid_destination = false; //is new portal destination a valid one

  int active_level_index;
  int mouse_x,mouse_y;
  int time_start;
  int time_end;
  int deltatime;

  //for moving portals
  int portal_index;
  unsigned int selected_portal_x;
  unsigned int selected_portal_y;

  char currentlvlname[] = "data/levels/init_world.lvl";

  //Transition_storage trans_storage;
  Selection mouse_selection = {0};
  Player player;
  Player storedPlayer;
  Level level;
  for(unsigned int j = 0 ; j < 20 ; ++j){
    for(unsigned int i = 0 ; i < 20 ; ++i){
       level.pushable[i][j] = 1;
    }
  }
  Levelportal portals[100];

  init_SDL_Rect(&From, 0, 0, TILESIZE, TILESIZE);
  init_SDL_Rect(&To, TILESIZE, TILESIZE, TILESIZE, TILESIZE);
  init_SDL_Rect(&sFrom, TILESIZE * 6, TILESIZE * 3, TILESIZE, TILESIZE);
  init_SDL_Rect(&sTo, TILESIZE, TILESIZE, TILESIZE, TILESIZE);

  SDL_Window* window = NULL;
  SDL_Surface* buffer = NULL;
  SDL_Surface* sourceImage = NULL;
  SDL_Surface* keys_pic = NULL;
  SDL_Event event;

  offset_x = (int)((SCREEN_WIDTH - level.width * TILESIZE) / 2);
  offset_y = (int)((SCREEN_HEIGHT - level.height * TILESIZE) / 2);

/*  portals_size = 3;

  FILE *f;
  f = fopen("data/levels/poco.dat", "wb");
  if(f == NULL){
    printf("Couldn't open file");
  }else{
    fwrite(&portals_size, sizeof(unsigned int), 1, f);
    printf("data/levels/poco.dat should exist");
  }
  fclose(f);
*/


  //LOAD PORTAL COUNT FROM FILE
  FILE *f;
  f = fopen("data/levels/poco.dat", "rb");
  if(f == NULL){
    printf("Couldn't open poco.dat at start.\n");
  }else{
    fread(&portals_size, sizeof(unsigned int), 1, f);
  }
  fclose(f);

//here some INIT stuff if new game and if not, continue on old save files
/*
  if(newgame == true){
    load_world_level(&world_level, "Initworld.lvl");
    save_world_level_with_name(&world_level, "world.lvl");
    load_initial_portals(portals, portals_size);
    save_portals(portals, portals_size);
  }else{
    load_world_level(&world_level, currentlvlname);
    load_portals(portals, portals_size);
  }
*/

  //USE THIS TO UPDATE INIT PORTAL LIST
  //---------------------------------------------
  //save_init_portals(portals, portals_size);
  //---------------------------------------------

  //NEW GAME INIT STUFF HERE
  //TODO: Insert Player class into these functions!
  load_world_level(&level, &player, currentlvlname);
  load_init_portals(portals,portals_size);
  //set lvl name from init_world to world
  strcpy(currentlvlname, "data/levels/world.lvl");
  //overwrite previsouly saved world.lvl
  save_current_world_level(&level, &player, currentlvlname);
  save_portals(portals,portals_size);

  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  }else{
    //Create window
    window = SDL_CreateWindow( "Boxle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL ){
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    }else{
       //Get window surface
      buffer = SDL_GetWindowSurface( window );

      keys_pic = IMG_Load("data/graphics/keys.png");
      if(!keys_pic){
        printf("IMG_Load: %s\n", IMG_GetError());
      }

      sourceImage = IMG_Load("data/graphics/tilesv5.png");
      if(!sourceImage){
        printf("IMG_Load: %s\n", IMG_GetError());
      }

      //START OF GAMELOOP
      while(game_loop_running){

        time_start = SDL_GetTicks();

        if(run_once){
          SDL_Rect keyspos;
          keyspos.x = SCREEN_HEIGHT/3;
          keyspos.y = SCREEN_WIDTH/3;
          SDL_BlitSurface(keys_pic, NULL, buffer ,&keyspos);
          SDL_UpdateWindowSurface( window );
          SDL_Delay(7000);
        }

        //Is there better way to get game drawn on startup?
        //Maybe gets fixed once menus are implemented???
        if(run_once){
          draw_worldmap_state(&level, &player, portals, &From, &To, sourceImage, buffer);
          run_once = false;
          SDL_UpdateWindowSurface( window );
        }

        //START OF INPUT BLOCK
        while( SDL_PollEvent( &event)){
          if (event.type == SDL_QUIT){
            game_loop_running = false;
          }
          switch(event.type){
            case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
              case SDLK_r:
                if(!worldmapmode){
                  load_play_level(&level, &player, currentlvlname);
                }
              break;
              case SDLK_LEFT:
                if(!editmode){
                  move(&level, &player, LEFT, worldmapmode);
                }else{
                  moveCamera(&player, LEFT, worldmapmode);
                }
              break;
              case SDLK_RIGHT:
                if(!editmode){
                  move(&level, &player, RIGHT, worldmapmode);
                }else{
                  moveCamera(&player, RIGHT, worldmapmode);
                }
              break;
              case SDLK_UP:
                if(!editmode){
                  move(&level, &player, UP, worldmapmode);
                }else{
                  moveCamera(&player, UP, worldmapmode);
                }
              break;
              case SDLK_DOWN:
                if(!editmode){
                  move(&level, &player, DOWN, worldmapmode);
                }else{
                  moveCamera(&player, DOWN, worldmapmode);
                }
              break;
              case SDLK_SPACE:
                if(!editmode){
                  jump(&level, &player, worldmapmode);
                }
              break;
              case SDLK_ESCAPE:
                if(worldmapmode){
                  //TODO:Change this to move back to main menu at some point
                  game_loop_running = false;
                }else{
                  //WARNING! TODO:Change this to not fuck things up once there are more places you can press esc in
                  worldmapmode = true;
                  strcpy(currentlvlname, "data/levels/world.lvl");
                  load_world_level(&level, &player, currentlvlname);
                }
              break;

              case SDLK_e:
                if(editmode){
                  player = storedPlayer;
                }else{
                  storedPlayer = player;
                }
                editmode = !editmode;

              break;

              //editmode keybindings
              case SDLK_0:
                if(editmode){
                  if(worldmapmode){
                    level.worldmap[mouse_selection.x][mouse_selection.y] = 0;
                  }else{
                    level.playmap[mouse_selection.x][mouse_selection.y] = 0;
                  }
                }
              break;
              case SDLK_1:
                if(editmode){
                  if(worldmapmode){
                    level.worldmap[mouse_selection.x][mouse_selection.y] = 1;
                  }else{
                    level.playmap[mouse_selection.x][mouse_selection.y] = 1;
                  }
                }
              break;
              case SDLK_2:
                if(editmode){
                  if(worldmapmode){
                    level.worldmap[mouse_selection.x][mouse_selection.y] = 2;
                  }else{
                    level.playmap[mouse_selection.x][mouse_selection.y] = 2;
                  }
                }
              break;
              case SDLK_3:
                if(editmode){
                  if(worldmapmode){
                    level.worldmap[mouse_selection.x][mouse_selection.y] = 3;
                  }else{
                    level.playmap[mouse_selection.x][mouse_selection.y] = 3;
                  }
                }
              break;
              case SDLK_4:
                if(editmode){
                  if(worldmapmode){
                    level.worldmap[mouse_selection.x][mouse_selection.y] = 4;
                  }else{
                    level.playmap[mouse_selection.x][mouse_selection.y] = 4;
                  }
                }
              break;
              case SDLK_5:
                if(editmode){
                  if(worldmapmode){
                    level.worldmap[mouse_selection.x][mouse_selection.y] = 5;
                  }else{
                    level.playmap[mouse_selection.x][mouse_selection.y] = 5;
                  }
                }
              break;
              case SDLK_6:
                if(editmode){
                  if(worldmapmode){
                    level.worldmap[mouse_selection.x][mouse_selection.y] = 6;
                  }else{
                    level.playmap[mouse_selection.x][mouse_selection.y] = 6;
                  }
                }
              break;
              case SDLK_7:
                if(editmode){
                  if(worldmapmode){
                    level.worldmap[mouse_selection.x][mouse_selection.y] = 7;
                  }else{
                    level.playmap[mouse_selection.x][mouse_selection.y] = 7;
                  }
                }
              break;
              case SDLK_8:
                if(editmode){
                  if(worldmapmode){
                    level.worldmap[mouse_selection.x][mouse_selection.y] = 8;
                  }else{
                    level.playmap[mouse_selection.x][mouse_selection.y] = 8;
                  }
                }
              break;
              case SDLK_9:
                if(editmode){
                  if(worldmapmode){
                    level.worldmap[mouse_selection.x][mouse_selection.y] = 9;
                  }else{
                    level.playmap[mouse_selection.x][mouse_selection.y] = 9;
                  }
                }
              break;
              case SDLK_t:
                /*
                if(editmode){
                  if(worldmapmode){
                    for(unsigned int i = 0 ; i < portals_size ; ++i){
                      if(mouse_selection.x == portals[i].x && mouse_selection.y == portals[i].y){
                        strcpy(currentlvlname, portals[i].destination);
                        trans_storage.px = player.x;
                        trans_storage.py = player.y;

                        load_play_level(&level, &player, currentlvlname);

                        trans_storage.wx = portals[i].x;
                        trans_storage.wy = portals[i].y;
                        trans_storage.lx = player.x;
                        trans_storage.ly = player.y;
                        trans_storage.height = level.height;
                        trans_storage.width = level.width;

                        strcpy(currentlvlname, "data/levels/world.lvl");
                        load_world_level(&level, &player, currentlvlname);

                        if(portals[i].active == false){
                          for(unsigned int j = 0 ; j < trans_storage.height ; ++j){
                            for(unsigned int i = 0 ; i < trans_storage.width ; ++i){
                              level.worldmap[i + (trans_storage.wx - trans_storage.lx)][j + (trans_storage.wy - trans_storage.ly)] -= level.playmap[i][j];
                            }
                          }
                          portals[i].active = true;
                        }else if(portals[i].active == true){
                           for(unsigned int j = 0 ; j < trans_storage.height ; ++j){
                            for(unsigned int i = 0 ; i < trans_storage.width ; ++i){
                              level.worldmap[i + (trans_storage.wx - trans_storage.lx)][j + (trans_storage.wy - trans_storage.ly)] += level.playmap[i][j];
                            }
                          }
                          portals[i].active = false;
                        }

                        player.x = trans_storage.px;
                        player.y = trans_storage.py;

                        save_current_world_level(&level, &player, currentlvlname);
                        save_portals(portals,portals_size);

                        break;
                      }
                    }
                  }
                }
              break;
              */
              case SDLK_x:
                if(editmode){
                  if(worldmapmode){
                    level.worldmap[mouse_selection.x][mouse_selection.y] = 11;
                  }else{
                    level.playmap[mouse_selection.x][mouse_selection.y] = 11;
                  }
                }
              break;
              case SDLK_o:
                if(editmode){
                  level.ex = mouse_selection.x;
                  level.ey = mouse_selection.y;
                }
              break;
              case SDLK_p:
                if(editmode){
                  player.x = mouse_selection.x;
                  player.y = mouse_selection.y;
                  storedPlayer.x = mouse_selection.x;
                  storedPlayer.y = mouse_selection.y;
                }
              break;
              case SDLK_s:
                if(editmode){
                  if(worldmapmode){
                    //save_world_level_with_name(&level);
                  }else{
                    FILE * f;
                    char levelname[100];
                    char dotlvl[5] = ".lvl";
                    char folder[100] = "data/levels/";
                     printf("Enter level name:");
                    scanf("%s", levelname);
                    strcat(folder, levelname);

                    strcpy(levelname, folder);
                    strcat(levelname, dotlvl);

                    f = fopen(levelname, "wb");
                    if(f == NULL){
                      printf("Couldn't open file at save level with name.\n");
                    }else{
                      fwrite(&player.x, sizeof(unsigned int), 1, f);
                      fwrite(&player.y, sizeof(unsigned int), 1, f);
                      fwrite(&player.z, sizeof(unsigned int), 1, f);
                      fwrite(&player.t, sizeof(unsigned int), 1, f);
                      fwrite(&player.dir, sizeof(unsigned int), 1, f);
                      fwrite(&level.ex, sizeof(unsigned int), 1, f);
                      fwrite(&level.ey, sizeof(unsigned int), 1, f);
                      fwrite(&level.width, sizeof(unsigned int), 1, f);
                      fwrite(&level.height, sizeof(unsigned int), 1, f);
                      fwrite(&level.playmap, sizeof(level.playmap), 1, f);
                      strcpy(currentlvlname, levelname);
                    }
                    fclose(f);
                  }
                }
              break;
              case SDLK_c:
                if(editmode){
                  if(worldmapmode){
                    save_current_world_level(&level, &player, currentlvlname);
                  }else{
                    save_current_play_level(&level, &player, currentlvlname);
                  }
                }
              break;
              case SDLK_m:
                if(editmode){
                  if(worldmapmode){
                    if(portal_selected){
                      valid_destination = true;
                      for(unsigned int i = 0 ; i < portals_size ; ++i){
                        if(mouse_selection.x == portals[i].x && mouse_selection.y == portals[i].y && portals[i].active == true){
                          printf("Portal already present at selected location!\n");
                          valid_destination = false;
                        }
                      }
                      if(valid_destination){
                        if(!(mouse_selection.x == selected_portal_x && mouse_selection.y == selected_portal_y)){
                          portals[portal_index].x = mouse_selection.x;
                          portals[portal_index].y = mouse_selection.y;
                          printf("Portal moved\n");

                          save_init_portals(portals, portals_size);
                          save_portals(portals, portals_size);
                          portal_selected = false;
                        }
                      }
                    }else if(!portal_selected){
                      for(unsigned int i = 0 ; i < portals_size ; ++i){
                        if(mouse_selection.x == portals[i].x && mouse_selection.y == portals[i].y && portals[i].active == true){
                          selected_portal_x = mouse_selection.x;
                          selected_portal_y = mouse_selection.y;
                          portal_index = i;
                          printf("Portal selected. Select a new location and press 'm'.\n");
                          portal_selected = true;
                        }
                      }
                    }
                  }
                }
              break;
              case SDLK_i:
                if(editmode){
                  printf("Current level:%s\n", currentlvlname);
                }
              break;
              case SDLK_b:
                if(editmode){
                  level.pushable[mouse_selection.x][mouse_selection.y] = !level.pushable[mouse_selection.x][mouse_selection.y];
                }
              break;
              case SDLK_DELETE:
                if(editmode){
                  if(worldmapmode){
                    bool portal_found = false;
                    unsigned int remove_index;
                    for(unsigned int i = 0 ; i < portals_size ; ++i){
                      if(mouse_selection.x == portals[i].x && mouse_selection.y == portals[i].y){
                        //DEBUG
                        printf("Found portal at index %d\n", i);
                        remove_index = i;
                        portal_found = true;
                      }
                    }
                    if(portal_found){
                      //RELOAD PORTALS TO ARRAY SKIPPING THE ONE AT INDEX
                      FILE * fp;
                      fp = fopen("data/levels/init_portals.dat", "rb");
                      if(fp == NULL){
                        printf("Couldn't open file for portal removal.\n");
                      }else{
                        int j = 0;
                        for(unsigned int i = 0 ; i < portals_size ; ++i){
                          if(i != remove_index){
                            fread(&portals[j].x, sizeof(unsigned int), 1, fp);
                            fread(&portals[j].y, sizeof(unsigned int), 1, fp);
                            fread(&portals[j].destination, sizeof(char[39]), 1, fp);
                            fread(&portals[j].active, sizeof(bool), 1, fp);
                            j++;
                          }
                        }
                      }
                      fclose(fp);
                      //DECREASE PORTAL COUNT
                      portals_size--;
                      //SAVE INIT_PORTALS
                      save_init_portals(portals, portals_size);
                      //SAVE PORTALS
                      save_portals(portals, portals_size);
                      //SAVE PORTAL COUNT
                      fp = fopen("data/levels/poco.dat", "wb");
                      if(fp == NULL){
                        printf("Couldn't open poco.dat to decrease portal count\n");
                      }else{
                        fwrite(&portals_size, sizeof(unsigned int), 1, fp);
                      }
                      fclose(fp);
                      load_init_portals(portals, portals_size);
                      load_portals(portals, portals_size);
                    }
                  }
                }
              break;
              case SDLK_n:
                if(editmode){
                  if(worldmapmode){
                    valid_destination = true;
                    for(unsigned int i = 0 ; i < portals_size ; ++i){
                      if(mouse_selection.x == portals[i].x && mouse_selection.y == portals[i].y){
                        printf("Portal already present at selected location!\n");
                        valid_destination = false;
                      }
                    }
                    if(valid_destination){
                      FILE *file;
                      bool level_found = false;
                      unsigned int portal_x, portal_y;
                      char target_level[100];
                      char dotlvl[5] = ".lvl";
                      char folder[100] = "data/levels/";
                      bool active = true;

                      portal_x = mouse_selection.x;
                      portal_y = mouse_selection.y;

                      while(!level_found){
                        printf("Give target level name:");
                        scanf("%s", target_level);

                        strcat(folder, target_level);
                        strcpy(target_level, folder);
                        strcat(target_level, dotlvl);

                        if(access(target_level, F_OK) != -1){
                          level_found = true;
                          printf("Level file found!\n");
                        }else{
                          printf("Level file not found.\n");
                          strcpy(folder, "data/levels/");
                        }
                      }
                     file = fopen("data/levels/init_portals.dat", "ab");
                      if(file == NULL){
                        printf("Couldn't open init_portals.dat in portal creation\n");
                      }else{
                        fwrite(&portal_x, sizeof(unsigned int), 1, file);
                        fwrite(&portal_y, sizeof(unsigned int), 1, file);
                        fwrite(&target_level, sizeof(char[39]), 1, file);
                        fwrite(&active, sizeof(bool), 1, file);
                      }
                      fclose(file);
                      file = fopen("data/levels/portals.dat", "ab");
                      if(file == NULL){
                        printf("Couldn't open portals.dat in portal creation\n");
                      }else{
                        fwrite(&portal_x, sizeof(unsigned int), 1, file);
                        fwrite(&portal_y, sizeof(unsigned int), 1, file);
                        fwrite(&target_level, sizeof(char[39]), 1, file);
                        fwrite(&active, sizeof(bool), 1, file);
                      }
                      fclose(file);

                      portals_size++;

                      file = fopen("data/levels/poco.dat", "wb");
                      if(file == NULL){
                        printf("Couldn't open file poco.dat in portal creation.\n");
                      }else{
                        fwrite(&portals_size, sizeof(unsigned int), 1, file);
                      }
                      fclose(file);

                      load_init_portals(portals, portals_size);
                      load_portals(portals, portals_size);
                    }
                  }
                }
              break;
              case SDLK_l:
                if(editmode){
                  //TODO: MAYBE PUT THE FILE CHECKING HERE TOO
                  char loadname[100];
                  printf("Give level name:");
                  scanf("%s", loadname);
                  char dotlvl[5] = ".lvl";
                  char folder[100] = "data/levels/";
                  strcat(folder, loadname);
                  strcpy(loadname, folder);
                  strcat(loadname, dotlvl);
                  FILE *f;
                  f = fopen(loadname, "rb");
                  if(f == NULL){
                    printf("Couldn't open file at load level.\n");
                  }else{
                    fread(&player.x, sizeof(unsigned int), 1, f);
                    fread(&player.y, sizeof(unsigned int), 1, f);
                    fread(&player.z, sizeof(unsigned int), 1, f);
                    fread(&player.t, sizeof(unsigned int), 1, f);
                    fread(&player.dir, sizeof(unsigned int), 1, f);
                    fread(&level.ex, sizeof(unsigned int), 1, f);
                    fread(&level.ey, sizeof(unsigned int), 1, f);
                    fread(&level.width, sizeof(unsigned int), 1, f);
                    fread(&level.height, sizeof(unsigned int), 1, f);
                    fread(&level.playmap, sizeof(level.playmap), 1, f);
                    strcpy(currentlvlname, loadname);
                  }
                  fclose(f);
                }
              break;
              case SDLK_KP_8:
                if(editmode){
                  if(level.height > 2){
                    level.height--;
                  }
                }
              break;
              case SDLK_KP_2:
                if(editmode){
                  if(level.height < LEVEL_MAX_Y){
                    level.height++;
                  }
                }
              break;
              case SDLK_KP_4:
                if(editmode){
                  if(level.width > 2){
                    level.width--;
                  }
                }
              break;
              case SDLK_KP_6:
                if(editmode){
                  if(level.width < LEVEL_MAX_X){
                    level.width++;
                  }
                }
              break;
              case SDLK_KP_MINUS:
                if(editmode){
                  if(level.width > 2 && level.height > 2){
                    level.width--;
                    level.height--;
                  }
                }
              break;
              case SDLK_KP_PLUS:
                if(editmode){
                  if(level.width < LEVEL_MAX_X && level.height < LEVEL_MAX_Y){
                    level.width++;
                    level.height++;
                    for(unsigned int j = 0 ; j < level.height ; j++){
                      for(unsigned int i = 0 ; i < level.width ; i++){
                        if(worldmapmode){
                          if(i == (level.width - 1)){
                          level.worldmap[i][j] = 0;
                          }
                          if(j == (level.height - 1)){
                            level.worldmap[i][j] = 0;
                          }
                        }else{
                          if(i == (level.width - 1)){
                          level.playmap[i][j] = 0;
                          }
                          if(j == (level.height - 1)){
                            level.playmap[i][j] = 0;
                          }
                        }
                      }
                    }
                  }
                }
              break;
            }
            //NOTE!! Crashes if level is increased to overflow the game window

            offset_x = (int)((SCREEN_WIDTH - level.width * TILESIZE) / 2);
            offset_y = (int)((SCREEN_HEIGHT - level.height * TILESIZE) / 2);

            case SDL_MOUSEBUTTONDOWN:
            switch(event.button.button){
              case SDL_BUTTON_LEFT:
                if(editmode == true){
                  SDL_GetMouseState(&mouse_x, &mouse_y);
                  if(!worldmapmode){
                    if((unsigned int)(mouse_x - offset_x)/TILESIZE < level.width){
                      mouse_selection.x = (int)(mouse_x - offset_x)/TILESIZE;
                    }
                    if((unsigned int)(mouse_y - offset_y)/TILESIZE < level.height){
                      mouse_selection.y = (int)(mouse_y - offset_y)/TILESIZE;
                    }
                  }else if(worldmapmode){
                    if(mouse_x < (SCREEN_WIDTH / 2 + TILESIZE / 2)){
                      mouse_selection.x = (int)(player.x + (mouse_x - SCREEN_WIDTH / 2 - TILESIZE / 2) / TILESIZE);
                    }else{
                      mouse_selection.x = 1 + (int)(player.x + (mouse_x - SCREEN_WIDTH / 2 - TILESIZE / 2) / TILESIZE);
                    }
                    if(mouse_y < (SCREEN_HEIGHT / 2 + TILESIZE / 2)){
                      mouse_selection.y = (int)(player.y + (mouse_y - SCREEN_HEIGHT / 2 - TILESIZE / 2) / TILESIZE);
                    }else{
                      mouse_selection.y = 1 + (int)(player.y + (mouse_y - SCREEN_HEIGHT / 2 - TILESIZE / 2) / TILESIZE);
                    }
                  }
                }
              break;
            }
          }
        }
        //END OF INPUT BLOCK

        //START OF STATE UPDATE BLOCK
        for(unsigned int i = 0 ; i < sizeof(portals)/sizeof(Levelportal) ; ++i){
          if(!editmode){
            if(player_on_portal(&level, &player, portals[i]) && portals[i].active == true && worldmapmode == true){
              active_level_index = i;
              worldmapmode = false;
              strcpy(currentlvlname, portals[i].destination);
              load_play_level(&level, &player, currentlvlname);

              //store required data needed to move level onto worldmap in case player solves level
              /*
              trans_storage.wx = portals[i].x;
              trans_storage.wy = portals[i].y;
              trans_storage.lx = player.x;
              trans_storage.ly = player.y;
              trans_storage.height = level.height;
              trans_storage.width = level.width;
             */

              offset_x = (int)((SCREEN_WIDTH - level.width * TILESIZE) / 2);
              offset_y = (int)((SCREEN_HEIGHT - level.height * TILESIZE) / 2);

            }else if(player_on_exit(&level, &player) && worldmapmode == false){
              //level solved
              portals[active_level_index].active = false;

              worldmapmode = true;

              //reload play level to move initial state to worldmap
              load_play_level(&level, &player, currentlvlname);

              strcpy(currentlvlname, "data/levels/world.lvl");
              load_world_level(&level, &player, currentlvlname);
              /*
              for(unsigned int j = 0 ; j < trans_storage.height ; ++j){
                for(unsigned int i = 0 ; i < trans_storage.width ; ++i){
                  level.worldmap[i + (trans_storage.wx - trans_storage.lx)][j + (trans_storage.wy - trans_storage.ly)] += level.playmap[i][j];
                }
              }
              */
              //SAVE CHANGES TO WORLDMAP AND SAVE PORTAL LIST
              save_current_world_level(&level, &player, currentlvlname);
              save_portals(portals,portals_size);

              offset_x = (int)((SCREEN_WIDTH - level.width * TILESIZE) / 2);
              offset_y = (int)((SCREEN_HEIGHT - level.height * TILESIZE) / 2);
            }
          }
        }
        //END OF STATE UPDATE BLOCK

        //DRAW GAME BLOCK
        if(!worldmapmode){
          draw_game_state(&level, &player, &From, &To, sourceImage, buffer);
        }else if(worldmapmode){
          draw_worldmap_state(&level, &player, portals, &From, &To, sourceImage, buffer);
        }

        //Draw tile selection in debug mode
        if(editmode){
          if(worldmapmode){
            sTo.x = (int)((SCREEN_WIDTH - TILESIZE) / 2 + TILESIZE*(mouse_selection.x - player.x));
            sTo.y = (int)((SCREEN_HEIGHT - TILESIZE) / 2 + TILESIZE*(mouse_selection.y - player.y));
          }else{
            sTo.x = TILESIZE * mouse_selection.x + offset_x;
            sTo.y = TILESIZE * mouse_selection.y + offset_y;
          }
          SDL_BlitSurface(sourceImage, &sFrom, buffer ,&sTo);
        }

        if(SDL_UpdateWindowSurface( window ) < 0){
          printf("UpdateWindow error %s\n", SDL_GetError());
        }

        time_end = SDL_GetTicks();
        deltatime = time_end - time_start;

        //TODO:FPS counter here someday to check what it actually is, is it 30?
        //if()

        if(deltatime < SCREEN_TICKS_PER_FRAME){
          SDL_Delay(SCREEN_TICKS_PER_FRAME - deltatime);
        }
      }
    SDL_FreeSurface(sourceImage);
    }
  }
 //Destroy window
  SDL_DestroyWindow( window );
  //Quit SDL subsystems
  SDL_Quit();

  return 0;
}
