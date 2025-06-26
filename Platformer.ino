#include <Arduboy2.h>
#include "math.h"

Arduboy2 arduboy;

// http://www.bloggingadeadhorse.com/TeamARGImgConverter/

enum GameState : byte {Title, Gameplay} gameState;


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

struct Player {
	Vector position {x: 64, y: 32};
	Vector velocity;
	float speed = 1;
	float jumpVelocity = 1.7551f; //2.4375
	float gravity = 0.09f; //0.125
	int face = 1; // -1: left, 1: right
	int grounded = false;

	void Update() {
		velocity.x = 0;
		velocity.y += gravity;

		if (arduboy.justPressed(A_BUTTON) && grounded) {
			velocity.y -= jumpVelocity;
			grounded = false;
		}
		if (arduboy.justReleased(A_BUTTON) && velocity.y < 0) {
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

		if (!GetCollisionAtMapPosition(position.x + velocity.x, position.y + velocity.y + (velocity.y < 0 ? -8 : 0))) {
			position.y += velocity.y;
		} else {
			velocity.y = 0;
			grounded = true;
		}
		
		if (!GetCollisionAtMapPosition(position.x + velocity.x + (4 * face), position.y)
		 && !GetCollisionAtMapPosition(position.x + velocity.x + (4 * face), position.y - 8)
		 && !GetCollisionAtMapPosition(position.x + velocity.x + (4 * face), position.y - 12)) 
		{
			position.x += velocity.x;
		}
	}

	void Draw() {
		arduboy.fillRect(position.x - 6, position.y - 12, 12, 12, WHITE);
	}
} player;



void setup() {
	arduboy.begin();
	arduboy.clear();

	arduboy.setFrameRate(60);
}

void loop() {
	if (!arduboy.nextFrame()) return;

	arduboy.clear();
	arduboy.pollButtons();

	switch (gameState) {
		case GameState::Title:
			arduboy.setCursor(0, 0);
			arduboy.print("Title");

			if (arduboy.justPressed(A_BUTTON)) {
				gameState = GameState::Gameplay;
			}
			break;
		
		case GameState::Gameplay:
			player.Update();

			for (int y = 0; y < 8; ++y) {
				for (int x = 0; x < 16; ++x) {
					if (worldmap[y][x] > 0) {
						arduboy.fillRect(x * 8, y * 8, 7, 7, WHITE);
					} else {
						arduboy.fillRect(x * 8, y * 8, 1, 1, WHITE);
					}
				}
			}
			player.Draw();

			break;
	}

	arduboy.display();
}



