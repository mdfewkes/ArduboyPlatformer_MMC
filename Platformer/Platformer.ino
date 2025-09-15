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
			for (int i = 0; i < MAX_SHOTS; i++) {
				shots[i].Draw();
			}

			break;
	}

	arduboy.display();
}



