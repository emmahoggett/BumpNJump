#pragma once

#include <nds.h>
#include <string.h>
#include "road.h"
#include "carred.h"
#include "carpurple.h"




//Pointer to the graphic buffer where to store the sprite
u16* gfx;


void P_Graphics_Sub();
void P_Graphics_configureSprites();

void P_Graphics_Sub_config_BG0();
void P_Graphics_Sub_config_BG1();

void P_Graphics_setSprites(OamState oam, int sprite, int sprite_x, int sprite_y, int palette);
