#include "boxle.hpp"

void cameraFollow(Camera* camera, Player* player){
  camera->x = player->x;
  camera->y = player->y;
}

int player_on_exit(Level* level, Player* player){
  if(player->x == level->ex && player->y == level->ey){
    return 1;
  }
  return 0;
}

int player_on_portal(Level* level, Player* player, Levelportal portal){
  if(player->x == portal.x && player->y == portal.y){
    return 1;
  }
  return 0;
}

void move(Level* level, Player* player, unsigned int dir, bool worldmapmode){
  if(worldmapmode){
    player->z = level->worldmap[player->x][player->y];

    if(player->dir != dir){
      player->dir = dir;
    }else{
      if(player->dir == LEFT){
        player->t = player->x - 1;
        if(player->x > 0 && player->z >= level->worldmap[player->t][player->y]){
          player->x -= 1;
        }else if((player->x > 1 && player->z >= level->worldmap[player->t - 1][player->y])
                 && (player->t != level->ex || player->y != level->ey)
                 && (worldmapmode == false)
                 && (level->worldmap[player->t][player->y] != 11)){
          player->x -= 1;
          int tmp = level->worldmap[player->x][player->y] - player->z;
          level->worldmap[player->x][player->y] = player->z;
          level->worldmap[player->t - 1][player->y] += tmp;
        }
      }else if(player->dir == RIGHT){
        player->t = player->x + 1;
        if(player->x < level->width - 1 && player->z >= level->worldmap[player->t][player->y]){
          player->x += 1;
        }else if((player->x < level->width - 2 && player->z >= level->worldmap[player->t + 1][player->y])
                 && (player->t != level->ex || player->y != level->ey)
                 && (worldmapmode == false)
                 && (level->worldmap[player->t][player->y] != 11)){
          player->x += 1;
          int tmp = level->worldmap[player->x][player->y] - player->z;
          level->worldmap[player->x][player->y] = player->z;
          level->worldmap[player->t + 1][player->y] += tmp;
        }
      }else if(player->dir == UP){
        player->t = player->y - 1;
        if(player->y > 0 && player->z >= level->worldmap[player->x][player->t]){
          player->y -= 1;
        }else if((player->y > 1 && player->z >= level->worldmap[player->x][player->t - 1])
                 && (player->t != level->ey || player->x != level->ex)
                 && (worldmapmode == false)
                 && (level->worldmap[player->x][player->t] != 11)){
          player->y -= 1;
          int tmp = level->worldmap[player->x][player->y] - player->z;
          level->worldmap[player->x][player->y] = player->z;
          level->worldmap[player->x][player->t - 1] += tmp;
        }
      }else if(player->dir == DOWN){
        player->t = player->y + 1;
        if(player->y < level->height - 1 && player->z >= level->worldmap[player->x][player->t]){
          player->y += 1;
        }else if((player->y < level->height - 2 && player->z >= level->worldmap[player->x][player->t + 1])
                 && (player->t != level->ey || player->x != level->ex)
                 && (worldmapmode == false)
                 && (level->worldmap[player->x][player->t] != 11)){
          player->y += 1;
          int tmp = level->worldmap[player->x][player->y] - player->z;
          level->worldmap[player->x][player->y] = player->z;
          level->worldmap[player->x][player->t + 1] += tmp;
        }
      }
    }
    player->z = level->worldmap[player->x][player->y];
  }else{
    player->z = level->playmap[player->x][player->y];
    if(player->dir != dir){
      player->dir = dir;
    }else{
      if(player->dir == LEFT){
        player->t = player->x - 1;
        if(player->x > 0 && player->z >= level->playmap[player->t][player->y]){
          player->x -= 1;
        }else if((player->x > 1 && player->z >= level->playmap[player->t - 1][player->y])
                 && (player->t != level->ex || player->y != level->ey)
                 && (worldmapmode == false)
                 && (level->playmap[player->t][player->y] != 11)
                 && (level->pushable[player->t][player->y])){
          player->x -= 1;
          int tmp = level->playmap[player->x][player->y] - player->z;
          level->playmap[player->x][player->y] = player->z;
          level->playmap[player->t - 1][player->y] += tmp;
        }
      }else if(player->dir == RIGHT){
        player->t = player->x + 1;
        if(player->x < level->width - 1 && player->z >= level->playmap[player->t][player->y]){
          player->x += 1;
        }else if((player->x < level->width - 2 && player->z >= level->playmap[player->t + 1][player->y])
                 && (player->t != level->ex || player->y != level->ey)
                 && (worldmapmode == false)
                 && (level->playmap[player->t][player->y] != 11)
                 && (level->pushable[player->t][player->y])){
          player->x += 1;
          int tmp = level->playmap[player->x][player->y] - player->z;
          level->playmap[player->x][player->y] = player->z;
          level->playmap[player->t + 1][player->y] += tmp;
        }
      }else if(player->dir == UP){
        player->t = player->y - 1;
        if(player->y > 0 && player->z >= level->playmap[player->x][player->t]){
          player->y -= 1;
        }else if((player->y > 1 && player->z >= level->playmap[player->x][player->t - 1])
                 && (player->t != level->ey || player->x != level->ex)
                 && (worldmapmode == false)
                 && (level->playmap[player->x][player->t] != 11)
                 && (level->pushable[player->x][player->t])){
          player->y -= 1;
          int tmp = level->playmap[player->x][player->y] - player->z;
          level->playmap[player->x][player->y] = player->z;
          level->playmap[player->x][player->t - 1] += tmp;
        }
      }else if(player->dir == DOWN){
        player->t = player->y + 1;
        if(player->y < level->height - 1 && player->z >= level->playmap[player->x][player->t]){
          player->y += 1;
        }else if((player->y < level->height - 2 && player->z >= level->playmap[player->x][player->t + 1])
                 && (player->t != level->ey || player->x != level->ex)
                 && (worldmapmode == false)
                 && (level->playmap[player->x][player->t] != 11)
                 && (level->pushable[player->x][player->t])){
          player->y += 1;
          int tmp = level->playmap[player->x][player->y] - player->z;
          level->playmap[player->x][player->y] = player->z;
          level->playmap[player->x][player->t + 1] += tmp;
        }
      }
    }
    player->z = level->playmap[player->x][player->y];
  }
}

