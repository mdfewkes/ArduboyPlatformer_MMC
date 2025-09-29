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

				// LoadRoom(level[0], 0);
				// LoadRoom(level[1], 1);
				// LoadRoom(level[2], 2);
			}
			break;
		
		case GameState::Gameplay:
			player.Update();
			for (int i = 0; i < MAX_SHOTS; i++) {
				shots[i].Update();
			}

			cameraLeft = player.position.x - WIDTH/2;
			if (cameraLeft < screenLeft) cameraLeft = screenLeft;
			if (cameraLeft > screenRight) cameraLeft = screenRight;
			DrawMap();
			player.Draw();
			for (int i = 0; i < MAX_SHOTS; i++) {
				shots[i].Draw();
			}

			break;
	}

	arduboy.display();
}


