#pragma once

#include "global.h"
#include "math.h"
#include "map.h"

const int MAX_SHOTS = 4;
const int SHOT_SPEED = 3;
struct Shot {
	Vector position;
	float xVelocity;
	bool active = false;

	void Update() {
		if (active) {
			position.x += xVelocity;

			if (GetCollisionAtMapPosition(position.x, position.y)) {
				active = false;
			}
		}
	}

	void Draw() {
		if (active) {
			arduboy.fillCircle(position.x, position.y, 2);
		}
	}
};
Shot shots[MAX_SHOTS];

struct Player {
	Vector position {x: 64, y: 32};
	Vector velocity;
	float speed = 1;
	float jumpVelocity = 1.7551f; //2.4375
	float gravity = 0.09f; //0.125
	int8_t face = 1; // -1: left, 1: right
	bool grounded = false;

	void Update() {
		velocity.x = 0;
		velocity.y += gravity;

		// Movement input
		if (arduboy.justPressed(JUMP_BUTTON) && grounded) {
			velocity.y -= jumpVelocity;
			grounded = false;
		}
		if (arduboy.justReleased(JUMP_BUTTON) && velocity.y < 0) {
			velocity.y = gravity;
		}
		if (arduboy.pressed(LEFT_BUTTON)) {
			velocity.x -= speed;
			face = -1;
		}
		if (arduboy.pressed(RIGHT_BUTTON)) {
			velocity.x += speed;
			face = 1;
		}

		//char strBuf[120];
		//sprintf(strBuf, "y: %d vy: %d g: %d", (int)position.y, (int)velocity.y, grounded ? 1 : 0);
		//Serial.println(strBuf);

		// Apply veritcal movement
		if (!GetCollisionAtMapPosition(position.x + velocity.x, position.y + velocity.y + (velocity.y < 0 ? -8 : 0))) {
			position.y += velocity.y;
		} else {
			velocity.y = 0;
			grounded = true;
		}
		
		// Apply horizontal movement
		if (!GetCollisionAtMapPosition(position.x + velocity.x + (4 * face), position.y)
		 && !GetCollisionAtMapPosition(position.x + velocity.x + (4 * face), position.y - 8)
		 && !GetCollisionAtMapPosition(position.x + velocity.x + (4 * face), position.y - 12)) 
		{
			position.x += velocity.x;
		}

		// Shoot		
		if (arduboy.justPressed(SHOT_BUTTON)) {
			for (int i = 0; i < MAX_SHOTS; i++) {
				if (!shots[i].active) {
					shots[i].position = {x: position.x + (4 * face), y: position.y - 6};
					shots[i].xVelocity = SHOT_SPEED * face;
					shots[i].active = true;
					break;
				}
			}
		}
	}

	void Draw() {
		arduboy.fillRect(position.x - 6, position.y - 12, 12, 12, WHITE);
	}
} player;