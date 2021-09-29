#include "MuteChannel.h"

void MuteChannel::SetParam(const std::string& key, bool value)
{
    if (key == "isLeft")
        isLeft = value;
}

void MuteChannel::GetParam(const std::string& key, bool& value)
{
    if (key == "isLeft")
        value = isLeft;
}

void MuteChannel::Process(pcmSample* data, uint32_t size)
{
    for (int i = 0; i < size / 2; i++)
    {
        if (isLeft)
            data[i].channels.left = 0;
        else
            data[i].channels.right = 0;
    }
}