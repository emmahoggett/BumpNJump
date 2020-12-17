#include <nds.h>
#include <stdio.h>
#include "P_Graphics.h"
#include "road.h"
#include "numbers.h"
#include "warning.h"
#include "carred.h"
#include "carjump.h"
#include "carpink.h"
#include "startscreenmain.h"

//Pointer to the graphic buffer where to store the sprite
u16* gfx_red;
u16* gfx_jump;
u16* gfx_pink;


void P_Map16x16_configureStart();
void P_Map16x16_configureBG0();
void P_Map16x16_configureBG2();
void P_Map16x16_configureBG3();

void P_Map16x16_configureBG2_Sub();

void P_Map16x16_scrolling_BG3(int _speed);
void P_Map16x16_scrolling_BG2_Sub(int _speed);
void P_Map16x16_scrolling_Init();
int scroll_pos(int bg_num);

void P_Map16x16_TimerInit();

void P_Map16x16_warning();

void P_Map16x16_Init();

void P_Graphics_configureSprites();
void P_Graphics_setCarRed(int sprite_x, bool hide);
void P_Graphics_setCarPink(int sprite_x, int sprite_y, bool hide);
void P_Graphics_setCarJump(int sprite_x, bool hide);




