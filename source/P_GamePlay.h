#pragma once

#include <nds.h>
#include "BumpNJumpDefines.h"
#include "P_Audio.h"
#include "P_Map16x16.h"
#include <nds/arm9/sound.h>		// sound functions
#include "soundbank.h"
#include "P_Score.h"
#include "P_Timer.h"
#include "P_Controls.h"

void Gameplay_Init();
void Gameplay_handleInput(enum ACTION a);

void Gameplay_Update();

void Gameplay_Enemies();

void carTouched(int x_enemy, int y_enemy);
void carJump(int x_enemy, int y_enemy);
int Get_Car_Pos();
