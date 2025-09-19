#include "global.h"
#include "math.h"
#include "map.h"
#include "player.h"

enum GameState : byte {Title, Gameplay} gameState;

void setup() {
	arduboy.begin();
	arduboy.clear();

	arduboy.setFrameRate(FRAME_RATE);
}

void loop() {
	if (!arduboy.nextFrame()) return;

	deltaTime = (millis() - now) / 1000.0;
	now = millis();

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
			for (int i = 0; i < MAX_SHOTS; i++) {
				shots[i].Update();
			}

			cameraLeft = player.position.x - WIDTH/2;
			if (cameraLeft < 0) cameraLeft = 0;
			if (cameraLeft > SCREEN_WIDTH * (SCREENS_WIDE - 1) * TILE_SIZE) cameraLeft = SCREEN_WIDTH * (SCREENS_WIDE - 1) * TILE_SIZE;
			DrawMap();
			player.Draw();
			for (int i = 0; i < MAX_SHOTS; i++) {
				shots[i].Draw();
			}

			break;
	}

	arduboy.display();
}


