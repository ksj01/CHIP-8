#include <string>
#include <stdio.h>

using namespace std;

class chip8 {
private:
	unsigned short opcode;
	unsigned char memory[4096];
	unsigned char V[16];
	unsigned short I;
	unsigned short pc;
	unsigned char gfx[64 * 32];
	unsigned char delay_timer;
	unsigned char sound_timer;
	unsigned short stack[16];
	unsigned short sp;
	unsigned char key[16];

public:
	bool drawFlag;

	void initialize() {
		//initalize registers and memory once
		pc = 0x200;	// program counter starts at 0x200
		opcode = 0;	// Reset current opcode
		I = 0;		// Reset index register
		sp = 0;		// Reset stack pointer
		//Clear Display
		//Clear Stack
		for (int i = 0; i < 16; ++i) {
			stack[i] = NULL;
		}
		//Clear Registers V0-VF
		for (int i = 0; i < 16; ++i) {
			V[i] = NULL;
		}
		//Clear memory
		for (int i = 0; i < 4096; ++i) {
			memory[i] = NULL;
		}

		//Load fontset
		for (int i = 0; i < 80; ++i) {
			memory[i] = chip8_fontset[i];
		}

		delay_timer = 0;	//Reset timers
		sound_timer = 0;
	}

	void loadGame(string name) {

	}

	void emulateCycle() {
		//fetch opcode
		opcode = memory[pc] << 8 | memory[pc + 1];
		//decode opcode
			//decode the opcode from the opcode table on Wikipedia.
		//execute opcode

		//update timers
	}

	void setKeys() {

	}

};