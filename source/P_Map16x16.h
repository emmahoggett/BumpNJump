#include <nds.h>
#include "P_Graphics.h"
#include "road.h"
#include "numbers.h"

u16* mapMemory;

void P_Map16x16_configureStart();
void P_Map16x16_configureGameOver();

void P_Map16x16_configureBG3();
void P_Map16x16_configureBG0();
void P_Map16x16_configureBG2();

void P_Map16x16_configureBG2_Sub();

void P_Map16x16_scrolling_BG3(int _speed);
void P_Map16x16_scrolling_BG2_Sub(int _speed);

void P_Map16x16_TimerInit();

void P_Map16x16_warning();

void P_Map16x16_Init();

void P_Graphics_setSprites(OamState oam, int sprite, int sprite_x, int sprite_y, int palette);
void P_Graphics_configureSprites();




