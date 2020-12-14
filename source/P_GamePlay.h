
#pragma once

#include <nds.h>
#include "BumpNJumpDefines.h"
#include "P_Map16x16.h"

void Gameplay_Init();
void Gameplay_handleInput(enum ACTION a);
void Gameplay_Update();

int carTouched(int x_enemy, int y_enemy);
