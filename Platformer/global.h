#pragma once

#include <Arduboy2.h>
Arduboy2 arduboy;

#define ARDBITMAP_SBUF arduboy.getBuffer()
#include <ArdBitmap.h>
ArdBitmap<WIDTH, HEIGHT> ardbitmap;

const int FRAME_RATE = 60;
const uint8_t JUMP_BUTTON = B_BUTTON;
const uint8_t SHOT_BUTTON = A_BUTTON;

double deltaTime = 0.0f;
unsigned long now = 0;