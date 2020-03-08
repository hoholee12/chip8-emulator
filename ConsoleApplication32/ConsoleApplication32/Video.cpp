#include"Video.h"

void Video::init(char* str){
	//clear videobuffer
	for (int i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT); i++) videoBuffer[i] = 0;

	defaults::videoInit(str, SCREEN_WIDTH, SCREEN_HEIGHT, SCALE);

	draw();

}

void Video::draw(){

	int scan = 0;

	defaults::drawVideo(videoBuffer);


}

void Video::writeVBuffer(uint16 addr, uint8 input){
	videoBuffer[addr] = input;
}

uint8 Video::readVBuffer(uint16 addr){
	return videoBuffer[addr];
}

void Video::clearVBuffer(){
	for(int i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT); i++) videoBuffer[i] = 0;
}

void Video::copySprite(uint16 input, CPU* cpu, Memory* memory){
	//?x??
	uint8 *vx = cpu->getV((input & 0x0f00) >> 8);

	//??y?
	uint8 *vy = cpu->getV((input & 0x00f0) >> 4);

	//vf
	uint8 *vf = cpu->getV(0xf);

	//??nn
	uint8 n = input & 0x000f;
	*vf = 0x0; //default


	for (int y = 0; y < n; y++){
		for (int x = 0; x < 8; x++){
			int check1 = SCREEN_WIDTH * (*vy + y) + *vx + x;
			uint8 check2 = memory->read(*cpu->getIndexRegister() + y) << x;
			check2 >>= 7;
			printf("%d ", check2);
			if ((videoBuffer[check1] & check2) != 0) *vf = 0x1;
			videoBuffer[check1] ^= check2;
		}
		printf("\n");
	}
}