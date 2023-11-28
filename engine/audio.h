#pragma once

#include "utils.h"

#pragma warning(push, 0)
#include <AudioFile.h>
#pragma warning(pop)
#include <portaudio.h>

#include <string>

namespace pong
{

class Sound
{
public:
    Sound(const std::string& filePath);

    const AudioFile<float>& GetAudioFile() const;

private:
    AudioFile<float> mAudioFile {};
};

class PlayingSound
{
public:
    PlayingSound(const Sound& sound);

    float GetNextSample();
    bool IsFinished() const;

private:
    const Sound* mSound { nullptr };
    int mIndex {0};
    int mNumFrames {0};
};

class AudioMixer
{
public:
    int AudioCallback(const void* inputBuffer, void* outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void* userData);

    void PlaySound(const Sound& sound);

private:
    std::vector<PlayingSound> mPlayingSounds {};
};

void ReadFile();

int AudioCallback(const void* inputBuffer, void* outputBuffer,
                  unsigned long framesPerBuffer,
                  const PaStreamCallbackTimeInfo* timeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void* userData);

} // namespace pong
