#pragma once

#include "main.h"

class MuteChannel : public alt::IAudioFilter {
	public:
		MuteChannel() {};
		~MuteChannel() {};

		void SetParam(const size_t& key, bool value) override;
		void GetParam(const size_t& key, bool& value) override;
		void Process(pcmSample* data, uint32_t size) override;
		
	private:
		bool isLeft = false;
};
