#include "RadioEffect.h"
#include "../../lib/DSPFilters/headers/Dsp.h"

#include <sstream>
#include <iostream>
#include <iomanip>

using namespace alt;
using namespace Dsp;

void RadioEffect::Process(pcmSample* data, uint32_t size) {
    Dsp::Filter* f = new Dsp::FilterDesign
        <Dsp::ChebyshevII::Design::BandPass <5>, 2>;
    Dsp::Params params;
    params[0] = 44100; // Sample rate
    params[1] = 5; // Order
    params[2] = 7000; // Corner frequency
    params[3] = 600; // Shelf gain
    params[4] = 0.1; // Passband ripple
    f->setParams(params);

    int numSamples = size / 2;
    float* audioData[2];
    audioData[0] = new float[1];
    audioData[1] = new float[1];

    for (int i = 0; i < numSamples; i++) {
        audioData[0][0] = data[i].channels.right;
        audioData[1][0] = data[i].channels.left;

        f->process(1, audioData);

        data[i].channels.right = audioData[0][0];
        data[i].channels.left = audioData[1][0];
    }
}
