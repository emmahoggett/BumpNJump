#include <nds.h>

#include "P_Graphics_Sub.h"

#define SCREEN_WIDTH	256
#define	SCREEN_HEIGHT	192

#define	SPRITE_WIDTH	16
#define	SPRITE_HEIGHT	16


void handleInput();
void spritePosition(OamState oam, int sprite, int sprite_x, int sprite_y);
