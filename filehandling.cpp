#include "filehandling.hpp"

unsigned int portals_size;

void save_init_portals(Levelportal portals[], int portals_size){
  FILE * f;
  f = fopen("data/levels/init_portals.dat", "wb");
  if(f == NULL){
    printf("Couldn't open init_portals.dat in save_init_portals func call.\n");
  }else{
    for(int i = 0 ; i < portals_size ; ++i){
      fwrite(&portals[i].x, sizeof(unsigned int), 1, f);
      fwrite(&portals[i].y, sizeof(unsigned int), 1, f);
      fwrite(&portals[i].destination, sizeof(char[39]), 1, f);
      fwrite(&portals[i].active, sizeof(bool), 1, f);
    }
  }
  fclose(f);
}

void load_init_portals(Levelportal portals[], int portals_size){
  FILE * f;
  f = fopen("data/levels/init_portals.dat", "rb");
  if(f == NULL){
    printf("Couldn't open init_portals.dat in load_init_portals func call.\n");
  }else{
    for(int i = 0 ; i < portals_size ; ++i){
      fread(&portals[i].x, sizeof(unsigned int), 1, f);
      fread(&portals[i].y, sizeof(unsigned int), 1, f);
      fread(&portals[i].destination, sizeof(char[39]), 1, f);
      fread(&portals[i].active, sizeof(bool), 1, f);
    }
  }
  fclose(f);
}

void save_portals(Levelportal portals[], int portals_size){
  FILE * f;
  f = fopen("data/levels/portals.dat", "wb");
  if(f == NULL){
    printf("Couldn't open portals.dat in save_portals func call.\n");
  }else{
    for(int i = 0 ; i < portals_size ; ++i){
      fwrite(&portals[i].x, sizeof(unsigned int), 1, f);
      fwrite(&portals[i].y, sizeof(unsigned int), 1, f);
      fwrite(&portals[i].destination, sizeof(char[39]), 1, f);
      fwrite(&portals[i].active, sizeof(bool), 1, f);
    }
  }
  fclose(f);
}

void load_portals(Levelportal portals[], int portals_size){
  FILE * f;
  f = fopen("data/levels/portals.dat", "rb");
  if(f == NULL){
    printf("Couldn't open portals.dat in load_portals func call.\n");
  }else{
    for(int i = 0 ; i < portals_size ; ++i){
      fread(&portals[i].x, sizeof(unsigned int), 1, f);
      fread(&portals[i].y, sizeof(unsigned int), 1, f);
      fread(&portals[i].destination, sizeof(char[39]), 1, f);
      fread(&portals[i].active, sizeof(bool), 1, f);
    }
  }
  fclose(f);
}

void save_play_level_with_name(Level* level, Player* player){
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
    printf("Couldn't open file in save_play_level_with_name func call.\n");
  }else{
    fwrite(&player->x, sizeof(unsigned int), 1, f);
    fwrite(&player->y, sizeof(unsigned int), 1, f);
    fwrite(&player->z, sizeof(unsigned int), 1, f);
    fwrite(&player->t, sizeof(unsigned int), 1, f);
    fwrite(&player->dir, sizeof(unsigned int), 1, f);
    fwrite(&level->ex, sizeof(unsigned int), 1, f);
    fwrite(&level->ey, sizeof(unsigned int), 1, f);
    fwrite(&level->width, sizeof(unsigned int), 1, f);
    fwrite(&level->height, sizeof(unsigned int), 1, f);
    fwrite(&level->playmap, sizeof(level->playmap), 1, f);
    fwrite(&level->pushable, sizeof(level->pushable),1 ,f);
  }
  fclose(f);
}

void save_current_play_level(Level* level,Player* player, char currentlvlname[]){
  FILE * f;
  f = fopen(currentlvlname, "wb");
  if(f == NULL){
    printf("Couldn't open file in save_current_play_level func call.\n");
  }else{
    fwrite(&player->x, sizeof(unsigned int), 1, f);
    fwrite(&player->y, sizeof(unsigned int), 1, f);
    fwrite(&player->z, sizeof(unsigned int), 1, f);
    fwrite(&player->t, sizeof(unsigned int), 1, f);
    fwrite(&player->dir, sizeof(unsigned int), 1, f);
    fwrite(&level->ex, sizeof(unsigned int), 1, f);
    fwrite(&level->ey, sizeof(unsigned int), 1, f);
    fwrite(&level->width, sizeof(unsigned int), 1, f);
    fwrite(&level->height, sizeof(unsigned int), 1, f);
    fwrite(&level->playmap, sizeof(level->playmap), 1, f);
    fwrite(&level->pushable, sizeof(level->pushable),1 ,f);
  }
  fclose(f);
}

