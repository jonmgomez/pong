#include "sound.h"

#include "utils.h"

namespace pong
{

Sound::Sound()
{
    mAudioFile.shouldLogErrorsToConsole(false);
}

Sound::Sound(const std::string& filePath)
{
    mAudioFile.shouldLogErrorsToConsole(false);

    ASSERT(mAudioFile.load(filePath));
}

void Sound::SetSource(const std::string& filePath)
{
    ASSERT(mAudioFile.load(filePath));
}

const AudioFile<float>& Sound::GetAudioFile() const
{
    return mAudioFile;
}

} // namespace pong
