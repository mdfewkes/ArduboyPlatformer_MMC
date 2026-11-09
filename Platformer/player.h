#include "Print.h"
#pragma once

#include "global.h"
#include "math.h"
#include "map.h"

const uint8_t PROGMEM PlayerImg[] = {
// 12, 12,
0x00, 0x60, 0xd0, 0xdc, 0x22, 0x2a, 0xaa, 0x5c, 0x50, 0x70, 0x70, 0x20, 
0x00, 0x0c, 0x0e, 0x0d, 0x07, 0x03, 0x0d, 0x0e, 0x0c, 0x00, 0x00, 0x00, 
};

const int MAX_SHOTS = 3;
const int SHOT_SPEED = 1.5 * 60;
struct Shot {
	Vector position;
	float xVelocity;
	bool active = false;

	void Update() {
		if (active) {
			position.x += xVelocity * deltaTime;

			// if (GetCollisionAtMapPosition(position.x, position.y)) {
			// 	active = false;
			// }
			if (position.x < cameraLeft || position.x > cameraLeft + WIDTH) {
				active = false;
			}
		}
	}

	void Draw() {
		if (active) {
			arduboy.drawCircle(position.x - cameraLeft, position.y, 1);
		}
	}
};
Shot shots[MAX_SHOTS];

struct Player {
	const float speed = 0.75f * 60;
	const float jumpVelocity = 1.7551f * 60;
	const float gravity = 0.09f * 60 * 60;
	const float jumpCutFallSpeed = 0.09f * 60.0f;

	Vector position {x: 64, y: 32};
	Vector velocity;
	int8_t face = 1; // -1: left, 1: right
	bool grounded = false;

	void Update() {
		velocity.x = 0;
		velocity.y += gravity * deltaTime;

		// Movement input
		if (arduboy.justPressed(JUMP_BUTTON) && grounded) {
			velocity.y = -jumpVelocity;
			grounded = false;
		}
		if (arduboy.justReleased(JUMP_BUTTON) && velocity.y < 0) {
			velocity.y = jumpCutFallSpeed;
		}
		if (arduboy.pressed(LEFT_BUTTON)) {
			velocity.x -= speed;
			face = -1;
		}
		if (arduboy.pressed(RIGHT_BUTTON)) {
			velocity.x += speed;
			face = 1;
		}

		const float dx = velocity.x * deltaTime;
		const float dy = velocity.y * deltaTime;
		
		// Apply horizontal movement
		if (!GetCollisionAtMapPosition(position.x + dx + (4 * face), position.y)
		 && !GetCollisionAtMapPosition(position.x + dx + (4 * face), position.y - 8)
		) {
			position.x += dx;
		}

		// Apply veritcal movement
		if (!GetCollisionAtMapPosition(position.x + 3, position.y + dy + (velocity.y < 0 ? -8 : 0))
		 && !GetCollisionAtMapPosition(position.x - 3, position.y + dy + (velocity.y < 0 ? -8 : 0))
		) {
			position.y += dy;
		} else {
			grounded = velocity.y > 0 ? true : false;
			velocity.y = 0;
		}

		// Shoot		
		if (arduboy.justPressed(SHOT_BUTTON)) {
			for (int i = 0; i < MAX_SHOTS; i++) {
				if (!shots[i].active) {
					shots[i].position = {x: position.x + (4 * face), y: position.y - 7};
					shots[i].xVelocity = SHOT_SPEED * face;
					shots[i].active = true;
					break;
				}
			}
		}
	}

	void Draw() {
		ardbitmap.drawBitmap(position.x - cameraLeft, position.y, PlayerImg, 12, 12, WHITE, ALIGN_V_BOTTOM | ALIGN_H_CENTER, face > 0 ? MIRROR_NONE : MIRROR_HORIZONTAL);
	}
} player;