void moveCamera(Player* camera, unsigned int dir, bool worldmapmode){
  if(worldmapmode){
    if(dir == LEFT){
      camera->x -= 1;
    }else if(dir == RIGHT){
      camera->x += 1;
    }else if(dir == UP){
      camera->y -= 1;
    }else if(dir == DOWN){
      camera->y += 1;
    }
  }
}

void jump(Level* level, Player* player, bool worldmapmode){
  if(worldmapmode){
    player->z = level->worldmap[player->x][player->y];
  if(player->dir == LEFT){
    if(player->x > 1 && level->worldmap[player->x - 1][player->y] <= player->z && level->worldmap[player->x - 2][player->y] <= player->z){
      player->x -= 2;
    }else if(player->x > 0 && (player->z + 1 == level->worldmap[player->x - 1][player->y] || player->z >= level->worldmap[player->x - 1][player->y])){
      player->x -= 1;
    }
  }else if(player->dir == RIGHT){
    if(player->x < level->width - 2 && level->worldmap[player->x + 1][player->y] <= player->z && level->worldmap[player->x + 2][player->y] <= player->z){
      player->x += 2;
    }else if(player->x < level->width - 1 && (player->z + 1 == level->worldmap[player->x + 1][player->y] || player->z >= level->worldmap[player->x + 1][player->y])){
      player->x += 1;
    }
  }else if(player->dir == UP){
    if(player->y > 1 && level->worldmap[player->x][player->y - 1] <= player->z && level->worldmap[player->x][player->y - 2] <= player->z){
      player->y -= 2;
    }else if(player->y > 0 && (player->z + 1 == level->worldmap[player->x][player->y - 1] || player->z >= level->worldmap[player->x][player->y - 1])){
      player->y -= 1;
    }
  }else if(player->dir == DOWN){
    if(player->y < level->height - 2 && level->worldmap[player->x][player->y + 1] <= player->z && level->worldmap[player->x][player->y + 2] <= player->z){
      player->y += 2;
    }else if(player->y < level->height - 1 && (player->z + 1 == level->worldmap[player->x][player->y + 1] || player->z >= level->worldmap[player->x][player->y + 1])){
      player->y += 1;
    }
  }
  player->z = level->worldmap[player->x][player->y];




  }else{
    player->z = level->playmap[player->x][player->y];
  if(player->dir == LEFT){
    if(player->x > 1 && level->playmap[player->x - 1][player->y] <= player->z && level->playmap[player->x - 2][player->y] <= player->z){
      player->x -= 2;
    }else if(player->x > 0 && (player->z + 1 == level->playmap[player->x - 1][player->y] || player->z >= level->playmap[player->x - 1][player->y])){
      player->x -= 1;
    }
  }else if(player->dir == RIGHT){
    if(player->x < level->width - 2 && level->playmap[player->x + 1][player->y] <= player->z && level->playmap[player->x + 2][player->y] <= player->z){
      player->x += 2;
    }else if(player->x < level->width - 1 && (player->z + 1 == level->playmap[player->x + 1][player->y] || player->z >= level->playmap[player->x + 1][player->y])){
      player->x += 1;
    }
  }else if(player->dir == UP){
    if(player->y > 1 && level->playmap[player->x][player->y - 1] <= player->z && level->playmap[player->x][player->y - 2] <= player->z){
      player->y -= 2;
    }else if(player->y > 0 && (player->z + 1 == level->playmap[player->x][player->y - 1] || player->z >= level->playmap[player->x][player->y - 1])){
      player->y -= 1;
    }
  }else if(player->dir == DOWN){
    if(player->y < level->height - 2 && level->playmap[player->x][player->y + 1] <= player->z && level->playmap[player->x][player->y + 2] <= player->z){
      player->y += 2;
    }else if(player->y < level->height - 1 && (player->z + 1 == level->playmap[player->x][player->y + 1] || player->z >= level->playmap[player->x][player->y + 1])){
      player->y += 1;
    }
  }
  player->z = level->playmap[player->x][player->y];
  }
}
