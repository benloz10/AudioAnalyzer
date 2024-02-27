#include <iostream>
#include "wavereader.h"
/*Dial Tone Frequencies:
*     1209 1336 1477
* 697  1    2    3
* 770  4    5    6
* 852  7    8    9
* 941  *    0    #
*/

void PrintBar(const uint16_t value) {
	const int maxLength = 128;
	const double barMult = (double)value / 65536;
	const int barLength = maxLength * barMult;
	std::string bar = "";
	for (int i = 0; i < barLength; i++) {
		bar += "=";
	}
	std::cout << bar << std::endl;
}


int main() {
	WaveReader waveReader;
	bool success = waveReader.LoadFile("DialTest-Clean.wav");
	if (!success) {
		std::cout << "FAILED TO OPEN FILE.";
		return 1;
	}
	waveReader.PrintHeaders();

	//ITERATE THROUGH AUDIO DATA:
	for (int i = 0; i < waveReader.audio.size()-1; i+=2) {
		uint16_t data = waveReader.audio[i] | waveReader.audio[i+1] << 8;
		PrintBar(data);
	}

	waveReader.CloseFile();
	return 0;
}