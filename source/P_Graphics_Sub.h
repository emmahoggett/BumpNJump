#pragma once

#include <nds.h>
#include <string.h>
#include "road.h"
#include "carred.h"
#include "P_Graphics_Main.h"


#define SCREEN_WIDTH	256
#define	SCREEN_HEIGHT	192

#define	SPRITE_WIDTH	16
#define	SPRITE_HEIGHT	16

//Pointer to the graphic buffer where to store the sprite
u16* gfx;


void P_Graphics_Sub();
void P_Graphics_configureSprites();

void P_Graphics_Sub_config_BG0();
void P_Graphics_Sub_config_BG2();
