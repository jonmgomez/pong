#pragma once

namespace pong
{

class Renderable
{
public:
    bool IsEnabled() const
    {
        return mEnabled;
    }

    void SetEnabled(bool enabled)
    {
        mEnabled = enabled;
    }

private:
    bool mEnabled { true };
};

} // namespace pong
