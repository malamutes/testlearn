#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

const int WAV_FILE_LENGTH_TIME = 3; // 3 seconds
const uint16_t BIT_DEPTH = 16;
const uint32_t FORMAT_LENGTH = 16;
const double SAMPLE_RATE_DOUBLE = 44100;
const uint32_t SAMPLE_RATE = 44100;
const uint16_t FORMAT_TYPE = 1;
const uint16_t NUM_CHANNELS = 1;
const double PI = 4.0 * std::atan(1.0);
const int16_t MAX_VOLUME = 32767;
const uint16_t BLOCK_ALIGN = BIT_DEPTH * NUM_CHANNELS / 8;
const uint32_t BYTE_RATE = SAMPLE_RATE * BIT_DEPTH * NUM_CHANNELS / 8;

// https://docs.fileformat.com/audio/wav/

#pragma pack(push, 1)
struct WAV_Header {      // should be 44 bytes
    char riff_marker[4]; // 4 bytes, RIFF
    uint32_t file_size;
    char file_type_header[4];    // for now only WAVE
    char format_chunk_marker[4]; // "fmt "
    uint32_t format_length;
    uint16_t format_type;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate; //(Sample Rate * BitsPerSample * Channels) / 8
    uint16_t block_align;
    uint16_t bits_per_sample; // bit_depth
    char data_chunk_header[4];
    uint32_t data_size;
};
#pragma pop

struct WAV {
    WAV_Header Header;
    std::vector<int16_t> data_chunk;
};

int main() {
    std::ofstream waveOutputFile;
    uint32_t totalSamples = SAMPLE_RATE * WAV_FILE_LENGTH_TIME; // basically total numbers needed
    uint32_t dataSize = totalSamples * NUM_CHANNELS * BIT_DEPTH / 8;
    uint32_t totalFileSize = dataSize + 36;

    double sample = 0;
    double sample2 = 0;
    std::vector<int16_t> soundOutputVector(totalSamples);

    std::cout << "GENERATING WAVE NUMBERS" << std::endl;
    std::cout << "================================" << std::endl;

    waveOutputFile.open("lessons/lesson-06/soundOutputFile.txt");

    for (uint32_t time = 0; time < totalSamples; time++) {
        sample2 = std::sin(2 * PI * 440.0 * (time / SAMPLE_RATE_DOUBLE));

        soundOutputVector[time] = (sample + sample2) * MAX_VOLUME / 1.5;
    }

    std::cout << "FINISHED" << std::endl;
    std::cout << "================================" << std::endl;

    waveOutputFile.close();

    std::cout << "CLOSED FILE" << std::endl;
    std::cout << "================================" << std::endl;

    std::cout << "VECTOR ARRAY NUMBER: " << soundOutputVector.size() << std::endl;

    WAV wavFile;
    WAV_Header header;

    std::memcpy(header.riff_marker, "RIFF", 4);
    header.file_size = totalFileSize;
    std::memcpy(header.file_type_header, "WAVE", 4);
    std::memcpy(header.format_chunk_marker, "fmt ", 4);

    header.format_length = 16;
    header.format_type = 1; // PCM
    header.num_channels = NUM_CHANNELS;
    header.sample_rate = SAMPLE_RATE;
    header.byte_rate = BYTE_RATE;
    header.block_align = BLOCK_ALIGN;
    header.bits_per_sample = BIT_DEPTH;

    std::memcpy(header.data_chunk_header, "data", 4);
    header.data_size = dataSize;

    wavFile.Header = header;

    wavFile.data_chunk = soundOutputVector;

    std::cout << "WRITING TO WAV FILE" << std::endl;
    std::cout << "================================" << std::endl;

    std::ofstream wavOutputFile("lessons/lesson-06/output.wav", std::ios::binary);
    wavOutputFile.write(reinterpret_cast<const char *>(&wavFile.Header), sizeof(wavFile.Header));
    wavOutputFile.write(reinterpret_cast<const char *>(wavFile.data_chunk.data()),
                        wavFile.data_chunk.size() * sizeof(int16_t));
    wavOutputFile.close();

    std::cout << "FINISHED WRITING TO WAV" << std::endl;
    std::cout << "================================" << std::endl;
    return 0;
}
