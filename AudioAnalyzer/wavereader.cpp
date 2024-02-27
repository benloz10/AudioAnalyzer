#include "wavereader.h"

bool WaveReader::LoadFile(std::string fileName) {

	audioFile.open(fileName, std::ios::binary);

	if (!audioFile.is_open()) {
		return false;
	}

	std::vector<uint8_t> binaryData((std::istreambuf_iterator<char>(audioFile)), std::istreambuf_iterator<char>());

	int ptr = 0;

	for (int ptr = 0; ptr < 44; ptr++) {
		uint8_t value = binaryData[ptr];
		if (ptr < 4) {
			riffHeader += (char)value;
		}
		else if (ptr < 8) {
			fileSize = fileSize | value << 8 * (ptr - 4);
		}
		else if (ptr < 12) {
			fileType += (char)value;
		}
		else if (ptr < 16) {
			formatChunk += (char)value;
		}
		else if (ptr < 20) {
			formatLength = formatLength | value << 8 * (ptr - 16);
		}
		else if (ptr < 22) {
			formatType = formatType | value << 8 * (ptr - 20);
		}
		else if (ptr < 24) {
			channelCount = channelCount | value << 8 * (ptr - 22);
		}
		else if (ptr < 28) {
			sampleRate = sampleRate | value << 8 * (ptr - 24);
		}
		else if (ptr < 32) {
			sampleData = sampleData | value << 8 * (ptr - 28);
		}
		else if (ptr < 34) {
			wtf = wtf | value << 8 * (ptr - 32);
		}
		else if (ptr < 36) {
			bitRate = bitRate | value << 8 * (ptr - 34);
		}
		else if (ptr < 40) {
			dataHeader += (char)value;
		}
		else if (ptr < 44) {
			dataSize = dataSize | value << 8 * (ptr - 40);
		}
	}

	for (int i = 45; i < binaryData.size(); i ++) {
		audio.push_back(binaryData[i]);
	}

	return true;
}

void WaveReader::PrintHeaders() {
	std::string formatName = "Unknown";
	if (formatType == 1) formatName = "PCM";

	std::cout << "FileHeader: " << riffHeader << std::endl;
	std::cout << "Size: " << (double)fileSize / 1000 << " KB" << std::endl;
	std::cout << "Type: " << fileType << std::endl;
	std::cout << formatChunk << "==========" << std::endl;
	std::cout << "Len: " << formatLength << std::endl;
	std::cout << "Type: " << formatName << std::endl;
	std::cout << "Channels: " << channelCount << std::endl;
	std::cout << "Sample Rate: " << sampleRate << " Hz" << std::endl;
	std::cout << "Data Rate: " << sampleData << " mbps" << std::endl;
	std::cout << "Wtfisthis: " << wtf << std::endl;
	std::cout << "BitRate: " << bitRate << " bits" << std::endl;
	std::cout << dataHeader << "==========" << std::endl;
	std::cout << "Data Size: " << (double)dataSize / 1000 << " KB" << std::endl;
}

void WaveReader::CloseFile() {
	audioFile.close();
}