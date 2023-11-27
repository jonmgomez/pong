#pragma once

#include <portaudio.h>

namespace pong
{

class Audio
{

};

void ReadFile();

int AudioCallback(const void* inputBuffer, void* outputBuffer,
                  unsigned long framesPerBuffer,
                  const PaStreamCallbackTimeInfo* timeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void* userData);

} // namespace pong
