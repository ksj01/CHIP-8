#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

class chip8 {
private:
	unsigned short opcode;
	unsigned char memory[4096];
	unsigned char V[16];
	unsigned short I;
	unsigned short pc;
	unsigned char delay_timer;
	unsigned char sound_timer;
	unsigned short stack[16];
	unsigned short sp;
	unsigned char key[16];
	unsigned char chip8_fontset[80] =
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

public:
	bool drawFlag;
	unsigned char gfx[64 * 32];

	void initialize() {
		//initalize registers and memory once
		pc = 0x200;	// program counter starts at 0x200
		opcode = 0;	// Reset current opcode
		I = 0;		// Reset index register
		sp = 0;		// Reset stack pointer
		///Clear Display
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
		switch (opcode & 0xF000) {
			// swtiches for all opcodes //
		case 0xA000: // ANNN: Sets I to the address NNN
			// Execute opcode //
			I = opcode & 0x0FFF;
			pc += 2;
			break;
			// More cases and opcodes //

		case 0x0000:	//0x00E0: Clears the screen
			//Execute opcode
			break;

		case 0x000E:	//0x00EE: Returns from subroutine
			//Execute opcode
			break;

		case 0x2000:
			stack[sp] = pc;
			++sp;
			pc = opcode & 0x0FFF;
			break;
		case 0x0004:
			if (V[(opcode & 0x00F0) >> 4] > (0xFF - V[(opcode & 0x0F00) >> 8])) {
				V[0xF] = 1; //carry
			}
			else {
				V[0xF] = 0;
			}
			V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
			pc += 2;
			break;

		case 0x0033:
			memory[I] = V[(opcode & 0x0F00) >> 8] / 100;
			memory[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;
			memory[I + 2] = (V[(opcode & 0x0F00) >> 8] % 100) % 10;
			pc += 2;
			break;

		case 0xD000:
		{
			unsigned short x = V[(opcode & 0x0F00) >> 8];
			unsigned short y = V[(opcode & 0x00F0) >> 4];
			unsigned short height = opcode & 0x000F;
			unsigned short pixel;

			V[0xF] = 0;
			for (int yline = 0; yline < height; yline++) {
				pixel = memory[I + yline];
				for (int xline = 0; xline < 8; xline++) {
					if ((pixel & (0x80 >> xline)) != 0) {
						if (gfx[(x + xline + ((y + yline) * 64))] == 1) {
							V[0xF] = 1;
						}
						gfx[x + xline + ((y + yline) * 64)] ^= 1;
					}
				}
			}
			drawFlag = true;
			pc += 2;
		}
			break;

		default:
			cout << "Unknown opcode: 0x" << opcode << endl;
		}
		//update timers

		if (delay_timer > 0) {
			--delay_timer;
		}
		if (sound_timer > 0) {
			if (sound_timer == 1) {
				cout << "BEEP!" << endl;
			}
			--sound_timer;
		}
	}

	void setKeys() {

	}

};