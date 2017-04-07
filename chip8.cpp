// CHIP8.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
//#include OpenGL graphics and input stuff
#include "chip8.h"

chip8 myChip8;

int main()
{
	//set up render systems and register input callbacks
	//setupGraphics();
	//setupInput();

	//initialize the chip8 system and load the game into memory
	myChip8.initialize();
	myChip8.loadGame("pong");

	//emulation loop {
	for (;;)
	{
		//emulate one cycle
		myChip8.emulateCycle();
		//If the draw flag is set, update the screen
		if (myChip8.drawFlag) {
			drawGraphics();
		}
		// Store key press state (press and release)
		myChip8.setKeys();
	// }
	}
    return 0;
}

