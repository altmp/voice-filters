#pragma once

#include "main.h"

class RadioEffect : public alt::IAudioFilter {
	public:
		RadioEffect() {};
		~RadioEffect() {};

		void Process(pcmSample* data, uint32_t size) override;
};
