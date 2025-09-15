#pragma once

#include "math.h"

int worldmap[8][16] = {
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
  { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

bool GetCollisionAtMapPosition(Vector position) {
	int tileX = position.x / 8;
	int tileY = position.y / 8;
	
	if (tileX < 0 || tileX >= 16) return true;
	if (tileY < 0 || tileY >= 8) return true;

	return worldmap[tileY][tileX] > 0;
}

bool GetCollisionAtMapPosition(float x, float y) {
	int tileX = x / 8;
	int tileY = y / 8;

	return worldmap[tileY][tileX] > 0;
}