#include "audio.h"

#include <cmath>
#include <chrono>
#include <iostream>

#pragma warning(push, 0)
#include <AudioFile.h>
#pragma warning(pop)

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 256

#include "config.h"

namespace pong
{

auto lastTime = std::chrono::system_clock::now();

constexpr float VOLUME = 0.35f;

AudioFile<float> audioFile;
int numSamples = 0;
int currentSample = 0;

void ReadFile()
{
    audioFile.load("assets/test.wav");
    if (audioFile.isMono())
    {
        std::cout << "Audio file is mono" << std::endl;
    }
    else if (audioFile.isStereo())
    {
        std::cout << "Audio file is stereo" << std::endl;
    }
    numSamples = audioFile.getNumSamplesPerChannel();
    std::cout << "Audio file has " << numSamples << " samples" << std::endl;

    // for (int i = 0; i < numSamples; i++)
    // {
    //     std::cout << audioFile.samples[0][i] << std::endl;
    // }
}

int AudioCallback(const void* /*inputBuffer*/, void* outputBuffer,
                  unsigned long framesPerBuffer,
                  const PaStreamCallbackTimeInfo* timeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void* userData)
{
    (void)timeInfo; // Unused
    (void)statusFlags; // Unused
    (void)userData; // Unused

    auto currentTime = std::chrono::system_clock::now();
    auto timeWaitedUs = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime);
    std::cout << "AudioCallback called with " << framesPerBuffer << " framesPerBuffer, and " << timeWaitedUs.count() << " us since last call\n";
    lastTime = currentTime;

    if (timeWaitedUs.count() < 600)
    {
        if (Config::GetValue("test", false))
        {
            std::cout << "returning" << std::endl;
            return paContinue;
        }
    }

    float* out = static_cast<float*>(outputBuffer);

    int startSample = currentSample;
    int frames = static_cast<int>(framesPerBuffer);
    for (; currentSample < numSamples && currentSample - startSample < frames; currentSample++)
    {
        *out++ = audioFile.samples[0][currentSample] * VOLUME;
        *out++ = audioFile.samples[1][currentSample] * VOLUME;
    }

    // // Simple example: Generate a stereo signal with different tones for left and right channels
    // for (unsigned int i = 0; i < framesPerBuffer; ++i) {
    //     // Left channel: 440 Hz sine wave
    //     *out++ = 0.5f * static_cast<float>(std::sin(2.0 * 3.14159265359 * 480.0 * i / SAMPLE_RATE)) * VOLUME;

    //     // Right channel: 880 Hz sine wave
    //     *out++ = 0; // 0.5f * static_cast<float>(std::sin(2.0 * 3.14159265359 * 440.0 * i / SAMPLE_RATE));
    // }

    return paContinue;
}

} // namespace pong
