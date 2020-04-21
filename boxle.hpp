#ifndef BOXLE_HPP
#define BOXLE_HPP

enum {UP, LEFT, DOWN, RIGHT};

struct Transition_storage{
  unsigned int px, py, wx, wy, lx, ly, height, width;
};

struct Selection{
  unsigned int x;
  unsigned int y;
};

struct Player{
  unsigned int x, y, z, t, dir;
};

struct Camera{
  unsigned int x, y;
};

struct Level{
  unsigned int ex, ey;
  unsigned int width;
  unsigned int height;
  unsigned int playmap[20][20];
  unsigned int worldmap[100][100];
  bool pushable[20][20];
};

struct Levelportal{
  unsigned int x, y;
  char destination[39];
  bool active;
};

void cameraFollow(Camera* camera, Player* player);

int player_on_exit(Level* level, Player* player);

int player_on_portal(Level* level, Player* player, Levelportal portal);

void move(Level* level, Player* player, unsigned int dir, bool worldmapmode);

void moveCamera(Player* camera, unsigned int dir, bool worldmapmode);

void jump(Level* level, Player* player, bool worldmapmode);

#endif
