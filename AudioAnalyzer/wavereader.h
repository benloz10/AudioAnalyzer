#ifndef _WAVEREADER_
#define _WAVEREADER_
#include <fstream>
#include <vector>
#include <iostream>

class WaveReader {
public:
	bool LoadFile(std::string fileName);

	void PrintHeaders();

	void CloseFile();

	std::string riffHeader = "";

	uint32_t fileSize = 0;
	std::string fileType = "";
	std::string formatChunk = "";
	uint32_t formatLength = 0;
	uint16_t formatType = 0;
	uint16_t channelCount = 0;
	uint32_t sampleRate = 0;
	uint32_t sampleData = 0;
	uint32_t wtf = 0;
	uint16_t bitRate = 0;
	std::string dataHeader = "";
	uint32_t dataSize = 0;

	std::vector<uint8_t> audio;
private:
	std::ifstream audioFile;
};

#endif