void load_play_level(Level* level, Player* player, char lvlname[]){
  FILE * f;
  f = fopen(lvlname, "rb");
  if(f == NULL){
    printf("Couldn't open file in load_play_level func call.\n");
  }else{
    fread(&player->x, sizeof(unsigned int), 1, f);
    fread(&player->y, sizeof(unsigned int), 1, f);
    fread(&player->z, sizeof(unsigned int), 1, f);
    fread(&player->t, sizeof(unsigned int), 1, f);
    fread(&player->dir, sizeof(unsigned int), 1, f);
    fread(&level->ex, sizeof(unsigned int), 1, f);
    fread(&level->ey, sizeof(unsigned int), 1, f);
    fread(&level->width, sizeof(unsigned int), 1, f);
    fread(&level->height, sizeof(unsigned int), 1, f);
    fread(&level->playmap, sizeof(level->playmap), 1, f);
    fread(&level->pushable, sizeof(level->pushable), 1, f);

    /*for(unsigned int j = 0 ; j < level->height ; ++j){
      for(unsigned int i = 0 ; i < level->width ; ++i){
        level->pushable[i][j] = true;
      }
    }
    */

  }
  fclose(f);
}

void save_world_level_with_name(Level* level, Player* player){
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
    printf("Couldn't open file in save_world_level_with_name func call.\n");
  }else{
    fwrite(&player->x, sizeof(unsigned int), 1, f);
    fwrite(&player->y, sizeof(unsigned int), 1, f);
    fwrite(&player->z, sizeof(unsigned int), 1, f);
    fwrite(&player->t, sizeof(unsigned int), 1, f);
    fwrite(&player->dir, sizeof(unsigned int), 1, f);
    fwrite(&level->ex, sizeof(unsigned int), 1, f);
    fwrite(&level->ey, sizeof(unsigned int), 1, f);
    fwrite(&level->width, sizeof(unsigned int), 1, f);
    fwrite(&level->height, sizeof(unsigned int), 1, f);
    fwrite(&level->worldmap, sizeof(level->worldmap), 1, f);
  }
  fclose(f);
}

void save_current_world_level(Level* level, Player* player, char currentlvlname[]){
  FILE * f;
  f = fopen(currentlvlname, "wb");
  if(f == NULL){
    printf("Couldn't open file in save_current_world_level func call.\n");
  }else{
    fwrite(&player->x, sizeof(unsigned int), 1, f);
    fwrite(&player->y, sizeof(unsigned int), 1, f);
    fwrite(&player->z, sizeof(unsigned int), 1, f);
    fwrite(&player->t, sizeof(unsigned int), 1, f);
    fwrite(&player->dir, sizeof(unsigned int), 1, f);
    fwrite(&level->ex, sizeof(unsigned int), 1, f);
    fwrite(&level->ey, sizeof(unsigned int), 1, f);
    fwrite(&level->width, sizeof(unsigned int), 1, f);
    fwrite(&level->height, sizeof(unsigned int), 1, f);
    fwrite(&level->worldmap, sizeof(level->worldmap), 1, f);
  }
  fclose(f);
}

void load_world_level(Level* level, Player* player, char lvlname[]){
  FILE * f;
  f = fopen(lvlname, "rb");
  if(f == NULL){
    printf("Couldn't open file in load_world_level func call.\n");
  }else{
    fread(&player->x, sizeof(unsigned int), 1, f);
    fread(&player->y, sizeof(unsigned int), 1, f);
    fread(&player->z, sizeof(unsigned int), 1, f);
    fread(&player->t, sizeof(unsigned int), 1, f);
    fread(&player->dir, sizeof(unsigned int), 1, f);
    fread(&level->ex, sizeof(unsigned int), 1, f);
    fread(&level->ey, sizeof(unsigned int), 1, f);
    fread(&level->width, sizeof(unsigned int), 1, f);
    fread(&level->height, sizeof(unsigned int), 1, f);
    fread(&level->worldmap, sizeof(level->worldmap), 1, f);
  }
  fclose(f);
}
