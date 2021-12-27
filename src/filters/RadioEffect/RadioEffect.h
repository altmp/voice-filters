#pragma once

#include "main.h"
#include "../../lib/DSPFilters/headers/Dsp.h"

class RadioEffect : public alt::IAudioFilter {
	public:
		RadioEffect() {};
		~RadioEffect() {};

		void Process(pcmSample* data, uint32_t size) override;

	private:
		Dsp::Filter* f = new Dsp::FilterDesign<Dsp::ChebyshevII::Design::BandPass <5>, 2>;
		float* audioData[2];

		void Init();
};
