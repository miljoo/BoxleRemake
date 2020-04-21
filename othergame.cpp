#include "othergame.hpp"

void linkTp(Tp tp1, Tp tp2){
  if(tp1.linked == 0 && tp2.linked == 0){
    tp1.tx = tp2.x;
    tp2.tx = tp1.x;

    tp1.ty = tp2.y;
    tp2.ty = tp1.y;

    tp1.linked = 1;
    tp2.linked = 1;
  }
}

int toggleButton(Level l,Player player, Button b[], unsigned int array_size){
	int id;
	for(unsigned int i = 0 ; i < array_size ; ++i){
		if(player.x == b[i].x && player.y == b[i].y){
			id = b[i].id;
			b[i].pressed = !b[i].pressed;
			return id;
		}
	}
	return -1;
}

void toggleDoors(int id, Level level){
	for(unsigned int j = 0 ; j < level.height ; ++j){
		for(unsigned int i = 0 ; i < level.width ; ++i){
			//if(level.worldmap[i][j].id == id){
				//level.worldmap[i][j].toggle = !level.worldmap[i][j].toggle;
			//}
		}
	}
}

void worldMove(Level* level, Player* player, unsigned int dir){

  if(player->dir == LEFT){

  }else if(player->dir == RIGHT){

  }else if(player->dir == UP){

  }else if(player->dir == DOWN){

  }
}
