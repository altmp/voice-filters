#include "RadioEffect.h"

#include <sstream>
#include <iostream>
#include <iomanip>

using namespace alt;
using namespace Dsp;

void RadioEffect::Process(pcmSample* data, uint32_t size) {
    int numSamples = size / 2;
    Init();

    for (int i = 0; i < numSamples; i++) {
        audioData[0][0] = data[i].channels.right;
        audioData[1][0] = data[i].channels.left;

        f->process(1, audioData);

        data[i].channels.right = audioData[0][0];
        data[i].channels.left = audioData[1][0];
    }
}

void RadioEffect::Init() {
    Dsp::Params params;
    params[0] = 44100; // Sample rate
    params[1] = 5; // Order
    params[2] = 7000; // Corner frequency
    params[3] = 600; // Shelf gain
    params[4] = 0.1; // Passband ripple

    f->setParams(params);

    audioData[0] = new float[1];
    audioData[1] = new float[1];
}
