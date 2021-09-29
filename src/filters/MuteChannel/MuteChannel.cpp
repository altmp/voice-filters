#include "MuteChannel.h"

using namespace alt;

void MuteChannel::SetParam(const size_t& key, bool value)
{
    if (key == hash("isLeft"))
        isLeft = value;
}

void MuteChannel::GetParam(const size_t& key, bool& value)
{
    if (key == hash("isLeft"))
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