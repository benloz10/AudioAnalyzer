#include <iostream>
#include "wavereader.h"
/*Dial Tone Frequencies:
*     1209 1336 1477
* 697  1    2    3
* 770  4    5    6
* 852  7    8    9
* 941  *    0    #
*/

void PrintBar(const int16_t value) {
	const int maxLength = 180;
	const double barMult = (double)((value*4)+32768) / 65536;
	const int pointPos = maxLength * barMult;
	std::string bar = "";
	for (int i = 0; i < maxLength; i++) {
		if (i >= pointPos && i <= maxLength / 2) {
			bar += '=';
		}
		else if (i >= maxLength / 2 && i <= pointPos) {
			bar += '=';
		}
		else {
			bar += ' ';
		}
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
		//uint16_t data = waveReader.audio[i] | waveReader.audio[i+1] << 8;
		int16_t data = waveReader.audio[i + 1] | waveReader.audio[i] << 8;
		PrintBar(data);
	}

	waveReader.CloseFile();
	return 0;
}