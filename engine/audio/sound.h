#pragma once

#include <AudioFile.h>

#include <string>

namespace pong
{

class Sound
{
public:
    Sound();
    Sound(const std::string& filePath);

    void SetSource(const std::string& filePath);
    const AudioFile<float>& GetAudioFile() const;

private:
    AudioFile<float> mAudioFile {};
};

} // namespace pong
