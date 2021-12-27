/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vinnie Falco

Official project location:
https://github.com/vinniefalco/DSPFilters

See Documentation.cpp for contact information, notes, and bibliography.

*******************************************************************************/

#ifndef DSPFILTERS_SMOOTHEDFILTER_H
#define DSPFILTERS_SMOOTHEDFILTER_H

#include "Common.h"
#include "Filter.h"

namespace Dsp {

/*
 * Implements smooth modulation of time-varying filter parameters
 *
 */
template <class DesignClass,
          int Channels,
          class StateType = DirectFormII>
class SmoothedFilterDesign
  : public FilterDesign <DesignClass,
                       Channels,
                       StateType>
{
public:
  typedef FilterDesign <DesignClass, Channels, StateType> filter_type_t;

  SmoothedFilterDesign (int transitionSamples)
    : m_transitionSamples (transitionSamples)
    , m_remainingSamples (-1) // first time flag
  {
  }

  // Process a block of samples.
  template <typename Sample>
  void processBlock (int numSamples, Sample* const* destChannelArray)
  {
    const int numChannels = this->getNumChannels();

    // If this goes off it means setup() was never called
    assert (m_remainingSamples >= 0);

    // first handle any transition samples
    int remainingSamples = (std::min) (m_remainingSamples, numSamples);

    if (remainingSamples > 0)
    {
      // interpolate parameters for each sample
      const double t = 1. / m_remainingSamples;
      double dp[maxParameters];
      for (int i = 0; i < DesignClass::NumParams; ++i)
        dp[i] = (this->getParams()[i] - m_transitionParams[i]) * t;

      for (int n = 0; n < remainingSamples; ++n)
      {
        for (int i = DesignClass::NumParams; --i >= 0;)
          m_transitionParams[i] += dp[i];

        m_transitionFilter.setParams (m_transitionParams);

        for (int i = numChannels; --i >= 0;)
        {
          Sample* dest = destChannelArray[i]+n;
          *dest = this->m_state[i].process (*dest, m_transitionFilter);
        }
      }

      m_remainingSamples -= remainingSamples;

      if (m_remainingSamples == 0)
        m_transitionParams = this->getParams();
    }

    // do what's left
    if (numSamples - remainingSamples > 0)
    {
      // no transition
      for (int i = 0; i < numChannels; ++i)
        this->m_design.process (numSamples - remainingSamples,
                          destChannelArray[i] + remainingSamples,
                          this->m_state[i]);
    }
  }

  void process (int numSamples, float* const* arrayOfChannels)
  {
    processBlock (numSamples, arrayOfChannels);
  }

  void process (int numSamples, double* const* arrayOfChannels)
  {
    processBlock (numSamples, arrayOfChannels);
  }

protected:
  void doSetParams (const Params& parameters)
  {
    if (m_remainingSamples >= 0)
    {
      m_remainingSamples = m_transitionSamples;
    }
    else
    {
      // first time
      m_remainingSamples = 0;
      m_transitionParams = parameters;
    }

    filter_type_t::doSetParams (parameters);
  }

protected:
  Params m_transitionParams;
  DesignClass m_transitionFilter;
  int m_transitionSamples;

  int m_remainingSamples;        // remaining transition samples
};

}

#endif
