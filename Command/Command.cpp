// A small test program to exercise most of TIGR's features.

#include "tigr.h"
#include <math.h>
#include <iostream>

float playerx = 160, playery = 200;
float playerxs = 0, playerys = 0;
bool standing = true;
float remaining = 0;
Tigr* backdrop, * screen;

enum {GAMEPAD_UP = 1, GAMEPAD_DOWN = 2, GAMEPAD_LEFT = 4, GAMEPAD_RIGHT = 8};

// Some simple platformer-esque physics.
// I do not necessarily recommend this as a good way of implementing a platformer :)
void update(float dt, unsigned gamepad) {
  if (remaining > 0)
    remaining -= dt;

  // Read the keyboard and move the player.
  if (standing && (gamepad & GAMEPAD_UP))
    playerys -= 200;
  if (gamepad & GAMEPAD_LEFT)
    playerxs -= 10;
  if (gamepad & GAMEPAD_RIGHT)
    playerxs += 10;

  float oldx = playerx, oldy = playery;

  // Apply simply physics.
  playerxs *= exp(-10.0f * dt);
  playerys *= exp(-2.0f * dt);
  playerys += dt * 200.0f;
  playerx += dt * playerxs;
  playery += dt * playerys;

  // Apply collision.
  if (playerx < 8) {
    playerx = 8;
    playerxs = 0;
  }

  if (playerx > screen->w - 8) {
    playerx = screen->w - 8.0f;
    playerxs = 0;
  }

  // Apply playfield collision and stepping.
  float dx = (playerx - oldx) / 10;
  float dy = (playery - oldy) / 10;
  standing = false;
  for (int n = 0; n < 10; n++) {
    TPixel p = tigrGet(backdrop, (int)oldx, (int)oldy - 1);
    if (p.r == 0 && p.g == 0 && p.b == 0)
      oldy -= 1;
    p = tigrGet(backdrop, (int)oldx, (int)oldy);
    if (p.r == 0 && p.g == 0 && p.b == 0 && playerys > 0) {
      playerys = 0;
      dy = 0;
      standing = true;
    }
    oldx += dx;
    oldy += dy;
  }

  playerx = oldx;
  playery = oldy;
}

int main(int argc, char* argv[]) {
  // Load our sprite.
  Tigr* squinkle = tigrLoadImage("squinkle.png");
  if (!squinkle)
    tigrError(0, "Cannot load squinkle.png");

  // Make a window and an off-screen backdrop.
  screen = tigrWindow(320, 240, "hola", TIGR_2X);
  backdrop = tigrBitmap(screen->w, screen->h);

  // Fill in the background.
  tigrClear(backdrop, tigrRGB(80, 180, 255));
  tigrFill(backdrop, 0, 200, 320, 40, tigrRGB(60, 120, 60));
  tigrFill(backdrop, 0, 200, 320, 3, tigrRGB(0, 0, 0));
  tigrLine(backdrop, 0, 201, 320, 201, tigrRGB(255, 255, 255));

  // Enable post fx
  tigrSetPostFX(screen, 1, 1, 1, 2.0f);

  bool isRecording = true;
  int frame = 0;
  int maxFrame = 0;
  unsigned commands[512];
  float firstX = playerx;
  float firstY = playery;
  // Repeat till they close the window.
  while (!tigrClosed(screen) && !tigrKeyDown(screen, TK_ESCAPE)) {


    if(tigrKeyDown(screen, TK_RETURN))
    {
      playerx = firstX;
      playery = firstY;
      isRecording = !isRecording;
      maxFrame = frame;
      frame = 0;
    }

    unsigned gamepad = 0;

    if (isRecording)
    {

      gamepad |= tigrKeyHeld(screen, TK_UP) * GAMEPAD_UP;
      gamepad |= tigrKeyHeld(screen, TK_DOWN) * GAMEPAD_DOWN;
      gamepad |= tigrKeyHeld(screen, TK_LEFT) * GAMEPAD_LEFT;
      gamepad |= tigrKeyHeld(screen, TK_RIGHT) * GAMEPAD_RIGHT;
      commands[frame] = gamepad;
      frame++;
    }
    else
    {
      gamepad = commands[frame];
      frame++;
      if (frame == maxFrame)
      {
        frame = 0;
        playerx = firstX;
        playery = firstY;
      }
    }

    // Update the game.
    float dt = tigrTime();
    update(dt, gamepad);

    // Composite the backdrop and sprite onto the screen.
    tigrBlit(screen, backdrop, 0, 0, 0, 0, backdrop->w, backdrop->h);
    tigrBlitAlpha(screen, squinkle, (int)playerx - squinkle->w / 2, (int)playery - squinkle->h, 0, 0, squinkle->w,
      squinkle->h, 1.0f);

    // Update the window.
    tigrUpdate(screen);
  }

  tigrFree(squinkle);
  tigrFree(backdrop);
  tigrFree(screen);
  return 0;
}