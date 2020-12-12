#pragma once

#include <nds.h>
#include <string.h>
#include "road.h"
#include "carred.h"
#include "carpurple.h"
#include "startscreensub.h"

//Pointer to the graphic buffer where to store the sprite
u16* gfx;


void P_Graphics_Sub();
void P_Graphics_Sub_config_BG0();
void P_Graphics_Sub_config_Start();

void P_Graphics_Sub_scrolling_BG0(int speed);

void P_Graphics_configureSprites();
void spritePosition(OamState oam, int sprite, int sprite_x, int sprite_y);

int scrollPos();
